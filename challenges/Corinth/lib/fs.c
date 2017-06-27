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
#include "cgc_stdio.h"
#include "cgc_stdint.h"
#include "cgc_malloc.h"
#include "cgc_string.h"
#include "cgc_stdlib.h"
#include "cgc_fs.h"

/* fs.c libc-cfe Filesystem library
This library implements a single-directory filesystem with basic
user permissions. Users are stored in a root-owned 'passwd' file
in the file systems.  Groups are not implemented, so file permissions
are owner cgc_read-cgc_write and other cgc_read-cgc_write only.

Example usage:

int main(int cgc_argc, char *cgc_argv[]) {
	uint32_t MaxFiles = 10;
	FILE *fp;
	char buf[64];

	if (!InitFilesystem(MaxFiles, "rootpasswd")) {
		puts(FsError());
		cgc__terminate(0);
	}

	if (!AddUser("testuser", "testpasswd")) {
		puts(FsError());
		cgc__terminate(0);
	}

	// it's up to the CB to validate passwords using 
	// CheckPasswd() before calling Login
	if (!Login("testuser")) {
		puts(FsError());
		cgc__terminate(0);
	}

	if ((fp = fopen("testfile", "w")) == NULL) {
		puts(FsError());
		cgc__terminate(0);
	}

	if ((fwrite("asdf\n", cgc_strlen("asdf\n"), 1, fp)) != cgc_strlen("asdf\n")) {
		puts(FsError());
		cgc__terminate(0);
	}

	fclose(fp);

	ListFiles(NULL);

	if ((fp = fopen("testfile", "r")) == NULL) {
		puts(FsError());
		cgc__terminate(0);
	}

	// could also use fgets() here
	if ((fread(buf, 10, 1, fp)) == 0) {
		puts(FsError());
		cgc__terminate(0);
	}

	cgc_printf("$s", buf);

	fclose(fp);

	if (!RenameFile("testfile", "testfile2")) {
		puts(FsError());
		cgc__terminate(0);
	}

	ListFiles(NULL);

	if (!DeleteFile("testfile2")) {
		puts(FsError());
		cgc__terminate(0);
	}

	ListFiles(NULL);

	DestroyFilesystem();

}

*/

pFilesystem cgc_FS = NULL;
char *cgc_CurrentUser = NULL;
FILE *FD[MAX_OPEN_FILES];
char FS_ERROR[MAX_ERROR_LEN+1];

// SetFsError: Sets the error buf if no other error has been logged yet
void cgc_SetFsError(char *error) {
	if (FS_ERROR[0] == '\0') {
		cgc_strncpy(FS_ERROR, error, MAX_ERROR_LEN);
	}
}

// Clears any previously logged errors
void cgc_ClearFsError(void) {
	FS_ERROR[0] = '\0';
}
		
// FsError: Returns a pointer to the error buf
char *cgc_FsError(void) {
	return(FS_ERROR);
}

//
// filesystem functions
//

// Destroy the fileysystem
uint8_t cgc_DestroyFilesystem(void) {
	uint32_t i;

	if (!cgc_FS) {
		cgc_SetFsError("Filesystem does not exist");
		return(0);
	}

	// Remove each inode
	for (i = 0; i < cgc_FS->MaxFiles; i++) {
		if (cgc_FS->Inodes[i]) {
			// free the filename
			if (cgc_FS->Inodes[i]->Filename) {
				cgc_free(cgc_FS->Inodes[i]->Filename);
				cgc_FS->Inodes[i]->Filename = NULL;
			}
			// free the owner
			if (cgc_FS->Inodes[i]->Owner) {
				cgc_free(cgc_FS->Inodes[i]->Owner);
				cgc_FS->Inodes[i]->Owner = NULL;
			}
			// free the data
			if (cgc_FS->Inodes[i]->Data) {
				cgc_free(cgc_FS->Inodes[i]->Data);
				cgc_FS->Inodes[i]->Data = NULL;
			}

			// free the inode itself
			cgc_free(cgc_FS->Inodes[i]);
			cgc_FS->Inodes[i] = NULL;
		}
	}

	cgc_free(cgc_FS);
	cgc_FS = NULL;

	cgc_ClearFsError();
	return(1);

}

// Initialize the filesystem
//   MaxFiles: Max number of files the FS should support
//   RootPassword: Initial root user password
uint8_t cgc_InitFilesystem(uint32_t MaxFiles, char *RootPassword) {

	// zero the error string buffer
	cgc_bzero(FS_ERROR, sizeof(FS_ERROR));

	// 0 for MaxFiles would just be silly
	if (MaxFiles == 0) {
		cgc_SetFsError("MaxFiles should be > 0");
		return(0);
	}

	// destroy the FS if one already exists
	if (cgc_FS) {
		cgc_DestroyFilesystem();
	}

	// malloc space for the filesystem
	if ((cgc_FS = cgc_calloc(sizeof(Filesystem))) == NULL) {
		cgc_SetFsError("calloc failed");
		return(0);
	}

	// malloc space for the inode array
	if ((cgc_FS->Inodes = cgc_calloc(sizeof(Inode)*MaxFiles)) == NULL) {
		cgc_SetFsError("calloc failed");
		cgc_free(cgc_FS);
		return(0);
	}

	// Set up the filesystem limits
	cgc_FS->MaxFiles = MaxFiles;
	
	// log in as root
	if (!cgc_Login("root")) {
		cgc_SetFsError("Login failed");
		cgc_free(cgc_FS->Inodes);
		cgc_free(cgc_FS);
		return(0);
	}

	// init the passwd file
	if (!cgc_InitPasswd(RootPassword)) {
		cgc_Logout();
		cgc_SetFsError("Failed to init the passwd file");
		cgc_free(cgc_FS->Inodes);
		cgc_free(cgc_FS);
		return(0);
	}

	// clear the file descriptor array
	cgc_bzero(FD, sizeof(FD));

	cgc_ClearFsError();
	return(1);
}

// Searches the filesystem for a given Filename and returns its Inode or NULL
pInode cgc_FindFile(char *Filename) {
	uint32_t i;

	for (i = 0; i < cgc_FS->MaxFiles; i++) {
		if (cgc_FS->Inodes[i] && cgc_FS->Inodes[i]->Filename) {
			if (!cgc_strcmp(cgc_FS->Inodes[i]->Filename, Filename)) {
				// found it
				return(cgc_FS->Inodes[i]);
			}
		}
	}

	return(NULL);
}

// Create an empty file (sort of like "touch")
pInode cgc_CreateEmptyFile(char *Filename, uint8_t Mode) {
	uint32_t i;

	if (!Filename) {
		cgc_SetFsError("Invalid filename");
		return(NULL);
	}
	if (!cgc_CurrentUser) {
		cgc_SetFsError("Must login first");
		return(NULL);
	}
	if (Mode & ((FS_OWNER_READ|FS_OWNER_WRITE|FS_OTHER_READ|FS_OTHER_WRITE) ^ 0xFF))  {
		cgc_SetFsError("Invalid mode");
		return(0);
	}

	// make sure the file doesn't already exist
	if (cgc_FindFile(Filename)) {
		cgc_SetFsError("File already exists");
		return(NULL);
	}

	// look for a free inode
	for (i = 0; i < cgc_FS->MaxFiles; i++) {
		if (cgc_FS->Inodes[i]) {
			continue;
		}

		// create the inode
		if ((cgc_FS->Inodes[i] = cgc_calloc(sizeof(Inode))) == NULL) {
			cgc_SetFsError("calloc failed");
			return(NULL);
		}

		// set the filename
		if ((cgc_FS->Inodes[i]->Filename = cgc_calloc(cgc_strlen(Filename)+1)) == NULL) {
			cgc_SetFsError("calloc failed");
			cgc_free(cgc_FS->Inodes[i]);
			cgc_FS->Inodes[i] = NULL;
			return(NULL);
		}
		cgc_strcpy(cgc_FS->Inodes[i]->Filename, Filename);

		// set the owner
		if ((cgc_FS->Inodes[i]->Owner = cgc_calloc(sizeof(cgc_CurrentUser)+1)) == NULL) {
			cgc_SetFsError("calloc failed");
			cgc_free(cgc_FS->Inodes[i]->Filename);
			cgc_FS->Inodes[i]->Filename = NULL;
			cgc_free(cgc_FS->Inodes[i]);
			cgc_FS->Inodes[i] = NULL;
			return(NULL);
		}
		cgc_strcpy(cgc_FS->Inodes[i]->Owner, cgc_CurrentUser);

		// set the Mode
		cgc_FS->Inodes[i]->Mode = Mode;

		// set the filesize and Data
		cgc_FS->Inodes[i]->FileSize = 0;
		cgc_FS->Inodes[i]->Data = NULL;

		break;
	}
	if (i == cgc_FS->MaxFiles) {
		cgc_SetFsError("No free inodes");
		return(NULL);
	}

	cgc_ClearFsError();
	return(cgc_FS->Inodes[i]);
}

// Open a file for reading or writing
//  Mode: must be either 'r' or 'w'
//  Returns a file handle suitable for calls to fread, fwrite, fgets, fclose
FILE *cgc_fopen(char *Filename, char *Mode) {
	uint32_t i;
	pInode TargetInode = NULL;
	FILE *fp;

	// sanity checks
	if (!cgc_FS) {
		cgc_SetFsError("Filesystem does not exist");
		return(NULL);
	}
	if (!Filename || !Mode) {
		cgc_SetFsError("Invalid filename or mode");
		return(NULL);
	}
	if (cgc_strlen(Mode) > 1) {
		cgc_SetFsError("Invalid mode");
		return(NULL);
	}
	if (Mode[0] != 'r' && Mode[0] != 'w') {
		cgc_SetFsError("Invalid mode");
		return(NULL);
	}
	if (!cgc_CurrentUser) {
		cgc_SetFsError("Must login first");
		return(NULL);
	}

	// search the filesystem for the filename
	TargetInode = cgc_FindFile(Filename);
	if (!TargetInode && Mode[0] == 'r') {
		cgc_SetFsError("Unable to locate file");
		return(NULL);
	}

	// If one was found, make sure the file isn't already open
	if (TargetInode) {
		for (i = 0; i < MAX_OPEN_FILES; i++) {
			if (FD[i]) {
				if (FD[i]->Inode == TargetInode) {
					// file already open
					cgc_SetFsError("File is already open");
					return(NULL);
				}
			}
		}
	}

	// check permissions
	// only check if we're not root and we're trying to create a new file
	if (TargetInode && cgc_strcmp(cgc_CurrentUser, "root") != 0) {
		// are we the owner of the file?
		if (!cgc_strcmp(TargetInode->Owner, cgc_CurrentUser)) {
			// check owner permissions
			if (Mode[0] == 'r' && ((TargetInode->Mode & FS_OWNER_READ) == 0)) {
				cgc_SetFsError("Permission denied");
				return(NULL);
			}
			if (Mode[0] == 'w' && ((TargetInode->Mode & FS_OWNER_WRITE) == 0)) {
				cgc_SetFsError("Permission denied");
				return(NULL);
			}
		} else {
			// check other permissions
			if (Mode[0] == 'r' && ((TargetInode->Mode & FS_OTHER_READ) == 0)) {
				cgc_SetFsError("Permission denied");
				return(NULL);
			}
			if (Mode[0] == 'w' && ((TargetInode->Mode & FS_OTHER_WRITE) == 0)) {
				cgc_SetFsError("Permission denied");
				return(NULL);
			}
		}
	}

	// allocate a FILE record
	if ((fp = cgc_calloc(sizeof(FILE))) == NULL) {
		cgc_SetFsError("calloc failed");
		return(NULL);
	}

	// find a file descriptor slot to hold the new FILE record
	for (i = 0; i < MAX_OPEN_FILES; i++) {
		if (FD[i]) {
			continue;
		}
		FD[i] = fp;
		break;
	}
	if (i == MAX_OPEN_FILES) {
		// unable to find available file descriptor
		cgc_SetFsError("No free file descriptors");
		cgc_free(fp);
		return(NULL);
	}

	if (Mode[0] == 'w') {
		// open for writing
		if (!TargetInode) {
			// create a new file
			if ((TargetInode = cgc_CreateEmptyFile(Filename, FS_OWNER_READ|FS_OWNER_WRITE)) == NULL) {
				cgc_SetFsError("Failed to create file");
				FD[i] = NULL;
				cgc_free(fp);
				return(NULL);
			}
			fp->Inode = TargetInode;
			fp->Mode = FS_WRITE;
			fp->CurrPosition = 0;
		} else {
			// truncate an existing file
			fp->Inode = TargetInode;
			fp->Mode = FS_WRITE;
			fp->CurrPosition = 0;

			fp->Inode->FileSize = 0;
			if (fp->Inode->Data) {
				cgc_free(fp->Inode->Data);
				fp->Inode->Data = NULL;
			}
		}
	} else {
		// open for reading
		fp->Inode = TargetInode;
		fp->Mode = FS_READ;
		fp->CurrPosition = 0;

	}

	cgc_ClearFsError();
	return(fp);

}

// closes an open file
uint8_t cgc_fclose(FILE *fp) {
	uint8_t i;

	if (!fp) {
		cgc_SetFsError("Invalid file pointer");
		return(0);
	}

	// find the FD holding this FILE pointer
	for (i = 0; i < MAX_OPEN_FILES; i++) {
		if (FD[i] == fp) {
			FD[i] = NULL;
		}
	}

	cgc_ClearFsError();
	cgc_free(fp);
	return(1);

}
	
// reads the specified number of items of a particular size from the specified file
//   returns the number of bytes cgc_read
uint32_t cgc_fread(char *buf, uint32_t size, uint32_t nitems, FILE *fp) {

	if (!buf || !fp) {
		cgc_SetFsError("Invalid buffer or file pointer");
		return(0);
	}
	if (!fp->Inode->Data) {
		cgc_SetFsError("End of file");
		return(0);
	}

	if (size*nitems > (fp->Inode->FileSize - fp->CurrPosition)) {
		cgc_memcpy(buf, fp->Inode->Data + fp->CurrPosition, fp->Inode->FileSize - fp->CurrPosition);
		fp->CurrPosition += (fp->Inode->FileSize - fp->CurrPosition);
		cgc_ClearFsError();
		return(fp->Inode->FileSize - fp->CurrPosition);
	} else {
		cgc_memcpy(buf, fp->Inode->Data + fp->CurrPosition, size*nitems);
		fp->CurrPosition += size*nitems;
		cgc_ClearFsError();
		return(size*nitems);
	}
}

// writes the specified number of items of a particular size to the specified file
//   returns the number of bytes written
uint32_t cgc_fwrite(char *buf, uint32_t size, uint32_t nitems, FILE *fp) {
	unsigned char *NewData;

	if (!buf || !fp) {
		cgc_SetFsError("Invalid buffer or file pointer");
		return(0);
	}

	// allocate space to hold the current data and the new data
	if ((NewData = cgc_calloc(fp->Inode->FileSize + size*nitems)) == NULL) {
		cgc_SetFsError("calloc failed");
		return(0);
	}

	// cgc_write the current data to the new buffer
	if (fp->Inode->Data) {
		cgc_memcpy(NewData, fp->Inode->Data, fp->Inode->FileSize);
	}

	// cgc_write the new data to the new buffer
	cgc_memcpy(NewData+fp->Inode->FileSize, buf, size*nitems);
	
	fp->Inode->FileSize += size*nitems;

	if (fp->Inode->Data) {
		cgc_free(fp->Inode->Data);
	}
	fp->Inode->Data = NewData;

	cgc_ClearFsError();
	return(size*nitems);
}

// reads a line delimited by '\n' from the file
//   returns a pointer to the line or NULL on EoF or error
char *cgc_fgets(char *buf, uint32_t size, FILE *fp) {
	uint32_t TotalBytes = 0;

	if (!buf) {
		cgc_SetFsError("Invalid buffer");
		return(NULL);
	}
	if (!fp) {
		cgc_SetFsError("Invalid file");
		return(NULL);
	}
	if (fp->CurrPosition == fp->Inode->FileSize) {
		cgc_SetFsError("End of file");
		return(NULL);
	}
	if (!fp->Inode->Data) {
		cgc_SetFsError("End of file");
		return(NULL);
	}

	// cgc_read in one character at a time
	while ((fp->CurrPosition < fp->Inode->FileSize) && (TotalBytes < size-1)) {
		buf[TotalBytes++] = fp->Inode->Data[fp->CurrPosition++];
		// if the character is a newline, we're done
		if (fp->Inode->Data[fp->CurrPosition-1] == '\n') {
			break;
		}
	}
	buf[TotalBytes] = '\0';

	return(buf);
}

// List the files in the filesystem
//   like an 'ls'
uint8_t cgc_ListFiles(char **Buf) {
	uint32_t i;
	char Mode[5];
	uint32_t TotalLen;
	uint32_t NewLen;

	if (!cgc_FS) {
		cgc_SetFsError("Filesystem does not exist");
		return(0);
	}

	// if we've been passed a Buf pointer, then cgc_write the list
	// to a newly allocated buffer rather than stdout
	// But first we need to calculate how much buffer we'll need
	if (Buf) {
		// listing header length
		TotalLen = 32+1+32+1+8+4+1;

		// length of each of the file lines
		for (i = 0; i < cgc_FS->MaxFiles; i++) {
			if (cgc_FS->Inodes[i] == NULL) {
				continue;
			}

			if ((NewLen = cgc_strlen(cgc_FS->Inodes[i]->Filename)) < 32) {
				TotalLen += 32;
			} else {
				TotalLen += NewLen;
			}
			TotalLen++;
			if ((NewLen = cgc_strlen(cgc_FS->Inodes[i]->Owner)) < 32) {
				TotalLen += 32;
			} else {
				TotalLen += NewLen;
			}
			TotalLen++;
			if ((NewLen = cgc_log10(cgc_FS->Inodes[i]->FileSize)+1) < 8) {
				TotalLen += 8;
			} else {
				TotalLen += NewLen;
			}
			// 1 (space), 4 (mode), 1 (newline)
			TotalLen += 6;
		}

		// allocate the buffer
		if ((*Buf = cgc_calloc(TotalLen)) == NULL) {
			cgc_SetFsError("calloc failed");
			return(0);
		}
	}

	if (Buf) {
		cgc_sprintf(*Buf, "$-32s $-32s $-8s $-4s\n", "Filename", "Owner", "Size", "Mode");
	} else {
		cgc_printf("$-32s $-32s $-8s $-4s\n", "Filename", "Owner", "Size", "Mode");
	}
	for (i = 0; i < cgc_FS->MaxFiles; i++) {
		if (cgc_FS->Inodes[i] == NULL) {
			continue;
		}
		if (Buf) {
			cgc_sprintf(*Buf, "$s$-32s $-32s $-8d ", 
				*Buf,
				cgc_FS->Inodes[i]->Filename,
				cgc_FS->Inodes[i]->Owner,
				cgc_FS->Inodes[i]->FileSize);
		} else {
			cgc_printf("$-32s $-32s $-8d ", 
				cgc_FS->Inodes[i]->Filename,
				cgc_FS->Inodes[i]->Owner,
				cgc_FS->Inodes[i]->FileSize);
		}
		// print the mode
		cgc_memset(Mode, '-', 5);	
		Mode[4] = '\0';
		if (cgc_FS->Inodes[i]->Mode & FS_OWNER_READ)
			Mode[0] = 'r';
		if (cgc_FS->Inodes[i]->Mode & FS_OWNER_WRITE)
			Mode[1] = 'w';
		if (cgc_FS->Inodes[i]->Mode & FS_OTHER_READ)
			Mode[2] = 'r';
		if (cgc_FS->Inodes[i]->Mode & FS_OTHER_WRITE)
			Mode[3] = 'w';
		if (Buf) {
			cgc_sprintf(*Buf,"$s$-4s\n", *Buf, Mode);
		} else {
			cgc_printf("$-4s\n", Mode);
		}
	}

	cgc_ClearFsError();
	return(1);

}

// Delete a file on the filesystem
uint8_t cgc_DeleteFile(char *Filename) {
	uint32_t i;
	uint32_t InodeIndex;
	pInode TargetInode;

	if (!cgc_FS) {
		cgc_SetFsError("Filesystem does not exist");
		return(0);
	}
	if (!Filename) {
		cgc_SetFsError("Invalid filename");
		return(0);
	}
	if (!cgc_CurrentUser) {
		cgc_SetFsError("Must login first");
		return(0);
	}

	for (i = 0; i < cgc_FS->MaxFiles; i++) {
		if (cgc_FS->Inodes[i] == NULL) {
			continue;
		}
		if (!cgc_strcmp(cgc_FS->Inodes[i]->Filename, Filename)) {
			// found it
			TargetInode = cgc_FS->Inodes[i];
			InodeIndex = i;
			break;
		}
	}
	if (i == cgc_FS->MaxFiles) {
		cgc_SetFsError("Unable to locate file");
		return(0);
	}

	// make sure there are no file descriptors open to it
	for (i = 0; i < MAX_OPEN_FILES; i++) {
		if (FD[i]) {
			if (FD[i]->Inode == TargetInode) {
				// file is still open
				return(0);
			}
		}
	}

	// do we have permission to remove it?
	if (cgc_strcmp(cgc_CurrentUser, "root") != 0 && (cgc_strcmp(cgc_CurrentUser, TargetInode->Owner) != 0)) {
		// we're not root or the owner of the file, so no
		cgc_SetFsError("Permission denied");
		return(0);
	}
	
	// remove the inode vars
	cgc_free(TargetInode->Filename);
	if (TargetInode->Owner) {
		cgc_free(TargetInode->Owner);
	}
	if (TargetInode->Data) {
		cgc_free(TargetInode->Data);
	}

	// remove the inode
	cgc_free(TargetInode);
	cgc_FS->Inodes[InodeIndex] = NULL;

	cgc_ClearFsError();
	return(1);
}

// Rename a file 
uint8_t cgc_RenameFile(char *OldFilename, char *NewFilename) {
	uint32_t i;
	pInode SourceInode = NULL;
	char *TempFilename;

	if (!OldFilename || !NewFilename) {
		cgc_SetFsError("Invalid filename");
		return(0);
	}

	// find the old filename
	for (i = 0; i < cgc_FS->MaxFiles; i++) {
		if (cgc_FS->Inodes[i] && cgc_FS->Inodes[i]->Filename) {
			if (!cgc_strcmp(cgc_FS->Inodes[i]->Filename, OldFilename)) {
				// found it
				SourceInode = cgc_FS->Inodes[i];
			}
			if (!cgc_strcmp(cgc_FS->Inodes[i]->Filename, NewFilename)) {
				// the new filename already exists
				cgc_SetFsError("Destination file already exists");
				return(0);
			}
		}
	}
	if (!SourceInode) {
		cgc_SetFsError("Source file not found");
		return(0);
	}

	// Do we have permissions to rename the old file
	if (cgc_strcmp(cgc_CurrentUser, "root") != 0 && (cgc_strcmp(cgc_CurrentUser, SourceInode->Owner) != 0)) {
		// we're not root or the owner of the file, so no
		cgc_SetFsError("Permission denied");
		return(0);
	}

	// rename the file
	if ((TempFilename = cgc_calloc(cgc_strlen(NewFilename)+1)) == NULL) {
		cgc_SetFsError("calloc failed");
		return(0);
	}	
	cgc_strcpy(TempFilename, NewFilename);
	cgc_free(SourceInode->Filename);
	SourceInode->Filename = TempFilename;

	cgc_ClearFsError();
	return(1);
}

// ChangeMode
uint8_t cgc_ChangeMode(char *Filename, uint8_t NewMode) {
	pInode TargetInode;

	if (!Filename) {
		cgc_SetFsError("Invalid user");
		return(0);
	}

	// check that the mode is valid
	if (NewMode & ((FS_OWNER_READ|FS_OWNER_WRITE|FS_OTHER_READ|FS_OTHER_WRITE) ^ 0xFF))  {
		cgc_SetFsError("Invalid mode");
		return(0);
	}

	// find the file
	if ((TargetInode = cgc_FindFile(Filename)) == NULL) {
		cgc_SetFsError("Unable to find file");
		return(0);
	}

	// make sure we're root or we're the owner
	if ((cgc_strcmp(cgc_CurrentUser, "root") != 0) && (cgc_strcmp(cgc_CurrentUser, TargetInode->Owner) != 0)) {
		cgc_SetFsError("Permission denied");
		return(0);
	}

	// change the mode
	TargetInode->Mode = NewMode;

	cgc_ClearFsError();	
	return(1);
}

// Change the owner of a file
//   Can only be done by 'root' user (root must be the currently logged in user)
uint8_t cgc_ChangeOwner(char *Filename, char *NewOwner) {
	pInode TargetInode;
	char *TempOwner;

	if (!Filename) {
		cgc_SetFsError("Invalid filename");
		return(0);
	}
	if (!NewOwner) {
		cgc_SetFsError("Invalid owner");
		return(0);
	}
	
	if (cgc_strcmp(cgc_CurrentUser, "root") != 0) {
		cgc_SetFsError("Must be root");
		return(0);
	}

	if ((TargetInode = cgc_FindFile(Filename)) == NULL) {
		cgc_SetFsError("Unable to find file");
		return(0);
	}

	// make sure the NewOwner exists in the passwd file
	if (!cgc_UserExists(NewOwner)) {
		cgc_SetFsError("Invalid user");
		return(0);
	}

	// calloc some space for the new owner name
	if ((TempOwner = cgc_calloc(cgc_strlen(NewOwner)+1)) == NULL) {
		cgc_SetFsError("calloc failed");
		return(0);
	}
	cgc_strcpy(TempOwner, NewOwner);

	// update the owner on the inode
	if (TargetInode->Owner) {
		cgc_free(TargetInode->Owner);
	}
	TargetInode->Owner = TempOwner;

	cgc_ClearFsError();
	return(1);
}

//
// user functions
//

// Login
uint8_t cgc_Login(char *Username) {
	char *NewUsername;

	if (!Username) {
		cgc_SetFsError("Invalid username");
		return(0);
	}

	// copy the requested username 
	if ((NewUsername = cgc_calloc(cgc_strlen(Username)+1)) == NULL) {
		cgc_SetFsError("calloc failed");
		return(0);
	}
	cgc_strcpy(NewUsername, Username);

	// is anyone currently logged in
	if (cgc_CurrentUser) {
		cgc_free(cgc_CurrentUser);
		cgc_CurrentUser = NULL;
	}

	// log in as the requested user
	cgc_CurrentUser = NewUsername;

	cgc_ClearFsError();
	return(1);
	
}

void cgc_Uid(void) {
	if (cgc_CurrentUser) {
		cgc_puts(cgc_CurrentUser);
	}
}

// log the current user out (leaving no user logged in)
uint8_t cgc_Logout(void) {

	if (cgc_CurrentUser) {
		cgc_free(cgc_CurrentUser);
	}

	cgc_CurrentUser = NULL;

	cgc_ClearFsError();
	return(1);
}

// init passwd file creating the 'root' user and setting its password
uint8_t cgc_InitPasswd(char *RootPassword) {
	FILE *fp;

	if (!RootPassword) {
		cgc_SetFsError("Invalid root password");
		return(0);
	}

	// fopen the passwd file
	if ((fp = cgc_fopen("passwd", "w")) == NULL) {
		cgc_SetFsError("Unable to open passwd file");
		return(0);
	}

	// cgc_write the root user
	cgc_fwrite("root:", 5, 1, fp);
	cgc_fwrite(RootPassword, cgc_strlen(RootPassword), 1, fp);

	// close the file
	cgc_fclose(fp);

	cgc_ClearFsError();
	return(1);

}

// checks if the specified Username exists in the passwd file
uint8_t cgc_UserExists(char *Username) {
	FILE *in;
	char line[128];
	char *User;

	if (!Username) {
		cgc_SetFsError("Invalid username");
		return(0);
	}

	// open the passwd file
	if ((in = cgc_fopen("passwd", "r")) == NULL) {
		cgc_SetFsError("Unable to open passwd file");
		return(0);
	}

	// cgc_read in each line
	while (cgc_fgets(line, 127, in)) {
		// see if it's the target username
		if ((User = cgc_strtok(line, ":")) == NULL) {
			cgc_SetFsError("Failed to parse passwd file");
			return(0);
		}
		if (!cgc_strcmp(User, Username)) {
			// found it
			cgc_fclose(in);
			return(1);
		}
	}

	// close the passwd file
	cgc_fclose(in);

	cgc_ClearFsError();
	return(0);

}

// add a user to the passwd file
uint8_t cgc_AddUser(char *Username, char *Password) {
	FILE *passwd;
	FILE *newpasswd;
	char line[128];

	if (!Username) {
		cgc_SetFsError("Invalid username");
		return(0);
	}
	if (!Password) {
		cgc_SetFsError("Invalid password");
		return(0);
	}
	if (cgc_strcmp(cgc_CurrentUser, "root") != 0) {
		cgc_SetFsError("Must be root");
		return(0);
	}
	if (cgc_strlen(Username) > MAX_USER_LEN) {
		cgc_SetFsError("Invalid username");
		return(0);
	}
	if (cgc_strlen(Password) > MAX_PASSWD_LEN) {
		cgc_SetFsError("Invalid password");
		return(0);
	}

	// make sure the username doesn't already exist
	if (cgc_UserExists(Username)) {
		cgc_SetFsError("User already exists");
		return(0);
	}

	// open the passwd file
	if ((passwd = cgc_fopen("passwd", "r")) == NULL) {
		cgc_SetFsError("Unable to open passwd file");
		return(0);
	}

	// open the temp passwd file
	if ((newpasswd = cgc_fopen("~passwd", "w")) == NULL) {
		cgc_SetFsError("Unable to open tmp passwd file");
		cgc_fclose(passwd);
		return(0);
	}

	// cgc_read in each line of the passwd file
	while (cgc_fgets(line, 127, passwd) != NULL) {
		// cgc_write it out to the temp passwd file
		if (cgc_fwrite(line, cgc_strlen(line), 1, newpasswd) != cgc_strlen(line)) {
			cgc_fclose(passwd);
			cgc_fclose(newpasswd);
			cgc_SetFsError("Unable to write tmp passwd file");
			cgc_DeleteFile("~passwd");
			return(0);
		}
		if (line[cgc_strlen(line)-1] != '\n') {
			if (cgc_fwrite("\n", 1, 1, newpasswd) != 1) {
				cgc_fclose(passwd);
				cgc_fclose(newpasswd);
				cgc_SetFsError("Unable to write tmp passwd file");
				cgc_DeleteFile("~passwd");
				return(0);
			}
		}
	}

	// cgc_write the new passwd entry
	cgc_sprintf(line, "$s:$s", Username, Password);
	cgc_fwrite(line, cgc_strlen(line), 1, newpasswd);

	// close the passwd file
	cgc_fclose(passwd);

	// close the temp passwd file
	cgc_fclose(newpasswd);

	// remove the passwd file
	cgc_DeleteFile("passwd");
	
	// move the temp passwd file to passwd
	cgc_RenameFile("~passwd", "passwd");

	cgc_ClearFsError();
	return(1);
}

// delete user
uint8_t cgc_DeleteUser(char *Username) {
	char line[128];
	char *User;
	uint8_t Found = 0;
	FILE *passwd;
	FILE *newpasswd;

	if (!Username) {
		cgc_SetFsError("Invalid username");
		return(0);
	}
	if (cgc_strcmp(cgc_CurrentUser, "root") != 0) {
		cgc_SetFsError("Must be root");
		return(0);
	}
	if (!cgc_strcmp(Username, "root")) {
		cgc_SetFsError("Can't delete root user");
		return(0);
	}

	// open the passwd file
	if ((passwd = cgc_fopen("passwd", "r")) == NULL) {
		cgc_SetFsError("Unable to open passwd file");
		return(0);
	}

	// open the temp passwd file
	if ((newpasswd = cgc_fopen("~passwd", "w")) == NULL) {
		cgc_SetFsError("Unable to open tmp passwd file");
		cgc_fclose(passwd);
		return(0);
	}

	// cgc_read in each line of the passwd file
	while (cgc_fgets(line, 127, passwd) != NULL) {
		// skip blank lines
		if (cgc_strlen(line) == 0) {
			continue;
		}
		// cgc_write it out to the temp passwd file
		// if it's not the user we're deleting
		if ((User = cgc_strtok(line, ":")) == NULL) {
			cgc_SetFsError("Failed to parse passwd file");
			cgc_fclose(passwd);
			cgc_fclose(newpasswd);
			cgc_DeleteFile("~passwd");
			return(0);
		}
		if (!cgc_strcmp(User, Username)) {
			// found it, so don't cgc_write the user
			Found = 1;
			continue;
		}

		// restore the delimiter strtok would have removed
		line[cgc_strlen(User)] = ':';

		// cgc_write the line to the temp passwd file
		if (cgc_fwrite(line, cgc_strlen(line), 1, newpasswd) != cgc_strlen(line)) {
			cgc_fclose(passwd);
			cgc_fclose(newpasswd);
			cgc_SetFsError("Unable to write tmp passwd file");
			cgc_DeleteFile("~passwd");
			return(0);
		}
	}

	// close the passwd file
	cgc_fclose(passwd);

	// close the temp passwd file
	cgc_fclose(newpasswd);

	if (!Found) {
		cgc_SetFsError("User not found");
		cgc_fclose(passwd);
		cgc_fclose(newpasswd);
		cgc_DeleteFile("~passwd");
		return(0);
	}

	// remove the passwd file
	cgc_DeleteFile("passwd");
	
	// move the temp passwd file to passwd
	cgc_RenameFile("~passwd", "passwd");

	cgc_ClearFsError();
	return(1);

}

// change user password
uint8_t cgc_ChangePasswd(char *Username, char *NewPasswd) {
	char line[128];
	char *User;
	uint8_t Found = 0;
	FILE *passwd;
	FILE *newpasswd;

	if (!Username) {
		cgc_SetFsError("Invalid username");
		return(0);
	}
	if (!NewPasswd) {
		cgc_SetFsError("Invalid password");
		return(0);
	}
	if (cgc_strlen(NewPasswd) > MAX_PASSWD_LEN) {
		cgc_SetFsError("Invalid password");
		return(0);
	}

	if (cgc_strcmp(cgc_CurrentUser, Username) != 0 && cgc_strcmp(cgc_CurrentUser, "root") != 0) {
		cgc_SetFsError("Must be root or the user being changed");
		return(0);
	}

	// open the passwd file
	if ((passwd = cgc_fopen("passwd", "r")) == NULL) {
		cgc_SetFsError("Unable to open passwd file");
		return(0);
	}

	// open the temp passwd file
	if ((newpasswd = cgc_fopen("~passwd", "w")) == NULL) {
		cgc_SetFsError("Unable to open tmp passwd file");
		cgc_fclose(passwd);
		return(0);
	}

	// cgc_read in each line of the passwd file
	while (cgc_fgets(line, 127, passwd) != NULL) {
		// skip blank lines
		if (cgc_strlen(line) == 0) {
			continue;
		}
		// cgc_write it out to the temp passwd file
		// if it's not the user we're deleting
		if ((User = cgc_strtok(line, ":")) == NULL) {
			cgc_SetFsError("Failed to parse passwd file");
			cgc_fclose(passwd);
			cgc_fclose(newpasswd);
			cgc_DeleteFile("~passwd");
			return(0);
		}
		if (!cgc_strcmp(User, Username)) {
			// found it, cgc_write the new passwd
			cgc_sprintf(line, "$s:$s\n", Username, NewPasswd);
			if (cgc_fwrite(line, cgc_strlen(line), 1, newpasswd) != cgc_strlen(line)) {
				cgc_fclose(passwd);
				cgc_fclose(newpasswd);
				cgc_SetFsError("Unable to write tmp passwd file");
				cgc_DeleteFile("~passwd");
				return(0);
			}
			continue;
		}

		// restore the delimiter strtok would have removed
		line[cgc_strlen(User)] = ':';

		// restore the delimiter strtok would have removed
		if (cgc_fwrite(line, cgc_strlen(line), 1, newpasswd) != cgc_strlen(line)) {
			cgc_SetFsError("Unable to write tmp passwd file");
			cgc_fclose(passwd);
			cgc_fclose(newpasswd);
			cgc_DeleteFile("~passwd");
			return(0);
		}
	}

	// close the passwd file
	cgc_fclose(passwd);

	// close the temp passwd file
	cgc_fclose(newpasswd);

	if (!Found) {
		cgc_SetFsError("User not found");
		cgc_fclose(passwd);
		cgc_fclose(newpasswd);
		cgc_DeleteFile("~passwd");
		return(0);
	}

	// remove the passwd file
	cgc_DeleteFile("passwd");
	
	// move the temp passwd file to passwd
	cgc_RenameFile("~passwd", "passwd");

	cgc_ClearFsError();
	return(1);

}

// check user password
uint8_t cgc_CheckPasswd(char *Username, char *Password) {
	char line[128];
	char *User;
	char *CurrPassword;
	uint8_t Found = 0;
	FILE *passwd;
	char *OldUser = NULL;
	uint8_t NoLogin = 0;

	if (!Username) {
		cgc_SetFsError("Invalid username");
		return(0);
	}
	if (!Password) {
		cgc_SetFsError("Invalid password");
		return(0);
	}
	if (cgc_strlen(Password) > MAX_PASSWD_LEN) {
		cgc_SetFsError("Invalid password");
		return(0);
	}

	// need to log in as root for the rest of this function
	// save the current logged in user
	if (cgc_CurrentUser) {
		if (cgc_strcmp(cgc_CurrentUser, "root") != 0) {
			if ((OldUser = cgc_calloc(cgc_strlen(cgc_CurrentUser)+1)) == NULL) {
				cgc_SetFsError("calloc failed");
				return(0);
			}
			cgc_strcpy(OldUser, cgc_CurrentUser);
			cgc_Logout();
			cgc_Login("root");
		}
	} else {
		cgc_Login("root");
		NoLogin = 1;
	}

	// open the passwd file
	if ((passwd = cgc_fopen("passwd", "r")) == NULL) {
		cgc_SetFsError("Unable to open passwd file");
		if (OldUser) {
			cgc_Logout();
			cgc_Login(OldUser);
			cgc_free(OldUser);
		}
		if (NoLogin) {
			cgc_Logout();
		}
		return(0);
	}

	// cgc_read in each line of the passwd file
	while (cgc_fgets(line, 127, passwd) != NULL) {
		// skip blank lines
		if (cgc_strlen(line) == 0) {
			continue;
		}
		// parse the password field
		if ((User = cgc_strtok(line, ":")) == NULL) {
			cgc_SetFsError("Failed to parse passwd file");
			cgc_fclose(passwd);
			if (OldUser) {
				cgc_Logout();
				cgc_Login(OldUser);
				cgc_free(OldUser);
			}
			if (NoLogin) {
				cgc_Logout();
			}
			return(0);
		}
		if (cgc_strcmp(User, Username) != 0) {
			// not the target user, skip on
			continue;
		}

		// found the target user, parse the password
		if ((CurrPassword = cgc_strtok(NULL, ":")) == NULL) {
			cgc_SetFsError("Failed to parse passwd file");
			cgc_fclose(passwd);
			if (OldUser) {
				cgc_Logout();
				cgc_Login(OldUser);
				cgc_free(OldUser);
			}
			if (NoLogin) {
				cgc_Logout();
			}
			return(0);
		}

		if (!cgc_strcmp(CurrPassword, Password)) {
			// matches
			cgc_ClearFsError();
			cgc_fclose(passwd);
			if (OldUser) {
				cgc_Logout();
				cgc_Login(OldUser);
				cgc_free(OldUser);
			}
			if (NoLogin) {
				cgc_Logout();
			}
			return(1);
		}

	}

	// close the passwd file
	cgc_fclose(passwd);

	if (!Found) {
		cgc_SetFsError("User not found");
		if (OldUser) {
			cgc_Logout();
			cgc_Login(OldUser);
			cgc_free(OldUser);
		}
		if (NoLogin) {
			cgc_Logout();
		}
		return(0);
	}

	cgc_ClearFsError();
	if (OldUser) {
		cgc_Logout();
		cgc_Login(OldUser);
		cgc_free(OldUser);
	}
	if (NoLogin) {
		cgc_Logout();
	}
	return(0);

}
