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


#ifndef OPERATION_H
#define OPERATION_H 1

#define ALLOC(sz,p) if (SUCCESS != allocate(sz, 0, (void **)p)) {_terminate(ERRNO_ALLOC);}
#define DEALLOC(p, sz) if(SUCCESS != deallocate((void *)p, sz)) {_terminate(ERRNO_ALLOC);}


#define RECV(v,s) if(s != recv_all((char *)v, s)) {_terminate(ERR_RECV_FAILED);}
#define SENDSI(v) send((char *)&v, sizeof(int32_t))
#define SENDUI(v) send((char *)&v, sizeof(uint32_t))

#define INIT_HAIKU_ID 424242
#define MAX_HAIKU_LINE_LEN 1362 // 3 * 1362 == 4086
#define MAX_HAIKU_LEN 4087 // 4096 - sizeof(struct haiku) - 1

#define EGG_ID 31337
#define EGG_HAIKU " from within HIGHCOO\x07 new Haiku every login\x07 a warm thought engulfs\x07"

struct haiku {
	uint32_t id;
	uint32_t length;
	char content[];
};

enum {
	ERR_RECV_FAILED = -911,
	ERR_RAND_FAILED = -912,
	ERR_INVALID_CMD = -999,
	ERR_LIST_EMPTY = -1111,
	ERR_LIST_NOT_EXIST = -2222,
	ERR_EMPTY_NODE = -2345,
	ERR_INVALID_ID = -3456,
	ERR_INVALID_HAIKU_LEN = -4567,
	ERR_INVALID_HAIKU = -4568,
};

extern int add_haiku();
extern int get_haiku_by_id();
extern int get_haiku_random();
extern int get_haiku_count();
extern int get_haiku_ids();

#endif