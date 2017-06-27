/*

Author: Joe Rogers <joe@cromulence.com>

Copyright (c) 2015 Cromulence LLC

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
#include "cgc_stdio.h"
#include "cgc_string.h"
#include "cgc_fs.h"
#include "cgc_proto.h"
#include "cgc_prng.h"

int main(int cgc_argc, char *cgc_argv[]) {
        uint32_t MaxFiles = 10;
	pRequest pReq;
	pResponse pResp;
	const char *rand_page = (const char *)0x4347C000;
	char user_password[11];
	uint32_t i;

	// init the filesystem
        if (!cgc_InitFilesystem(MaxFiles, "rootpasswd")) {
                cgc_puts(cgc_FsError());
                cgc__terminate(0);
        }

	// init the prng
	cgc_seed_prng(*(unsigned int *)rand_page);

	// generate a random user password
	cgc_bzero(user_password, 11);
	for (i = 0; i < 10; i++) {
		user_password[i] = (char)cgc_random_in_range(65,122);
	}

	// Add the random user
	if (!cgc_AddUser("user", user_password)) {
		cgc__terminate(0);
	}

	// loop receiving packets
	while (1) {
		// Receive the packet
		if ((pReq = cgc_ReceiveRequest()) == NULL) {
			continue;
		}

		// Handle the request
		if ((pResp = cgc_HandleRequest(pReq)) == NULL) {
			cgc_FreeRequest(pReq);
			continue;
		}

		// Send the response
		cgc_SendResponse(pResp);

		// Free the Request and Response
		cgc_FreeRequest(pReq);
		cgc_FreeResponse(pResp);

	}

	// all done
        DestroyFilesystem();
	return(0);
}
