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
#pragma once

// cb_id is the ID of the cb that owns the pipe containing the resulting fd
#define IPC_READ_FD(cb_id) 		(((cb_id * 2) + 3) + 1)
#define IPC_WRITE_FD(cb_id) 	((cb_id * 2) + 3)

/*
in graphic form...

ID	    0	1	2	3	4
__________________________________________
cgc_read	4	6	8	10	12
cgc_write	3	5	7	9	11

As an example

cb_1 has ID 0
cb_2 has ID 1
cb_3 has ID 2

cb_1 sends to cb_2 on fd 5, cb_2 reads that data on fd 6
cb_2 sends to cb_1 on fd 3, cb_1 reads that data on fd 4
cb_1 sends to cb_3 on fd 7, cb_3 reads that data on fd 8
cb_3 sends to cb_1 on fd 3, cb_1 reads that data on fd 4
etc..
*/
