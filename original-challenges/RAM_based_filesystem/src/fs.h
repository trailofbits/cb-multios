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

/*
The filesystem is shown graphically below.  The superblock
contiains an array of pointers to the inode pages.  Each inode 
page contains 16 inodes.  Each inode can describe a file
or directory (based on the type var).  Files are made up of 
multiple 512 byte blocks.  A single inode can describe up to
8 of those blocks for a total of 4096 bytes.  If more space
is needed for a given file, the indirect pointer can point
to another inode which provides another 8 blocks and, if 
necessary, another indirect pointer.  Directories use a single
block in the inode.  That block contains an array of
up to 128 inodes describing files or subdirectories.  So, a given
directory is limited to 128 files or subdirectories.  
------------------
| superblock     |
------------------
| magic          | 
| blocksize      |
| fs_size        |    -------------- 
| inode_page[64] | -> | inode_page |
------------------    --------------    ------------------
                      | inode[0]   | -> | inode          |
                      | ...        |    ------------------
                      | inode[15]  |    | fname          |
                      --------------    | type           |
                                        | fsize          |
                                        | num_blocks     |
                                        | indirect_block |    -------------
                                        | blocks[8]      | -> | block     |
                                        ------------------    -------------
                                                              | data[512] |
                                                              -------------
Directory as defined above.
--------------
| directory  |
--------------
| inode[0]   |
| ...        |
| inode[127] |
--------------


An array of 256 elements called the free_list contains pointers
to all of the allocated data pages.  Each page contains 
8 blocks (4096 page size / 8 blocks = 512 byte block size).
As a block is used in an inode, the free_mask is marked with a
'1' in the corresponding bit position for the block in the page.
So, for example, block[0] being used would result in a mask
value of 0x80.
-------------
| free_list |
-------------
| free_mask |    -------------
| page      | -> | page      |
-------------    -------------
                 | block[0]  |
                 | ...       |
                 | block[15] |    
                 -------------

*/
#define PAGE_SIZE 4096
#define MAX_CMD 256

// block
#define DATA_BLOCK_SIZE 512
typedef unsigned char block[DATA_BLOCK_SIZE];

// inode
#define INODE_FREE 0
#define INODE_FILE 1
#define INODE_DIRECTORY 2
#define INODE_DATA_BLOCKS 8
#define MAX_FILE_NAME_LEN 208
// sizeof(inode) = 256 for convenience of 4096 byte page sizes
typedef struct _inode {
	char fname[MAX_FILE_NAME_LEN];
	uint32_t type;
	uint32_t fsize;
	uint32_t num_blocks;
	struct _inode *indirect_inode;
	block *blocks[INODE_DATA_BLOCKS];
} inode;

// superblock
#define CRFS 0x43524653
#define MAX_INODE_PAGES 64
#define INODES_PER_PAGE 16
typedef struct _superblock {
	uint32_t magic;
	uint32_t blocksize;
	uint32_t fs_size;
	inode *inode_pages[MAX_INODE_PAGES];
} superblock;

// global pointer to our filesystem
superblock fs;

// free blocks
#define MAX_FREE_PAGES 256
#define MAX_FS_SIZE PAGE_SIZE*MAX_FREE_PAGES
#define BLOCKS_PER_PAGE 8
typedef struct _free_t {
	uint8_t in_use;
	block *page;
} free_t;
free_t free_list[MAX_FREE_PAGES];

// directory
#define MAX_DIR_INODES 128
typedef struct _directory {
	inode *inodes[MAX_DIR_INODES];
} directory;

// FILE struct
#define READ 0
#define WRITE 1
#define APPEND 2
typedef struct _FILE {
	inode *i;
	uint32_t pos;
	uint32_t mode;
	inode *curr_pos_inode;
	uint32_t index;
	uint32_t b_index;
} FILE;

int InitFS(uint32_t);
int DestroyFS();
inode *CreateFile(char *, char *);
inode *FindInode(char *);
int CheckFileExists(char *, inode **);
int SplitPath(char *, char *, char *);
int ReadFile(char *);
int FreeDataBlock(block *);
int mkdir(char *);
int rmdir(char *);
int unlink(char *);
FILE *fopen(char *, const char *);
size_t fread(void *, size_t, size_t, FILE *);
size_t fwrite(const void *, size_t, size_t, FILE *);
int fclose(FILE *);
int StatusFS();
int ls(char *);
