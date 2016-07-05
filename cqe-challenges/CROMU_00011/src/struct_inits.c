/*

Author: John Berry <john.n.berry@gmail.com>

Copyright (c) 2014 Cromulence LLC

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

#include "struct_inits.h"

void print_set( psetArray psa )
{
	int index = 0;

	if ( psa == NULL ) {
		goto end;
	}

	printf("@s = |", psa->varName);

	while ( index < psa->varCount ) {
		if (psa->sElems[index]->type == SET ) {
			printf("@s", psa->sElems[index]->value);
		} else {
			printf("\"@s\"", psa->sElems[index]->value);
		}
		index++;
		if ( index != psa->varCount ) {
			printf(",");
		}
	}

	printf("|\n");
end:
	return;
}

/**
 * Frees the necessary fields within an element as well as the element itself
 * @param element Pointer to the element to be freed
 **/
void free_element( psetElement element )
{
	if ( element == NULL ) {
		goto end;
	}

	deallocate( element->value, strlen( element->value) + 1 );
	deallocate( element, sizeof(setElement) );

end:
	return;
}

/**
 * Copies the provided structure though the next, prev and varName values are zeroed
 * @param Pointer to the set to be copied
 * @return Returns a copy of the supplied set or NULL on failure
 **/
psetArray copy_set( psetArray set )
{
	psetArray copy = NULL;
	int index = 0;

	if ( set == NULL ) {
		goto end;
	}

	if ( allocate( sizeof(setArray), 0, (void**)&copy) != 0 ) {
		copy = NULL;
		goto end;
	}

	bzero( copy, sizeof(setArray));

	while ( index < set->varCount ) {
		if (add_element_to_set( copy, copy_element( set->sElems[index]) ) != 0 ) {
			free_set_array( copy );
			copy = NULL;
			goto end;
		}
		index++;
	}

end:
	return copy;
}

/**
 * Frees a setArray structure and its sub structs
 * @param psa Pointer to a setArray structure
 * @return Nothing
 **/
void free_set_array( psetArray psa )
{
	int index = 0;

	if ( psa == NULL ) {
		goto end;
	}

	for ( index = 0; index < psa->varCount; index++){
		deallocate( psa->sElems[index]->value, strlen(psa->sElems[index]->value) + 1 );
		deallocate( psa->sElems[index], sizeof( setElement) );
		psa->sElems[index] = NULL;
	}

	deallocate( psa, sizeof(setArray));
	psa = NULL;

end:
	return;
}

/**
 * Returns a copy of an element
 * @param element Element to copy
 * @return Copy of the element argument
 **/
psetElement copy_element( psetElement element )
{
	psetElement copy = NULL;
	int vlen = 0;

	if ( element == NULL ) {
		goto end;
	}

	if ( allocate( sizeof(psetElement), 0, (void**)&copy) != 0 ) {
		copy = NULL;
		goto end;
	}

	vlen = strlen( element->value ) + 1;

	if ( allocate( vlen, 0, (void**)&copy->value) != 0 ) {
		deallocate( copy, sizeof(psetElement) );
		copy = NULL;
		goto end;
	}

	bzero( copy->value, vlen );
	memcpy( copy->value, element->value, vlen-1 );
	copy->type = element->type;

end:
	return copy;
}

/**
 * Checks if an element is in a set
 * @param set Set to check
 * @param element Element to check for
 * @return 1 if exists 0 if not, -1 on error
 **/
int element_in_set( psetArray set, psetElement element )
{
	int retval = -1;
	int vlen = 0;
	int nlen = 0;
	int index = 0;

	if ( set == NULL ) {
		goto end;
	}

	if ( element == NULL ) {
		goto end;
	}

	while ( index < set->varCount ) {
		if ( strcmp( element->value, set->sElems[index]->value) == 0 ) {
			if ( element->type == set->sElems[index]->type ) {
				retval = 1;
				goto end;
			}
		}
		index++;
	}

	retval = 0;
end:
	return retval;
}

/**
 * Adds a new element to a set
 * @param psa Set to add the element to
 * @param pse Element to be added to the set
 * @return 0 on success nonzero on failure
 **/
int add_element_to_set( psetArray psa, psetElement pse )
{
	int retval = 1;

	if ( psa == NULL || pse == NULL ) {
		goto end;
	}

	/// Maximum of 15 elements
	if ( psa->varCount >= 15 ) {
		goto end;
	}

	psa->sElems[ psa->varCount ] = pse;
	psa->varCount++;

	retval = 0;
end:
	return retval;
}

/**
 * Creates a new set element
 * @param value Pointer to the value name
 * @param type Type value either 0 or 1
 * @return Returns a pointer to a new set element or null on failure
 **/
psetElement create_element( char* value, int type )
{
        psetElement pse = NULL;
        int vlen = 0;

        if ( value == NULL ) {
                goto end;
        }

        if ( type != SET && type != VALUE ) {
                goto end;
        }

        if ( allocate( sizeof(setElement), 0, (void**)&pse) != 0 ) {
                pse = NULL;
                goto end;
        }

        vlen = strlen(value);

        if ( allocate( vlen + 1, 0, (void**)&(pse->value)) != 0 ) {
                deallocate( pse, sizeof(setElement) );
                pse = NULL;
                goto end;
        }

        memcpy( pse->value, value, vlen );

        pse->value[vlen] = 0x00;
        pse->type = type;

end:
        return pse;
}
