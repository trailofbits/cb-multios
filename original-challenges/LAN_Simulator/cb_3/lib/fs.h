/*

Copyright (c) 2015 Cromulence LLC

Authors: Cromulence <cgc@cromulence.com>

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
#ifndef __FS_H__
#define __FS_H__
#include "stdint.h"

#define FS_READ (0x4)
#define FS_WRITE (0x6)
#define FS_OWNER_READ (0x4)
#define FS_OWNER_WRITE (0x6)
#define FS_OTHER_READ (0x40)
#define FS_OTHER_WRITE (0x60)
#define MAX_OPEN_FILES (8)
#define MAX_ERROR_LEN (63)
#define MAX_USER_LEN (32)
#define MAX_PASSWD_LEN (32)

typedef struct _inode {
        char *Filename;
        char *Owner;
        uint8_t Mode;
        uint32_t FileSize;
        unsigned char *Data;
} Inode, *pInode;

typedef struct _fs {
        uint32_t MaxSize;
        uint32_t MaxFiles;
        pInode *Inodes;
} Filesystem, *pFilesystem;

typedef struct _file {
	pInode Inode;
	uint8_t Mode;
	uint32_t CurrPosition;
} FILE;

char *FsError(void);
uint8_t DestroyFilesystem(void);
uint8_t InitFilesystem(uint32_t MaxFiles, char *RootPassword);
uint8_t RenameFile(char *OldFilename, char *NewFilename);
uint8_t DeleteFile(char *Filename);
uint8_t InitPasswd(char *RootPassword);
FILE *fopen(char *Filename, char *Mode);
uint32_t fread(char *buf, uint32_t size, uint32_t nitems, FILE *fp);
uint32_t fwrite(char *buf, uint32_t size, uint32_t nitems, FILE *fp);
uint8_t fclose(FILE *fp);
uint8_t ListFiles(char **Buf);
uint8_t Login(char *Username);
void Uid(void);
uint8_t Logout(void);
uint8_t AddUser(char *Username, char *Password);
uint8_t DeleteUser(char *Username);
uint8_t ChangePasswd(char *Username, char *NewPasswd);
uint8_t CheckPasswd(char *Username, char *Password);
uint8_t UserExists(char *Username);
char *fgets(char *buf, uint32_t size, FILE *fp);

#endif // __FS_H__
