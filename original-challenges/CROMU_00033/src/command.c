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

#include "commands.h"

int handle_repo( )
{
    int length = 0;
    char name[256];
    
    if ( recv((char*)&length, 1) == 0 ) {
        return 0;
    }
   
    memset(name, 0, 256);
    
    if ( recv(name, length) == 0 ) {
        return 0;
    }
    
    return delete_file( name );
}

void handle_prnt( pfile base, char *st )
{
    int index = 0;
    pfile *list = NULL;
    char nm[256];
    pfile t = NULL;
    
    if ( base == NULL ) {
        return;
    }
    
    bubble_sort( base );
    
    list = (pfile*)base->data;
    
    for ( index = 0; index < base->length; index ++ ) {
        t = list[index];
        
        printf("$s/$s     ", st, t->name  );
        if ( t->type == FILE ) {
            printf("File     $d\n", t->length);
        } else {
            printf("Dir\n");
            
            memset(nm, 0, 256);
            
            strncpy( nm, st, 255 );
            strncat( nm, "/", 255);
            strncat( nm, t->name, 255);
            handle_prnt( t, nm );
        }
        
    }
    return;
}

int handle_recv( void )
{
  	int name_length = 0;
	char name[256];
	pfile fd = NULL;
    
	memset(name, 0, 256);
    
	if ( recv( (char*)&name_length, 1 ) == 0 ) {
		/// Send an error
		printf("[ERROR] Failed to recv\n");
		return 0;
	}
    
	if ( recv( name, name_length) == 0 ) {
		printf("[ERROR] Failed to recv name\n");
		return 0;
	}
    
    fd = get_file( name );
    
    if ( fd == NULL ) {
        printf("[ERROR] RECV failed\n");
        return 0;
    }
    
    if ( fd->type == DIR ) {
        printf("[ERROR] $s is a directory\n", fd->name);
        return 0;
    }
    
    if ( fd->data == NULL ) {
        return 0;
    }
    
    printf("[DATA] $s\n", fd->data);
    
    return 1;
}

int handle_ndir( void )
{
 	int name_length = 0;
	char name[256];
	pfile new_dir = NULL;
	
	memset(name, 0, 256);
    
	if ( recv( (char*)&name_length, 1 ) == 0 ) {
		/// Send an error
		printf("[ERROR] Failed to recv\n");
		return 0;
	}
    
	if ( recv( name, name_length) == 0 ) {
		printf("[ERROR] Failed to recv name\n");
		return 0;
	}
    
    new_dir = init_file();
    
    if ( new_dir == NULL ) {
        printf("[ERROR] Failed to initialize a new directory\n");
        return 0;
    }
    
    if ( set_name( new_dir, name ) == 0) {
        printf("[ERROR] Failed to set directory name\n");
        free(new_dir);
        return 0;
    }
    
    if ( set_type( new_dir, DIR) == 0 ) {
        printf("[ERROR] Failed to set type\n");
        free(new_dir);
        return 0;
    }
    
    if ( add_file( new_dir ) == 0 ) {
        printf("[ERROR] NDIR failed\n");
        free(new_dir);
        return 0;
    }
    
    printf("[INFO] Added new directory\n");
    
    return 1;
}

int handle_send( void )
{
	int name_length = 0;
	int file_length = 0;
	char name[256];
	char *data = NULL;
	pfile new_file = NULL;
	
	memset(name, 0, 256);

	if ( recv( (char*)&name_length, 1 ) == 0 ) {
		/// Send an error
		printf("[ERROR] Failed to recv\n");
		return 0;
	}

	if ( recv( name, name_length) == 0 ) {
		printf("[ERROR] Failed to recv name\n");
		return 0;
	}

	if ( recv( (char*)&file_length, 2 ) == 0 ) {
		printf("[ERROR] Failed to recv file length\n");
		return 0;
	}

	/// Maximum length that can be received is 0x400
    if (file_length > 0x400) {
        printf("[ERROR] Maximum file length is 0x400\n");
        return 0;
    }
    
    data = malloc( file_length + 1);
    
    if ( data == NULL ) {
        printf("[ERROR] malloc failed\n");
        return 0;
    }
    
    memset( data, 0, file_length + 1);
    
    if ( recv( data, file_length ) == 0 ) {
        printf("[ERROR] Failed to recv data\n");
        return 0;
    }

    new_file = init_file();
    
    if ( new_file == NULL ) {
        printf("[ERROR] Failed to initialize a new file\n");
        free(data);
        return 0;
    }
    
    if ( set_name( new_file, name ) == 0) {
        printf("[ERROR] Failed to set file name\n");
        free(data);
        free(new_file);
        return 0;
    }
    
    if ( set_type( new_file, FILE) == 0 ) {
        printf("[ERROR] Failed to set type\n");
        free(data);
        free(new_file);
        return 0;
    }
    
    if ( set_data( new_file, file_length, data) == 0) {
        printf("[ERROR] Failed to set data\n");
        free(data);
        free(new_file);
        return 0;
    }
    
    /// Free the data since set_data() allocates a new copy
    free(data);
    
    if ( add_file( new_file) == 0 ) {
        printf("[ERROR] SEND failed\n");
        free_file(new_file);
        return 0;
    }
    
    printf("[INFO] File received: $s\n", name);
    
    return 1;
}
