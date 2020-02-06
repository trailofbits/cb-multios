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
#include "cgc_exception_handler.h"
#include "cgc_mem_global.h"

extern tGlobalMemoryLayout cgc_g_memoryGlobal;

uint8_t cgc_g_exceptionFrameCur = 0;

void cgc_init_exception_handler( void )
{
    uint32_t i;

    // Reset the stack position
    cgc_g_exceptionFrameCur = 0;

    // Set the mem_resrve section to nulls
    for ( i = 0; i < MEM_RESERVE_SIZE; i++ )
        cgc_g_memoryGlobal.mem_reserve[i] = 0;
}

tExceptionFrame *cgc_get_next_exception_frame( void )
{
    tExceptionFrame *pCur;

    if ( cgc_g_exceptionFrameCur < MAX_EXCEPTION_FRAME_SIZE )
        pCur = (&cgc_g_memoryGlobal.exceptionFrameList[cgc_g_exceptionFrameCur++]);
    else
        pCur = NULL;

    // Return the newly allocated object
    return (pCur);
}

tExceptionFrame *cgc_get_current_exception_frame( void )
{
    tExceptionFrame *pCur;

    if ( cgc_g_exceptionFrameCur > 0 )
        pCur = (&cgc_g_memoryGlobal.exceptionFrameList[cgc_g_exceptionFrameCur-1]);
    else
        pCur = NULL;

    return (pCur);
}

tExceptionFrame *cgc_pop_exception_frame( void )
{
    tExceptionFrame *pCur;

    if ( cgc_g_exceptionFrameCur > 0 )
    {
        cgc_g_exceptionFrameCur--;
        pCur = (&cgc_g_memoryGlobal.exceptionFrameList[cgc_g_exceptionFrameCur]);
    }
    else
        pCur = NULL;

    return (pCur);
}
