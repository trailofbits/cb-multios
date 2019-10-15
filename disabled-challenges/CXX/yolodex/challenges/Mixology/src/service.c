/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#define MAINFILE
#include "libcgc.h"
#include "cgc_libc.h"

#include "cgc_libmixology.h"



int main(int cgc_argc, char *cgc_argv[]) {
    int ret;
    cgc_size_t size;

    cgc_malloc_init();
    
    

    if (ret != 0)
        cgc__terminate(ret);



    char * welcome = "Welcome to the new chemical discovery service!";
    cgc_transmit_line_nl(welcome);
    while (1) {



        char * cmd_buf = cgc_calloc(1, MAX_LINE_SZ);
        if(cmd_buf != NULL){
            cgc_size_t line_sz = cgc_read_ascii_line(STDIN, cmd_buf, MAX_LINE_SZ);
            if(line_sz < 3){
                cgc_free(cmd_buf);
                continue;
            }
            
            int (*cmd_func)(char *);
            cmd_func = cgc_get_command_from_input(cmd_buf);
            // strtok with NULL has 2nd argument
            // first arg is at the head of cmd buf...


            if(cmd_func == NULL)
                cgc__terminate(10);
            // after tokenized
            int args_offset = cgc_strlen(cmd_buf);
            if(args_offset > MAX_LINE_SZ)
                cgc__terminate(14);

            int cmd_result = cmd_func(cmd_buf+args_offset+1);
            if(cmd_result != CMDOKAY){
                // terminate
                cgc__terminate(cmd_result);
            }

            cgc_free(cmd_buf);
        }else{
            continue;
        }



    }
    cgc__terminate(1);
}
