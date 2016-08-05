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
#include <libcgc.h>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "stdint.h"
#include "fs.h"
#include "prng.h"
#include "shell.h"

Filesystem FS[MAX_FILES];
FILE FH[MAX_FILES];

extern environment ENV;

void InitFilesystem(void) {
	char root_passwd[32];
	char secure_passwd[32];
	uint8_t i;
        const char *rand_page = (const char *)0x4347C000;

	bzero(FS, sizeof(FS));
	bzero(FH, sizeof(FH));

	// generate a random root password
	bzero(root_passwd, 32);
	for (i = 0; i < 10; i++) {
		root_passwd[i] = (char)random_in_range(65,122);
	}
	root_passwd[i] = '\0';

	// generate a random secure user password
	bzero(secure_passwd, 32);
	for (i = 0; i < 31; i++) {
		secure_passwd[i] = (char)random_in_range(65,122);
	}
	secure_passwd[i] = '\0';

	// passwd file
	strcpy(FS[0].Filename, "passwd");
	strcpy(FS[0].Owner, "root");
	strcpy(FS[0].Group, "root");
	FS[0].Perms = 0x700;
	sprintf(FS[0].Data, "$s:secure:secure\ncrs:crs:crs\n$s:root:root", secure_passwd, root_passwd);
	FS[0].Size = strlen(FS[0].Data);

	// confidential data file
	strcpy(FS[1].Filename, "confidential");
	strcpy(FS[1].Owner, "secure");
	strcpy(FS[1].Group, "secure");
	FS[1].Perms = 0x700;
	// read starting at 4th byte since we already used the first 4 to seed the prng
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

void ListFiles(void) {
	uint8_t i;

	puts("Directory listing");
	printf("$-32s $-32s $-32s $5s\n\r", "Filename", "Owner", "Group", "Size");
	for (i = 0; i < MAX_FILES; i++) {
		if (FS[i].Filename[0] == '\0'){
			continue;
		}

		printf("$-32s $-32s $-32s $5d\n\r", FS[i].Filename, FS[i].Owner, FS[i].Group, FS[i].Size);
	}
}

uint16_t Mode2Perms(char *Mode) {
	uint16_t Perms = 0;

	if (Mode[0] == 'r')
		Perms |= PERMS_READ;
		
	if (Mode[0] == 'w')
		Perms |= PERMS_WRITE;

	return(Perms);
}
 
pFILE fopen(char *Filename, char *Mode, uint8_t Suid) {
	uint8_t i;
	uint16_t Perms;
	pFilesystem FirstAvailableFS = NULL;
	uint8_t inode;

	if (!Filename || !Mode) {
		return(NULL);
	}

	if (strlen(Filename) > 31) {
		return(NULL);
	}

	// make sure we only have 'r' or 'w' in Mode
	if (strlen(Mode) > 1) {
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

		if (strcmp(Filename, FS[inode].Filename) == 0) {
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
	if (Suid || !strcmp(ENV.User, "root")) {
		goto success;
	}

	// verify user permissions
	if (!strcmp(FS[inode].Owner, ENV.User)) {
		Perms = (FS[inode].Perms & 0xF00) >> 8;
		if ((Perms & Mode2Perms(Mode)) == 0) {
			return(NULL);
		} else {
			goto success;
		}
	}

	// verify group permissions
	if (!strcmp(FS[inode].Group, ENV.Group)) {
		Perms = (FS[inode].Perms & 0xF0) >> 4;
		if ((Perms & Mode2Perms(Mode)) == 0) {
			return(NULL);
		} else {
			goto success;
		}
	}
	
	// verify other permissions
	Perms = (FS[inode].Perms & 0xF);
	if ((Perms & Mode2Perms(Mode)) == 0) {
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
			strcpy(FirstAvailableFS->Filename, Filename);
			strcpy(FirstAvailableFS->Owner, ENV.User);
			strcpy(FirstAvailableFS->Group, ENV.Group);
			FirstAvailableFS->Perms = 0x700;
			bzero(FirstAvailableFS->Data, MAX_FILE_SIZE);
			FirstAvailableFS->Size = 0;
			FH[i].fp = FirstAvailableFS;
			FH[i].mode = PERMS_WRITE;
		} else {
			// open the existing file
			FH[i].fp = &FS[inode];
			FH[i].mode = PERMS_WRITE;
			bzero(FH[i].fp->Data, MAX_FILE_SIZE);
			FH[i].fp->Size = 0;
		}
	} else {
		FH[i].fp = &FS[inode];
		FH[i].mode = PERMS_READ;
	}
	FH[i].CurrPosition = FH[i].fp->Data;

	return(&FH[i]);
}

char *fgets(char *str, uint32_t size, pFILE stream) {
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

uint8_t fclose(pFILE stream) {

	if (!stream) {
		return(0);
	}

	stream->fp = NULL;
	stream->CurrPosition = NULL;

	return(1);

}

size_t fread(void *restrict ptr, size_t size, size_t nitems, FILE *restrict stream) {

	if (!ptr || !stream || size == 0 || nitems == 0) {
		return(0);
	}

	if (stream->fp == NULL || stream->CurrPosition == NULL || size*nitems > MAX_FILE_SIZE) {
		return(0);
	}

	if (size*nitems > stream->fp->Size) {
		memcpy(ptr, stream->fp->Data, stream->fp->Size);
		return(stream->fp->Size);
	} else {
		memcpy(ptr, stream->fp->Data, size*nitems);
		return(size*nitems);
	}

}	

size_t fwrite(const void *restrict ptr, size_t size, size_t nitems, FILE *restrict stream) {

	if (!ptr || !stream) {
		return(0);
	}

	if (stream->fp == NULL || stream->CurrPosition == NULL || size*nitems > MAX_FILE_SIZE || stream->mode != PERMS_WRITE) {
		return(0);
	}

	memcpy(stream->CurrPosition, ptr, size*nitems);
	stream->fp->Size += size*nitems;

	return(size*nitems);

}

uint8_t Dump(char *filename) {
	FILE *stream;
	char buf[1024];

	if (!filename) {
		return(0);
	}

	if ((stream = fopen(filename, "r", 0)) == NULL) {
		printf("Unable to open file '$s'\n\r", filename);
		return(0);
	}

	while (fgets(buf, 1024, stream)) {
		puts(buf);
	}

	fclose(stream);

	return(1);

}	
