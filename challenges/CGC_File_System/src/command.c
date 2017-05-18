/*
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

#include "cgc_commands.h"

int cgc_handle_repo( )
{
    int length = 0;
    char name[256];
    
    if ( cgc_recv((char*)&length, 1) == 0 ) {
        return 0;
    }
   
    cgc_memset(name, 0, 256);
    
    if ( cgc_recv(name, length) == 0 ) {
        return 0;
    }
    
    return cgc_delete_file( name );
}

void cgc_handle_prnt( pfile base, char *st )
{
    int index = 0;
    pfile *list = NULL;
    char nm[256];
    pfile t = NULL;
    
    if ( base == NULL ) {
        return;
    }
    
    cgc_bubble_sort( base );
    
    list = (pfile*)base->data;
    
    for ( index = 0; index < base->length; index ++ ) {
        t = list[index];
        
        cgc_printf("$s/$s     ", st, t->name  );
        if ( t->type == FILE ) {
            cgc_printf("File     $d\n", t->length);
        } else {
            cgc_printf("Dir\n");
            
            cgc_memset(nm, 0, 256);
            
            cgc_strncpy( nm, st, 255 );
            cgc_strncat( nm, "/", 255);
            cgc_strncat( nm, t->name, 255);
            cgc_handle_prnt( t, nm );
        }
        
    }
    return;
}

int cgc_handle_recv( void )
{
  	int name_length = 0;
	char name[256];
	pfile fd = NULL;
    
	cgc_memset(name, 0, 256);
    
	if ( cgc_recv( (char*)&name_length, 1 ) == 0 ) {
		/// Send an error
		cgc_printf("[ERROR] Failed to recv\n");
		return 0;
	}
    
	if ( cgc_recv( name, name_length) == 0 ) {
		cgc_printf("[ERROR] Failed to recv name\n");
		return 0;
	}
    
    fd = cgc_get_file( name );
    
    if ( fd == NULL ) {
        cgc_printf("[ERROR] RECV failed\n");
        return 0;
    }
    
    if ( fd->type == DIR ) {
        cgc_printf("[ERROR] $s is a directory\n", fd->name);
        return 0;
    }
    
    if ( fd->data == NULL ) {
        return 0;
    }
    
    cgc_printf("[DATA] $s\n", fd->data);
    
    return 1;
}

int cgc_handle_ndir( void )
{
 	int name_length = 0;
	char name[256];
	pfile new_dir = NULL;
	
	cgc_memset(name, 0, 256);
    
	if ( cgc_recv( (char*)&name_length, 1 ) == 0 ) {
		/// Send an error
		cgc_printf("[ERROR] Failed to recv\n");
		return 0;
	}
    
	if ( cgc_recv( name, name_length) == 0 ) {
		cgc_printf("[ERROR] Failed to recv name\n");
		return 0;
	}
    
    new_dir = cgc_init_file();
    
    if ( new_dir == NULL ) {
        cgc_printf("[ERROR] Failed to initialize a new directory\n");
        return 0;
    }
    
    if ( cgc_set_name( new_dir, name ) == 0) {
        cgc_printf("[ERROR] Failed to set directory name\n");
        cgc_free(new_dir);
        return 0;
    }
    
    if ( cgc_set_type( new_dir, DIR) == 0 ) {
        cgc_printf("[ERROR] Failed to set type\n");
        cgc_free(new_dir);
        return 0;
    }
    
    if ( cgc_add_file( new_dir ) == 0 ) {
        cgc_printf("[ERROR] NDIR failed\n");
        cgc_free(new_dir);
        return 0;
    }
    
    cgc_printf("[INFO] Added new directory\n");
    
    return 1;
}

int cgc_handle_send( void )
{
	int name_length = 0;
	int file_length = 0;
	char name[256];
	char *data = NULL;
	pfile new_file = NULL;
	
	cgc_memset(name, 0, 256);

	if ( cgc_recv( (char*)&name_length, 1 ) == 0 ) {
		/// Send an error
		cgc_printf("[ERROR] Failed to recv\n");
		return 0;
	}

	if ( cgc_recv( name, name_length) == 0 ) {
		cgc_printf("[ERROR] Failed to recv name\n");
		return 0;
	}

	if ( cgc_recv( (char*)&file_length, 2 ) == 0 ) {
		cgc_printf("[ERROR] Failed to recv file length\n");
		return 0;
	}

	/// Maximum length that can be received is 0x400
    if (file_length > 0x400) {
        cgc_printf("[ERROR] Maximum file length is 0x400\n");
        return 0;
    }
    
    data = cgc_malloc( file_length + 1);
    
    if ( data == NULL ) {
        cgc_printf("[ERROR] malloc failed\n");
        return 0;
    }
    
    cgc_memset( data, 0, file_length + 1);
    
    if ( cgc_recv( data, file_length ) == 0 ) {
        cgc_printf("[ERROR] Failed to recv data\n");
        return 0;
    }

    new_file = cgc_init_file();
    
    if ( new_file == NULL ) {
        cgc_printf("[ERROR] Failed to initialize a new file\n");
        cgc_free(data);
        return 0;
    }
    
    if ( cgc_set_name( new_file, name ) == 0) {
        cgc_printf("[ERROR] Failed to set file name\n");
        cgc_free(data);
        cgc_free(new_file);
        return 0;
    }
    
    if ( cgc_set_type( new_file, FILE) == 0 ) {
        cgc_printf("[ERROR] Failed to set type\n");
        cgc_free(data);
        cgc_free(new_file);
        return 0;
    }
    
    if ( cgc_set_data( new_file, file_length, data) == 0) {
        cgc_printf("[ERROR] Failed to set data\n");
        cgc_free(data);
        cgc_free(new_file);
        return 0;
    }
    
    /// Free the data since set_data() allocates a new copy
    cgc_free(data);
    
    if ( cgc_add_file( new_file) == 0 ) {
        cgc_printf("[ERROR] SEND failed\n");
        cgc_free_file(new_file);
        return 0;
    }
    
    cgc_printf("[INFO] File received: $s\n", name);
    
    return 1;
}
