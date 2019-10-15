/*

Authors: Cromulence <cgc@cromulence.com>

Copyright (c) 2015 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#include "cgc_malloc.h"
#include "cgc_stdlib.h"
#include "cgc_stdio.h"
#include "cgc_string.h"

typedef struct meta {
	cgc_size_t length;
	struct meta *next;
	struct meta *prev;
} meta, *pmeta;

#define BUCKET( size )	(size > 1016 ? 0 : size / 8 )

/// Each bucket is the head of a singly linked list
///  The size for the bucket can be calculated via index*8
///  However, the freelist bucket 0 also uses the prev pointer
pmeta lookaside[128] = {NULL};

void cgc_link( pmeta linkme )
{
	pmeta walker = lookaside[0];

	if ( linkme == NULL ) {
		return;
	}

	/// Handle the case where this is <= 1016
	if ( linkme->length <= 1016 ) {
		//cgc_printf("Adding into bucket: $d\n", BUCKET( linkme->length) );
		linkme->next = lookaside[ BUCKET( linkme->length ) ];
		lookaside[ BUCKET( linkme->length ) ] = linkme;
		return;
	}

	while ( walker ) {
		if ( walker->next == NULL ) {
			walker->next = linkme;
			linkme->prev = walker;
			linkme->next = NULL;
			return;
		} else if ( linkme->length < walker->next->length ) {
			linkme->next = walker->next;
			linkme->prev = walker;
			walker->next->prev = linkme;
			walker->next = linkme;
			return;
		} else {
			walker = walker->next;
		}
	}

	return;
}

void cgc_add_freelist_block( cgc_size_t length )
{
	pmeta block = NULL;
	pmeta walker = NULL;

	/// Round to the nearest page

	/// Account for the 4 byte length field
	length += 4;

	length = (length + 4095 ) & 0xfffff000;

	if ( cgc_allocate( length, 0, (void**)&block) != 0 ) {
		cgc_printf("[ERROR] Allocating a free list block failed: $d\n", length);
		cgc__terminate(-1);
	}

	cgc_bzero( block, length );

	block->length = length-4;
	
	if ( lookaside[0] == NULL ) {
		lookaside[0] = block;
		return;
	}

	cgc_link( block );

	return;
}

void cgc_free( void *block )
{
	pmeta nb = NULL;

	if ( block ) {
		nb = (pmeta) (( (char*)block) - 4);
		cgc_link(nb);
	}

	return;
}

void cgc_init_freelist( void )
{
	pmeta zero_block = NULL;
	pmeta base_block = NULL;

	if ( cgc_allocate(4096, 0, (void**)&lookaside) != 0 ) {
		cgc_printf("[ERROR] Malloc fail terminate\n");
		cgc__terminate(-1);
	}

	cgc_bzero( lookaside[0], 4096);

	zero_block = lookaside[0];
	base_block = zero_block + 1;

	/// Keep a zero length head on the freelist for
	///	ease of organization
	zero_block->length = 0;
	zero_block->next = base_block;
	zero_block->prev = NULL;

	base_block->length = 4096 - sizeof(meta) - 4;
	base_block->prev = zero_block;
	base_block->next = NULL;

	//cgc_printf("Set up head: $x with walker: $d: $x\n", zero_block, base_block->length, base_block);

	return;
}

void cgc_unlink( pmeta block )
{
	if ( block == NULL ) {
		return;
	}

	if ( block->prev != NULL ) {
		block->prev->next = block->next;
	}

	if ( block->next != NULL ) {
		block->next->prev = block->prev;
	}

	return;
}

void *cgc_freelist_alloc( cgc_size_t length )
{
	pmeta walker = NULL;
	pmeta newone = NULL;

	/// If there isn't a block on the free list then initialize one
	/// This should only be the case on the first allocation request
	if ( lookaside[0] == NULL ) {
		cgc_init_freelist();
	}

	walker = (pmeta)lookaside[0];

	// Walk while looking for the smallest useable
	while ( walker ) {
		if ( walker->length < length ) {
			walker = walker->next;
		} else {
			break;
		}
	}

	if ( walker == NULL ) {
		//cgc_printf("no blocks found\n");
		cgc_add_freelist_block( length );
		return cgc_freelist_alloc(length);
	} else {
		//cgc_printf("foudn block size: $d\n", walker->length );

		cgc_unlink(walker);

		/// If the block is less than the size needed for at
		///	least an 8 byte block then return the whole thing
		///	That means sizeof(meta) prev and next total 8 bytes
		///	bytes on the lookaside list
		if ( walker->length - length < sizeof(meta) ) {
			/// Skip the 4 byte length
			return ((char*)walker) + 4;
		}

		/// Break the chunk off
		newone = (pmeta) ( ((char*)walker) + 4 + length );
		newone->length = walker->length - (length+4);

		//cgc_printf("Broke $d into $d and $d\n", walker->length, length, newone->length);
		walker->length = length;

		cgc_link(newone);

		//cgc_printf("Returning size: $d\n", walker->length);
		return ((char*)walker) + 4;
	}

	return NULL;
}


void *cgc_calloc( cgc_size_t length )
{
	void *out = cgc_malloc( length );

	if ( !out ) {
		return out;
	}

	length = (length+7) & 0xfffffff8;

	cgc_bzero( out, length);

	return out;
}

void *cgc_malloc( cgc_size_t length )
{
	int bucket = 0;
	pmeta outb = NULL;
	
	// The minimum size for a valid request is 8 bytes
	if ( length < 8 ) {
		length = 8;
	}

	// Round up to nearest 8
	length = (length+7) & 0xfffffff8;

	bucket = BUCKET(length);

	if ( bucket == 0 ) {
		return cgc_freelist_alloc( length );
	} else {
		while ( bucket < 128 ) {
			if ( lookaside[ bucket] != NULL ) {
				break;
			}

			bucket++;
		}
	}

	if ( bucket == 128 ) {
		//cgc_printf("No available buckets freelist alloc\n");
		return cgc_freelist_alloc( length );
	} else {
		//cgc_printf("Found bucket: $d\n", bucket);
		outb = lookaside[ bucket ];
		lookaside[bucket] = outb->next;

		return ( (char*)outb ) + 4;
	}

	return NULL;
}
