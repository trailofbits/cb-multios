/*

Author: Jason Williams <jdw@cromulence.com>

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
#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_exception_handler.h"
#include "cgc_command_handler.h"
#include "cgc_database.h"
#include "cgc_io.h"

// Maximum number of characters in the command buffer
#define COMMAND_BUFFER_MAX      (512)


void cgc_run_parser( void )
{
    uint8_t done = 0;
    uint8_t commandBuffer[COMMAND_BUFFER_MAX+1];
    int32_t iRetVal;
    tUserState userState;

    cgc_init_user( &userState );

    do
    {
        cgc_printf( "> " );

        iRetVal = cgc_readLine( STDIN, (char *)commandBuffer, COMMAND_BUFFER_MAX );

        if ( iRetVal == -1 )
        {
            cgc_printf( "Connection failed. Exiting.\n" );
            done = 1;
        }
        else
        {
            // Pares command, NULL terminated
            cgc_parse_command( commandBuffer, &userState );
        }

    } while ( !done );
}

void cgc_test( void )
{
    // Tests exception handler subroutines
    //
    cgc_printf( "Enter test function\n" );
    TRY
    {
        THROW(1);
    }
    CATCH( 1 )
    {
        cgc_printf( "Got 1\n" );
        THROW( 1 );
    }
    FINALLY
    {
        cgc_printf( "Blah\n" );
    }
    ETRY
    cgc_printf( "Exit test function\n" );
}

int main(int cgc_argc, char *cgc_argv[])
{
    // Initialize exception handler
    cgc_init_exception_handler();

    // Initialize the database
    cgc_init_database();

    // Run the main command line parser
    cgc_run_parser();

    return 0;
}
