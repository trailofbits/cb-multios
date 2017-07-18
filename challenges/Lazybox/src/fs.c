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
#include "cgc_stdint.h"
#include "cgc_fs.h"
#include "cgc_prng.h"
#include "cgc_shell.h"

Filesystem FS[MAX_FILES];
FILE FH[MAX_FILES];

extern environment cgc_ENV;

void cgc_InitFilesystem(void) {
	char root_passwd[32];
	char secure_passwd[32];
	uint8_t i;
        const char *rand_page = (const char *)0x4347C000;

	cgc_bzero(FS, sizeof(FS));
	cgc_bzero(FH, sizeof(FH));

	// generate a random root password
	cgc_bzero(root_passwd, 32);
	for (i = 0; i < 10; i++) {
		root_passwd[i] = (char)cgc_random_in_range(65,122);
	}
	root_passwd[i] = '\0';

	// generate a random secure user password
	cgc_bzero(secure_passwd, 32);
	for (i = 0; i < 31; i++) {
		secure_passwd[i] = (char)cgc_random_in_range(65,122);
	}
	secure_passwd[i] = '\0';

	// passwd file
	cgc_strcpy(FS[0].Filename, "passwd");
	cgc_strcpy(FS[0].Owner, "root");
	cgc_strcpy(FS[0].Group, "root");
	FS[0].Perms = 0x700;
	cgc_sprintf(FS[0].Data, "$s:secure:secure\ncrs:crs:crs\n$s:root:root", secure_passwd, root_passwd);
	FS[0].Size = cgc_strlen(FS[0].Data);

	// confidential data file
	cgc_strcpy(FS[1].Filename, "confidential");
	cgc_strcpy(FS[1].Owner, "secure");
	cgc_strcpy(FS[1].Group, "secure");
	FS[1].Perms = 0x700;
	// cgc_read starting at 4th byte since we already used the first 4 to seed the prng
	// but don't use any 4-byte chunks that have NULL's or newlines
	rand_page+=4;
	i = 0;
	while (i < 4) {
		if (*rand_page == '\0' || *rand_page == '\n') {
			i = 0;
			rand_page++;
			continue;
		}
		FS[1].Data[i++] = *rand_page;
		rand_page++;
	}
	FS[1].Size = 4;

}

void cgc_ListFiles(void) {
	uint8_t i;

	cgc_puts("Directory listing");
	cgc_printf("$-32s $-32s $-32s $5s\n\r", "Filename", "Owner", "Group", "Size");
	for (i = 0; i < MAX_FILES; i++) {
		if (FS[i].Filename[0] == '\0'){
			continue;
		}

		cgc_printf("$-32s $-32s $-32s $5d\n\r", FS[i].Filename, FS[i].Owner, FS[i].Group, FS[i].Size);
	}
}

uint16_t cgc_Mode2Perms(char *Mode) {
	uint16_t Perms = 0;

	if (Mode[0] == 'r')
		Perms |= PERMS_READ;
		
	if (Mode[0] == 'w')
		Perms |= PERMS_WRITE;

	return(Perms);
}
 
pFILE cgc_fopen(char *Filename, char *Mode, uint8_t Suid) {
	uint8_t i;
	uint16_t Perms;
	pFilesystem FirstAvailableFS = NULL;
	uint8_t inode;

	if (!Filename || !Mode) {
		return(NULL);
	}

	if (cgc_strlen(Filename) > 31) {
		return(NULL);
	}

	// make sure we only have 'r' or 'w' in Mode
	if (cgc_strlen(Mode) > 1) {
		return(NULL);
	}
	if (Mode[0] != 'r' && Mode[0] != 'w') {
		return(NULL);
	}

	// look for the requested file
	for (inode = 0; inode < MAX_FILES; inode++) {
		if (FS[inode].Filename[0] == '\0' && !FirstAvailableFS) {
			// found an availale file, keep track of it
			// in case we need it later
			FirstAvailableFS = &FS[inode];
		}

		if (cgc_strcmp(Filename, FS[inode].Filename) == 0) {
			break;
		}
	}
	if (inode == MAX_FILES) {
		if (Mode[0] == 'r') {
			return(NULL);
		} else {
			goto success;
		}
	}

	// if called from a 'setuid root' function
	if (Suid || !cgc_strcmp(cgc_ENV.User, "root")) {
		goto success;
	}

	// verify user permissions
	if (!cgc_strcmp(FS[inode].Owner, cgc_ENV.User)) {
		Perms = (FS[inode].Perms & 0xF00) >> 8;
		if ((Perms & cgc_Mode2Perms(Mode)) == 0) {
			return(NULL);
		} else {
			goto success;
		}
	}

	// verify group permissions
	if (!cgc_strcmp(FS[inode].Group, cgc_ENV.Group)) {
		Perms = (FS[inode].Perms & 0xF0) >> 4;
		if ((Perms & cgc_Mode2Perms(Mode)) == 0) {
			return(NULL);
		} else {
			goto success;
		}
	}
	
	// verify other permissions
	Perms = (FS[inode].Perms & 0xF);
	if ((Perms & cgc_Mode2Perms(Mode)) == 0) {
		return(NULL);
	} 

success:
	// Populate a new file handle and return it
	for (i = 0; i < MAX_FILES; i++) {
		if (FH[i].fp == NULL) {
			break;
		}
	}
	if (i == MAX_FILES) {
		// no available file handles
		return(NULL);
	}
	if (Mode[0] == 'w') {
		if (inode == MAX_FILES) { 
			if (!FirstAvailableFS) {
				// no available filesystem slots
				return(NULL);
			}
			// create a new file
			cgc_strcpy(FirstAvailableFS->Filename, Filename);
			cgc_strcpy(FirstAvailableFS->Owner, cgc_ENV.User);
			cgc_strcpy(FirstAvailableFS->Group, cgc_ENV.Group);
			FirstAvailableFS->Perms = 0x700;
			cgc_bzero(FirstAvailableFS->Data, MAX_FILE_SIZE);
			FirstAvailableFS->Size = 0;
			FH[i].fp = FirstAvailableFS;
			FH[i].mode = PERMS_WRITE;
		} else {
			// open the existing file
			FH[i].fp = &FS[inode];
			FH[i].mode = PERMS_WRITE;
			cgc_bzero(FH[i].fp->Data, MAX_FILE_SIZE);
			FH[i].fp->Size = 0;
		}
	} else {
		FH[i].fp = &FS[inode];
		FH[i].mode = PERMS_READ;
	}
	FH[i].CurrPosition = FH[i].fp->Data;

	return(&FH[i]);
}

char *cgc_fgets(char *str, uint32_t size, pFILE stream) {
	uint32_t i;

	if (!str || !stream || size == 0) {
		return(NULL);
	}

	if (stream->CurrPosition == NULL) {
		return(NULL);
	}

	if (*(stream->CurrPosition) == '\0') {
		return(NULL);
	}

	i = 0;
	while (*(stream->CurrPosition) != '\0' && size-1) {
		if (*(stream->CurrPosition) == '\n') {
			stream->CurrPosition++;
			str[i] = '\0';
			return(str);
		}
		str[i++] = *(stream->CurrPosition++);
		size--;
	}
	str[i] = '\0';
	return(str);
}

uint8_t cgc_fclose(pFILE stream) {

	if (!stream) {
		return(0);
	}

	stream->fp = NULL;
	stream->CurrPosition = NULL;

	return(1);

}

cgc_size_t cgc_fread(void *restrict ptr, cgc_size_t size, cgc_size_t nitems, FILE *restrict stream) {

	if (!ptr || !stream || size == 0 || nitems == 0) {
		return(0);
	}

	if (stream->fp == NULL || stream->CurrPosition == NULL || size*nitems > MAX_FILE_SIZE) {
		return(0);
	}

	if (size*nitems > stream->fp->Size) {
		cgc_memcpy(ptr, stream->fp->Data, stream->fp->Size);
		return(stream->fp->Size);
	} else {
		cgc_memcpy(ptr, stream->fp->Data, size*nitems);
		return(size*nitems);
	}

}	

cgc_size_t cgc_fwrite(const void *restrict ptr, cgc_size_t size, cgc_size_t nitems, FILE *restrict stream) {

	if (!ptr || !stream) {
		return(0);
	}

	if (stream->fp == NULL || stream->CurrPosition == NULL || size*nitems > MAX_FILE_SIZE || stream->mode != PERMS_WRITE) {
		return(0);
	}

	cgc_memcpy(stream->CurrPosition, ptr, size*nitems);
	stream->fp->Size += size*nitems;

	return(size*nitems);

}

uint8_t cgc_Dump(char *filename) {
	FILE *stream;
	char buf[1024];

	if (!filename) {
		return(0);
	}

	if ((stream = cgc_fopen(filename, "r", 0)) == NULL) {
		cgc_printf("Unable to open file '$s'\n\r", filename);
		return(0);
	}

	while (cgc_fgets(buf, 1024, stream)) {
		cgc_puts(buf);
	}

	cgc_fclose(stream);

	return(1);

}	
