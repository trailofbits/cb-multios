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

#include <sys/mman.h>
#include "libcgc.h"

// lame so we don't have to include over-riding .h files
#define MAP_ANONYMOUS 0x20
#define MAP_PRIVATE 0x02
// #define PROT_READ 0x01
// #define PROT_WRITE 0x02

#define _SC_PAGESIZE 4096
// todo prot_exec

void _terminate(unsigned int status){
	_exit(status);
}

int transmit(int fd, const void *buf, size_t count, size_t *tx_bytes){
	ssize_t txb = write(fd, buf, count);
	if(txb < 0)
		return EFAULT;
	*tx_bytes = (size_t) txb;

	
	return 0;
}

int receive(int fd, void *buf, size_t count, size_t *rx_bytes){
	ssize_t s = read(fd, buf, count);
	if(s < 0)
		return EFAULT;
	*rx_bytes = (size_t) s;
	return 0;
}


int allocate(size_t length, int is_X, void **addr){
	size_t ps = _SC_PAGESIZE;
	if(length % ps != 0)
		length += (ps - (length % ps));


	void *c = mmap(NULL, length, PROT_READ | PROT_WRITE,  MAP_ANONYMOUS|MAP_PRIVATE, -1, NULL);
	
	if(c != NULL && c != (void *) -1){
		*addr = c;
		return 0;
	}
	// todo see if we can bring errno in ex = errno
	int ex = EFAULT;
	return ex;

}

int deallocate(void *addr, size_t length){
	// warning! length not used!

	size_t ps = _SC_PAGESIZE;//sysconf(_SC_PAGESIZE);
	if(length % ps != 0)
		length += (ps - (length % ps));



	return munmap(addr, length);
}

// int random(void *buf, size_t count, size_t *rnd_bytes){
// 	size_t read_sz = 0;
// 	// 0x00 is for rdonly
// 	int rndfd = open("/dev/urandom", 0x00);
	
// 	ssize_t res = read(rndfd, (char *) buf, count);
// 	if(res < 0)
// 		return EFAULT;
// 	*rnd_bytes = (size_t) res;
// 	return 0;

// }