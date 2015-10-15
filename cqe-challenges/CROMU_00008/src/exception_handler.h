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
#ifndef __EXCEPTION_HANDLER_H__
#define __EXCEPTION_HANDLER_H__

#include <libcgc.h>
#include <stdint.h>
// Implement an exception handler with setjmp/longjmp

#define MAX_EXCEPTION_NAME      (64)
#define MAX_EXCEPTION_EXTRA     (128)

typedef struct EXCEPTION_DATA_STRUCT
{
    uint8_t exceptionNumber;
    char szExceptionName[MAX_EXCEPTION_NAME];
    char szExceptionExtra[MAX_EXCEPTION_EXTRA];
} tExceptionData;

typedef struct EXCEPTION_FRAME_STRUCT
{
    jmp_buf jmpBuffer;
} tExceptionFrame;

#define TRY         switch( setjmp( get_next_exception_frame()->jmpBuffer ) ) { case 0: while(1) {
#define CATCH(e)    break; case e:
#define THROW(e)    longjmp( get_current_exception_frame()->jmpBuffer, e )
#define FINALLY   break; } default:
#define ETRY      pop_exception_frame(); }

void init_exception_handler( void );
tExceptionFrame *get_next_exception_frame( void );
tExceptionFrame *get_current_exception_frame( void );
tExceptionFrame *pop_exception_frame( void );

#endif // __EXCEPTION_HANDLER_H__
