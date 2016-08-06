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

#include "common.h"

extern "C"
{
// Add external commands here (if they are in .c files)
extern void sort_command( char * );
extern void matrix_command( char * );
extern void simon_command( char *);
extern void encode_command( char * );

}

int main(void)
{
    CCommandHandler oCmdHandler;

    // Make sure to register your command with the command handler and add a description...
    oCmdHandler.RegisterCommand( "sort", "This command sorts integers.", &sort_command );
    oCmdHandler.RegisterCommand( "matrix", "This command performs matrix math.", &matrix_command );
    oCmdHandler.RegisterCommand( "simon", "This command plays a game like Simon Says.", &simon_command );
    oCmdHandler.RegisterCommand( "encode", "This command encodes data.", &encode_command );

    oCmdHandler.Run();

    return 0;
}
