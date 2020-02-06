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

#include "cgc_service.h"

pfile cgc_root = NULL;

void cgc_service_loop( void )
{
	int command = 0;
    pfile nf = NULL;
    
    /// Create the root file
    cgc_root = cgc_init_file();
    
    if ( cgc_root == NULL ) {
        cgc_printf("[ERROR] Failed to create the root node\n");
        return;
    }
    
    cgc_set_type( cgc_root, DIR );
    cgc_set_name( cgc_root, "/");
    
	while (1) {
		if ( cgc_recv( (char*)&command, 4 ) != 4 ) {
			// Failed to receive send error
			cgc_printf("[ERROR] Receive failed\n");
            return;
		}

		switch ( command ) {
			/// SEND
			case 0x444e4553:
				if ( cgc_handle_send( ) == 0 ) {
                    continue;
                }
                
				break;
            /// NDIR
            case 0x5249444e:
                if ( cgc_handle_ndir( ) == 0 ) {
                    continue;
                }
                
                break;
            /// RECV
			case 0x56434552:
                if ( cgc_handle_recv() == 0 ) {
                    continue;
                }
                
				break;
            /// STOP
            case 0x504f5453:
                cgc_printf("[INFO] Terminating\n");
                cgc__terminate(0);
                break;
            /// PRNT
			case 0x544e5250:
                cgc_printf("[INFO] Listing files\n");
                
                cgc_handle_prnt( cgc_root, "" );
                
				break;
            /// REPO
            case 0x4f504552:
                cgc_handle_repo( );
                break;
			default:
				cgc_printf("[ERROR] Invalid command: $x\n", command);
				break;
		};
	}

	return;
}


int main(int cgc_argc, char *cgc_argv[])
{
	cgc_service_loop();

    return 0;
}
