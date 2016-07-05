/*

Author: Joe Rogers <joe@cromulence.com>

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
#include <libcgc.h>
#include "stdlib.h"
#include "stdint.h"
#include "fs.h"

/*
   Initialize the file system for the given fs_size
 */
int InitFS(uint32_t fs_size) {
	inode *n;

	// round up to the nearest convenient page size
	if ((fs_size % PAGE_SIZE) != 0) {
		fs_size -= (fs_size % PAGE_SIZE);
		fs_size += PAGE_SIZE; 
	}

	// make sure the fs_size is within limits
	if (fs_size > MAX_FS_SIZE) {
		puts("Requested filesystem size is too large\n");
		return(-1);
	}

	// make sure the fs_size is an even number of blocks
	if ((fs_size % DATA_BLOCK_SIZE) != 0) {
		puts("Requested filesystem size is not an even number of blocks\n");
		return(-1);
	}

	// populate the superblock
	bzero(&fs, sizeof(superblock));
	fs.magic = CRFS;
	fs.blocksize = DATA_BLOCK_SIZE;
	fs.fs_size = fs_size;

	// allocate space for the first inode page
	if (allocate(PAGE_SIZE, 0, (void **)&(fs.inode_pages[0]))) {
		puts("Failed to allocate inode page\n");
		return(-1);
	}
	bzero(fs.inode_pages[0], PAGE_SIZE);

	// zero space for the free_list
	bzero(free_list, sizeof(free_t)*MAX_FREE_PAGES);

	// allocate space for the first data page
	if (allocate(PAGE_SIZE, 0, (void *)&(free_list[0].page))) {
		puts("Failed to allocate data blocks\n");
		return(-1);
	}
	bzero(free_list[0].page, PAGE_SIZE);

	// populate the top-level root directory inode
	n = fs.inode_pages[0];
	strcpy(n[0].fname, "/");
	n[0].type = INODE_DIRECTORY;
	n[0].fsize = 0;
	n[0].num_blocks = 1;
	n[0].blocks[0] = &(free_list[0].page[0]);
	free_list[0].in_use = 0x80;

	return(0);
}

/*
   Destroy the filesystem
 */
int DestroyFS() {
	uint32_t num_pages;
	int i;

	num_pages = fs.fs_size/PAGE_SIZE;

	// deallocate the data blocks
	for (i = 0; i < num_pages; i++) {
		if (free_list[i].page) {
			deallocate((void *)&(free_list[i].page), PAGE_SIZE);
		}
	}

	// deallocate the inodes
	for (i = 0; i < MAX_INODE_PAGES; i++) {
		if (fs.inode_pages[i]) {
			deallocate((void **)&(fs.inode_pages[i]), PAGE_SIZE);
		}
	}

	return(0);
}

/* 
   Find an inode given the file name
 */
inode *FindInode(char *fname) {
	int i, j;
	inode *t;

	if (!fname) {
		return(NULL);
	}

	// linear search 
	for (i = 0; i < MAX_INODE_PAGES; i++) {
		if (!fs.inode_pages[i]) {
			break;
		}

		t = fs.inode_pages[i];
		for (j = 0; j < INODES_PER_PAGE; j++) {
			if ((t[j].type == INODE_FILE || t[j].type == INODE_DIRECTORY) 
				&& !strcmp(t[j].fname, fname)) {
				return(&(t[j]));
			}
		}
	}
	return(NULL);

}

/*
   Find a directory entry given the filename and the directory's inode pointer
 */
inode *FindDirEntry(inode *dir, char *fname) {
	int i,j;
	inode *file;
	directory *d;

	if (dir == NULL || fname == NULL) {
		return(NULL);
	}

	if (dir->type != INODE_DIRECTORY) {
		return(NULL);
	}

	// check each inode block to see if it has data
	for (i = 0; i < INODE_DATA_BLOCKS; i++)  {
		d = (directory *)(dir->blocks[i]);
		if (!d) {
			continue;
		}
#ifdef PATCHED
		for (j = 0; j < MAX_DIR_INODES; j++) {
#else
		// allow the directory to to go past the MAX
		// by one entry, but only if the dir->fsize
		// variable indicates that an entry is valid
		for (j = 0; j <= MAX_DIR_INODES && (j+1)*4 <= dir->fsize; j++) {
#endif
			file = d->inodes[j];
			if (!file) {
				continue;
			}
			if (!strcmp(file->fname, fname)) {
				return(file);
			}
		}
	}
	return(NULL);

}

/* 
   Traverse the file system to see if a given file exists.
   retval:
     -1 error
      0 file does not exist
      1 file exists
      2 file exists and is a directory
 */
int CheckFileExists(char *fname, inode **file_inode) {
	char *tok;
	char *f = fname;
	inode *i, *i2;
	int32_t retval = 1;

	if (!fname) {
		return(-1);
	}

	// should include full path
	if (fname[0] != '/') {
		puts("invalid filename");
		return(-1);	
	}

	// find the root inode
	if ((i = FindInode("/")) == NULL) {
		puts("failed to root find inode");
		return(-1);
	}

	// handle special case of the root directory
	if (!strcmp(fname, "/")) {
		*file_inode = i;
		return(2);
	}

	while ((tok = strtok(f, "/"))) {
		f = NULL;
		retval = 0;

		// read the directory contents to see 
		// if our current token is in there
		if ((i2 = FindDirEntry(i, tok))) {
			// found this token
			if (i2->type == INODE_DIRECTORY) {
				// it's a directory, traverse it
				i = i2;
				*file_inode = i2;
				retval = 2;
			} else {
				// it's a file, we found the end of the path
				*file_inode = i2;
				retval = 1;
				break;
			}
		}
	}
	// never made it into the while loop so the path doesn't exist
	if (f != NULL) {
		retval = 0;
	}

	return(retval);

}

/*
   Find an available inode
 */
inode *FindFreeInode() {
	int i, j;
	inode *ipage;
	inode *in;

	for (i = 0; i < MAX_INODE_PAGES; i++) {
		ipage = fs.inode_pages[i];
		if (!ipage) {
			// allocate a new page
			if (allocate(PAGE_SIZE, 0, (void **)&(fs.inode_pages[i]))) {
				puts("Failed to allocate inode page\n");
				return(NULL);
			}
			bzero(fs.inode_pages[i], PAGE_SIZE);
			ipage = fs.inode_pages[i];
		}
		for (j = 0; j < INODES_PER_PAGE; j++) {
			in = &(ipage[j]);
			if (in->type == INODE_FREE) {
				return(in);	
			}
		}
	}

	// all inodes are consumed
	return(NULL);

}

/* 
   Find an available data block
 */
block *FindFreeDataBlock() {
	int i;
	block *p;
	int free_block = 7;
	uint8_t in_use;

	for (i = 0; i < MAX_FREE_PAGES; i++) {
		p = free_list[i].page;
		if (!p) {
			// see if the fs is full
			if (i*PAGE_SIZE >= fs.fs_size) {
				return(NULL);
			}
	
			// allocate a new page
			if (allocate(PAGE_SIZE, 0, (void *)&(free_list[i].page))) {
				puts("Failed to allocate data blocks\n");
				return(NULL);
			}
			bzero(free_list[i].page, PAGE_SIZE);
			p = free_list[i].page;
		}
		if (free_list[i].in_use == 0xff) {
			// page entirely used
			continue;
		}
		in_use = free_list[i].in_use;
		while ((in_use & 0x1) && free_block) {
			in_use = in_use >> 1;
			free_block--;
		}

		// mark the found block as in_use
		free_list[i].in_use |= (0x80 >> free_block);

		return(&(free_list[i].page[free_block]));
	}

	return(NULL);

}

/*
   Given a full path to a file, split it into its component
   directory path and file name.  ie:
   full_name = "/home/cgc/filename"
     returns:
      path = "/home/cgc"
      fname = "filename"
*/
int SplitPath(char *full_name, char *path, char *fname) {
	int i;

	if (!full_name || !path || !fname) {
		return(0);
	}

	strcpy(path, full_name);
	for (i = strlen(path); i > 0; i--) {
		if (path[i] == '/') {
			// grab the file name portion while we're here
			strcpy(fname, path+i+1);

			// null term the path and we're done
			path[i] = '\0';
			break;
		}
	}
	// path only has one / at the beginning
	// so path is "/"
	if (i == 0) {
		strcpy(fname, full_name+1);
		path[i+1] = '\0';
	}

	return(0);

}

/*
  Create a file full_name with the specified contents
*/ 
inode *CreateFile(char *full_name, char *contents) {
	int i;
	int index;
	uint32_t block_count;
	uint32_t inode_count;
	inode *in;
	block *b;
	inode *file_inode = NULL;
	inode *dir_inode = NULL;
	inode *last_inode = NULL;
	inode *inode_head = NULL;
	inode *in2;
	directory *dir;
	char path[MAX_CMD];
	char fname[MAX_CMD];
	int len;

	if (!full_name || !contents) {
		return(NULL);
	}

	bzero(path, MAX_CMD);
	bzero(fname, MAX_CMD);

	if (strlen(fname) > MAX_FILE_NAME_LEN-1) {
		puts("file name too large");
		return(NULL);
	}

	// see if the file already exists
	i = CheckFileExists(full_name, &file_inode);
	if (i == -1) {
		return(NULL);
	} else if (i == 1) {
		// yes, return an error
		puts("file exists");
		return(NULL);
	}

	// see if the required directory path already exists
	SplitPath(full_name, path, fname);
	if (CheckFileExists(path, &dir_inode) != 2) {
		// directory doesn't exist
		puts("directory doesn't exist");
		return(NULL);
	}

	// how many blocks will this content require
	block_count = strlen(contents)/fs.blocksize;
	if (strlen(contents) % fs.blocksize != 0) {
		block_count++;
	}
	// in case someone is creating an empty file
	if (block_count == 0) {
		block_count = 1;
	}

	// will we require multiple inodes?
	inode_count = block_count/INODE_DATA_BLOCKS;
	if (block_count % INODE_DATA_BLOCKS) {
		inode_count++;
	}

	// locate available inode(s)
	for (i = 0; i < inode_count; i++) {
		if ((in = FindFreeInode()) == NULL) { 
			puts("out of inodes");
			return(NULL);
		}
		// grab a pointer to the first inode
		if (i == 0) {
			inode_head = in;
		}
		in->type = INODE_FILE;
		in->fsize = strlen(contents);
		in->num_blocks = block_count;
		if (last_inode) {
			last_inode->indirect_inode = in;
		}
		last_inode = in;
		strncpy(in->fname, fname, MAX_FILE_NAME_LEN-1);
	}

	// locate available data blocks
	in2 = inode_head;
	index = 0;
	for (i = 0; i < block_count; i++, index++) {
		if ((b = FindFreeDataBlock()) == NULL) {
			puts("out of space");
			// free allocated inodes
			while (in2) {
				last_inode = in2;
				in2 = in2->indirect_inode;
				bzero(last_inode, sizeof(inode));
			}
			return(NULL);
		}

		// see if we've filled up the current inode
		if (i && (i % INODE_DATA_BLOCKS == 0)) {
			in2 = in2->indirect_inode;
			index = 0;
		}

		// populate the inodes
		in2->blocks[index] = b;

		// copy the data into each block
		len = strlen(contents+(DATA_BLOCK_SIZE*i));
		memcpy(b, contents+(DATA_BLOCK_SIZE*i), (len > DATA_BLOCK_SIZE) ? 512 : len);

	}

	// update the directory entry
	dir = (directory *)(dir_inode->blocks[0]);
	for (i = 0; i < MAX_DIR_INODES; i++) {
		if (dir->inodes[i] == NULL) {
			dir->inodes[i] = inode_head;
			// update the fsize value
			if ((i+1)*4 > dir_inode->fsize) {
				dir_inode->fsize = (i+1)*4;
			}
			break;
		}
	}
	if (i == MAX_DIR_INODES) {
		// failed to add entry, directory is full
		// free allocated data blocks
		// free allocated inodes
		in2 = inode_head;
		while (in2) {
			last_inode = in2;
			in2 = in2->indirect_inode;
			for (index = 0; index < INODE_DATA_BLOCKS; index++) {
				FreeDataBlock(last_inode->blocks[index]);
			}
			bzero(last_inode, sizeof(inode));
		}
		puts("directory is full");
		return(NULL);
	}

	puts("file created");
	return(inode_head);

}

/*
   Read and print out the contents of a file
 */
int ReadFile(char *full_name) {
	int i,k;
	int index;
	inode *file_inode = NULL;
	block *b;
	unsigned char t[DATA_BLOCK_SIZE+1];
	unsigned char c;
	uint32_t fsize;

	// see if the file already exists
	i = CheckFileExists(full_name, &file_inode);
	if (i == -1) {
		return(1);
	} else if (i == 0) {
		// yes, return an error
		puts("file doesn't exist");
		return(1);
	} else if (i == 2) {
		// it's a directory
		puts("file is a directory");
		return(1);
	}


	index = 0;
	fsize = file_inode->fsize;
	for (i = 0; i < file_inode->num_blocks; i++, index++) {
		if (i && (i % INODE_DATA_BLOCKS == 0)) {
			// move on to the indirect inode
			file_inode = file_inode->indirect_inode;
			if (!file_inode) {
				return(0);;
			}
			index = 0;
		}
		b = file_inode->blocks[index];
		if (!b) {
			return(0);
		}
		if (fsize >= DATA_BLOCK_SIZE) {
			write(b, DATA_BLOCK_SIZE);
			fsize -= DATA_BLOCK_SIZE;
		} else {
			write(b, fsize);
		}
	}	
	puts("");

	return(0);
}

/*
   Make a new directory
 */
int mkdir(char *pathname) {
	int i;
	inode *file_inode;
	inode *dir_inode;
	inode *in;
	inode *last_inode;
	block *b;
	directory *dir;
	char path[MAX_CMD];
	char fname[MAX_CMD];
	int index;

	if (!pathname) {
		return(-1);
	}

	bzero(path, MAX_CMD);
	bzero(fname, MAX_CMD);

	// see if the file already exists
	i = CheckFileExists(pathname, &file_inode);
	if (i == -1) {
		return(-1);
	} else if (i == 1) {
		// yes, return an error
		puts("file exists");
		return(-1);
	} else if (i == 2) {
		// yes, return an error
		puts("directory exists");
		return(-1);
	}

	// make sure the parent directory exists
	SplitPath(pathname, path, fname);
	if (strlen(fname) > MAX_FILE_NAME_LEN-1) {
		puts("file name too large");
		return(-1);
	}
	if (CheckFileExists(path, &dir_inode) != 2) {
		// directory doesn't exist
		puts("parent directory doesn't exist");
		return(-1);
	}

	// locate an available data block
	if ((b = FindFreeDataBlock()) == NULL) {
		puts("out of space");
		// free allocated inodes
		return(-1);
	}

	// locate an available inode
	if ((in = FindFreeInode()) == NULL) { 
		puts("out of inodes");
		return(-1);
	}

	// populate the inode
	in->type = INODE_DIRECTORY;
	in->fsize = 0;
	in->num_blocks = 1;
	in->indirect_inode = NULL;
	strncpy(in->fname, fname, MAX_FILE_NAME_LEN-1);
	in->blocks[0] = b;

	// update the parent directory
	dir = (directory *)(dir_inode->blocks[0]);
#ifdef PATCHED
	for (i = 0; i < MAX_DIR_INODES; i++) {
#else
	for (i = 0; i <= MAX_DIR_INODES; i++) {
#endif
		if (dir->inodes[i] == NULL) {
			dir->inodes[i] = in;
			// update the fsize value
			if ((i+1)*4 > dir_inode->fsize) {
				dir_inode->fsize = (i+1)*4;
			}
			break;
		}
	}
#ifdef PATCHED
	if (i == MAX_DIR_INODES) {
#else
	if (i > MAX_DIR_INODES) {
#endif
		// free inodes and data blocks previously allocated
		while (in) {
			last_inode = in;
			in = in->indirect_inode;
			for (index = 0; index < INODE_DATA_BLOCKS; index++) {
				FreeDataBlock(last_inode->blocks[index]);
			}
			bzero(last_inode, sizeof(inode));
		}
		puts("directory is full");
		return(-1);
	}

	puts("directory created");
	return(0);
}

/* 
   Remove a directory
 */
int rmdir(char *pathname) {
	int i;
	inode *file_inode;
	inode *parent_inode;
	char path[MAX_CMD];
	char fname[MAX_CMD];
	directory *dir;
	int index;
	inode *in2;
	inode *tmp_inode;

	if (!pathname) {
		return(-1);
	}

	bzero(path, MAX_CMD);
	bzero(fname, MAX_CMD);

	// see if the file exists
	i = CheckFileExists(pathname, &file_inode);
	if (i == 0 || i == -1) {
		puts("directory does not exist");
		return(-1);
	}

	// make sure it's a directory
	if (file_inode->type != INODE_DIRECTORY) {
		puts("not a directory");
		return(-1);
	}

	// make sure it isn't the top level dir
	if (!strcmp(pathname, "/")) {
		puts("unable to remove /");	
		return(-1);
	}

	// check that the directory is empty
	dir = (directory *)(file_inode->blocks[0]);
	for (i = 0; i < MAX_DIR_INODES; i++) {
		if (dir->inodes[i] != NULL) {
			puts("directory not empty");
			return(-1);
		}
	}

	// get the parent directory inode
	SplitPath(pathname, path, fname);
	if (CheckFileExists(path, &parent_inode) != 2) {
		puts("parent directory doesn't exist...file system corruption detected");
		return(1);
	}

	// find the directory inode entry and remove it
	dir = (directory *)(parent_inode->blocks[0]);
	for (i = 0; i < MAX_DIR_INODES; i++) {
		if (dir->inodes[i] == file_inode) {
			dir->inodes[i] = NULL;
			// update the fsize value
			if ((i+1)*4 == parent_inode->fsize) {
				parent_inode->fsize = i*4;
			}
			break;
		}
	}
	if (i == MAX_DIR_INODES) {
		puts("parent directory doesn't have an entry for this directory...file system corruption detected");
		return(1);
	}
	
	// free the data blocks associated with the directory
	index = 0;
	in2 = file_inode;
	for (i = 0; i < in2->num_blocks; i++, index++) {
		if (i && (i % INODE_DATA_BLOCKS == 0)) {
			// get a pointer to the next inode (if there is one)
			tmp_inode = in2->indirect_inode;

			// zero/free the current inode
			bzero(in2, sizeof(inode));

			// move on to the next one
			in2 = tmp_inode;
			index = 0;
			if (!in2) {
				break;
			}
		}

		if (in2->blocks[index]) {
			FreeDataBlock(in2->blocks[index]);
		}
	}

	// free the now unused inode
	bzero(file_inode, sizeof(inode));

	puts("directory removed");
	return(0);

}

/*
   Mark as free a given data block
 */
int FreeDataBlock(block *b) {
	int i, j;
	free_t *f;

	if (b == NULL) {
		return(1);
	}

	for (i = 0; i < MAX_FREE_PAGES; i++) {
		f = &(free_list[i]);
		if (b >= &(f->page[0]) && b <= &(f->page[BLOCKS_PER_PAGE-1])) {
			// found the target page
			// figure out which block on the page
			for (j = 0; j < BLOCKS_PER_PAGE; j++) {
				if (b == &(f->page[j])) {
					// found it
					f->in_use ^= (0x80 >> j);
					bzero(f->page[j], DATA_BLOCK_SIZE);
					break;
				}
			}
			if (j == BLOCKS_PER_PAGE) {
				puts("unable to free block");
				return(1);
			}
			break;
		}
	}
	if (i == MAX_FREE_PAGES) {
		puts("unable to free block");
		return(1);
	}

	return(0);
}

/*
   Remove a file
 */
int unlink(char *full_name) {
	int i;
	int index;
	inode *file_inode;
	inode *dir_inode;
	inode *tmp_inode;
	inode *in2;
	char path[MAX_CMD];
	char fname[MAX_CMD];
	directory *dir;

	bzero(path, MAX_CMD);
	bzero(fname, MAX_CMD);

	// make sure the target file exists
	i = CheckFileExists(full_name, &file_inode);
	if (i == -1) {
		return(1);
	} else if (i == 0) {
		// no, return an error
		puts("file doesn't exist");
		return(1);
	} else if (i == 2) {
		// yes, but it's a directory, return an error
		puts("file is a directory");
		return(1);
	}

	// grab a pointer to the parent directory
	SplitPath(full_name, path, fname);
	if (CheckFileExists(path, &dir_inode) != 2) {
		puts("parent directory doesn't exist...file system corruption detected");
		return(1);
	}

	// free the data block(s) pointed to by the inode
	index = 0;
	in2 = file_inode;
	for (i = 0; i < in2->num_blocks; i++, index++) {
		if (i && (i % INODE_DATA_BLOCKS == 0)) {
			// get a pointer to the next inode (if there is one)
			tmp_inode = in2->indirect_inode;

			// zero/free the current inode
			bzero(in2, sizeof(inode));

			// move on to the next one
			in2 = tmp_inode;
			index = 0;
			if (!in2) {
				break;
			}
		}

		if (in2->blocks[index]) {
			FreeDataBlock(in2->blocks[index]);
		}
	}

	// remove the directory inode pointer
	dir = (directory *)(dir_inode->blocks[0]);
	for (i = 0; i < MAX_DIR_INODES; i++) {
		if (dir->inodes[i] == file_inode) {
			dir->inodes[i] = NULL;
			// update the fsize value
			if ((i+1)*4 == dir_inode->fsize) {
				dir_inode->fsize = i*4;
			}
			break;
		}
	}

	// free the now unused inode
	bzero(file_inode, sizeof(inode));

	puts("file removed");
	return(0);
}

/*
   open a file for reading, writing or appending
 */
FILE *fopen(char *path, const char *mode) {
	int i;
	inode *file_inode = NULL;
	FILE *f;
	int mode_val;
	uint32_t inode_depth;
	inode *in2;
	inode *tmp_inode;

	if (!path) {
		return(NULL);
	}

	// make sure the target file exists
	i = CheckFileExists(path, &file_inode);
	if (i == -1) {
		return(NULL);
	} else if (i == 0) {
		// file doesn't exist
		if (!strcmp(mode, "w")) {
			// but this is a 'w' call, so create the file
			if (!(file_inode = CreateFile(path, ""))) {
				puts("file creation failed\n");
				return(NULL);
			}
		} else {
			puts("file doesn't exist");
			return(NULL);
		}
	} else if (i == 2) {
		// yes, but it's a directory, return an error
		puts("file is a directory");
		return(NULL);
	}

	// create and populate a FILE pointer
	if (allocate(sizeof(FILE), 0, (void *)&(f))) {
		puts("Failed to allocate FILE struct\n");
		return(NULL);
	}
	bzero(f, sizeof(FILE));
	f->i = file_inode;
	if (!strcmp(mode, "r")) {
		f->pos = 0;
		f->mode = READ;
		f->curr_pos_inode = file_inode;
	} else if (!strcmp(mode, "w"))  {
		// delete the current file contents
		// all except block[0]
		for (i = 1; i < INODE_DATA_BLOCKS; i++) {
			FreeDataBlock(file_inode->blocks[i]);
			file_inode->blocks[i] = NULL;
		}
		in2 = file_inode->indirect_inode;
		while (in2) {
			// free the inode's data blocks
			for (i = 0; i < INODE_DATA_BLOCKS; i++) {
				FreeDataBlock(in2->blocks[i]);
				in2->blocks[i] = NULL;
			}
			// free the inode itself
			tmp_inode = in2->indirect_inode;
			bzero(in2, sizeof(inode));
			in2 = tmp_inode;
		}

		// zero block[0]
		bzero(file_inode->blocks[0], DATA_BLOCK_SIZE);
		file_inode->fsize = 0;

		f->pos = 0;
		f->mode = WRITE;
		f->curr_pos_inode = file_inode;
	} else if (!strcmp(mode, "a")) {
		f->pos = file_inode->fsize;
		f->mode = APPEND;
		// calculate the inode, block, and offset in that block 
		// where we should start appending
		f->curr_pos_inode = file_inode;
		inode_depth = file_inode->fsize/(INODE_DATA_BLOCKS*DATA_BLOCK_SIZE);
		f->index = (file_inode->fsize % (INODE_DATA_BLOCKS*DATA_BLOCK_SIZE)) / DATA_BLOCK_SIZE;
		f->b_index = (file_inode->fsize % (INODE_DATA_BLOCKS*DATA_BLOCK_SIZE)) % DATA_BLOCK_SIZE;
		while (inode_depth--) {
			f->curr_pos_inode = f->curr_pos_inode->indirect_inode;
		}
	} else {
		deallocate(f, sizeof(FILE));
		return(NULL);
	}

	return(f);
}

/*
   read from the file specified by stream (previously opened with fopen)
*/
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	uint32_t i;
	int index;
	int b_index;
	block *b;
	inode *in2;
	unsigned char *p = (unsigned char *)ptr;

	// input checks
	if (!ptr || !stream) {
		return(0);
	}
	if (stream->mode != READ || !(stream->i)) {
		return(0);
	}

	in2 = stream->curr_pos_inode;
	index = stream->index;
	b = in2->blocks[index];
	b_index = stream->b_index;

	// try to read in the specified number of bytes
	for (i = 0; i < size*nmemb && stream->pos < stream->i->fsize; i++) {
		if (b_index && (b_index % DATA_BLOCK_SIZE == 0)) {
			// move on to the next block
			if (index && (index % INODE_DATA_BLOCKS == 0)) {
				// move on to the next inode
				if (!(in2 = in2->indirect_inode)) {
					// indirect_inode is null, that's bad
					// return what has been read so far
					stream->curr_pos_inode = in2;
					stream->index = index;
					stream->b_index = b_index;
					return(i);
				}
				index = -1;
			}
			index++;
			b = in2->blocks[index];
			if (!b) {
				// block is empty, that's bad
				// return what has been read so far
				stream->curr_pos_inode = in2;
				stream->index = index;
				stream->b_index = b_index;
				return(i);
			}
			b_index = 0;
		}
		p[i] = ((unsigned char *)b)[b_index++];
		stream->pos++;
	}	
	stream->curr_pos_inode = in2;
	stream->index = index;
	stream->b_index = b_index;
	return(i);
}

/*
   write to the file specified by stream (previously opened with fopen)
*/
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
	int i;
	unsigned char *p = (unsigned char *)ptr;
	inode *in;
	inode *in2;
	inode *last_inode;
	int index;
	int b_index;
	block *b;

	// check inputs
	if (!ptr || !stream) {
		return(0);
	}

	// make sure stream is a WRITE or APPEND type
	if (stream->mode != WRITE && stream->mode != APPEND) {
		return(0);
	}

	// write size*nmemb bytes from ptr to the file
	in2 = stream->curr_pos_inode;
	index = stream->index;
	b = in2->blocks[index];
#ifdef PATCHED
	if ( b == NULL) {
		return (0);
	}
#endif

	b_index = stream->b_index;
	for (i = 0; i < size*nmemb; i++) {
		if (b_index && (b_index % DATA_BLOCK_SIZE == 0)) {
			index++;
			// allocate a new block
			if (index && (index % INODE_DATA_BLOCKS == 0)) {
				// since we're writing to the end of the file,
				// the indirect_inode shouldn't be set
				if (in2->indirect_inode) {
					// indirect_inode already set, that's bad
					// return what was written so far
					stream->curr_pos_inode = in2;
					stream->index = index;
					stream->b_index = b_index;
					return(i);
				}

				if ((in = FindFreeInode()) == NULL) { 
					puts("out of inodes");
					return(0);
				}
				in->type = stream->i->type;
				in->fsize = stream->i->fsize;
				in->num_blocks = stream->i->num_blocks;
				in->indirect_inode = NULL;
				strncpy(in->fname, stream->i->fname, MAX_FILE_NAME_LEN-1);

				in2->indirect_inode = in;
				index = 0;
			}

			if ((b = FindFreeDataBlock()) == NULL) {
				puts("out of space");
				stream->curr_pos_inode = in2;
				stream->index = index;
				stream->b_index = b_index;
				// free the just allocated inode
				while (in2) {
					last_inode = in2;
					in2 = in2->indirect_inode;
					bzero(last_inode, sizeof(inode));
				}
				return(i);
			}
			in2->blocks[index] = b;
			b_index = 0;
			stream->i->num_blocks++;
		}
		((unsigned char *)b)[b_index++] = p[i];
		stream->i->fsize++;
		stream->pos++;
	}	
	stream->curr_pos_inode = in2;
	stream->index = index;
	stream->b_index = b_index;
	return(i);
		

	return(i);

}

/* 
   close the file identified by stream
 */
int fclose(FILE *stream) {

	if (!stream) {
		return(-1);
	}

	deallocate(stream, sizeof(FILE));

	return(0);

}

/*
   Get a status of the file system including free inodes and blocks
 */
int StatusFS() {
	int i,j;
	int active_inode_count = 0;
	int active_block_count = 0;
	int active_pages = 0;
	inode *in;
	inode *t;

	// print out superblock info
	printf("Filesystem info:\n");
	printf("  Blocksize: @d\n", fs.blocksize);

	// print out free inodes
	for (i = 0; i < MAX_INODE_PAGES; i++) {
		if (!fs.inode_pages[i]) {
			break;
		}
				
		in = fs.inode_pages[i];
		for (j = 0; j < INODES_PER_PAGE; j++) {
			if (in[j].type != INODE_FREE) {
				active_inode_count++;
			}
		}
	}
	printf("  Used Inodes: @d/@d\n", active_inode_count, MAX_INODE_PAGES*INODES_PER_PAGE);

	// print out free data blocks
	for (i = 0; i < MAX_FREE_PAGES; i++) {
		if (!free_list[i].page) {
			break;
		}
		active_pages++;
		for (j = 0; j < BLOCKS_PER_PAGE; j++) {
			if ((free_list[i].in_use >> j) & 0x01) {
				active_block_count++;
			}
		}
	}
	printf("  Used Blocks: @d/@d\n", active_block_count, fs.fs_size/DATA_BLOCK_SIZE);

	return(0);

}

/*
   obtain a directory listing
*/
int ls(char *pathname) {
	int i;
	inode *in;
	inode *file_inode;
	directory *dir;
	int len;

	if (!pathname) {
		return(-1);
	}

	i = CheckFileExists(pathname, &file_inode);
	if (i == 0) {
		puts("No such directory");
		return(-1);
	} else if (i == 1) {
		puts("File is not a directory");
		return(-1);
	} else if (i == -1) {
		return(-1);
	}

	// get a pointer to the directory contents
	dir = (directory *)(file_inode->blocks[0]);
	if (!dir) {
		return(-1);
	}

	printf("Directory listing of @s\n", pathname);

	// read each directory entry
	for (i = 0; i < MAX_DIR_INODES && (in = dir->inodes[i]); i++) {
		if (in->type == INODE_DIRECTORY) {
			printf("d ");
		} else {
			printf("  ");
		}

		printf("@s", in->fname);
		len = strlen(in->fname);
		len = 50-len;
		while (len-- > 0) {
			printf(" ");
		}
		printf(" @d\n", in->fsize);
	}

	return(0);
}
