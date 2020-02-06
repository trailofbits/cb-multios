/*

Author: Steve Wood <swood@cromulence.com>

Copyright (c) 2016 Cromulence LLC

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
#include "cgc_filesystem.h"
#include "cgc_stdio.h"
#include "cgc_string.h"
#include "cgc_stdlib.h"
#include "cgc_malloc.h"


// Globals for handles to the filesystem objects
void *fileSystem;
mbStructType *masterBlocks;
unsigned char *freeList;
rootDirType *rootDir;
fileCursorType fileCursors[MAX_OPEN_FILES];


// internally used functions
void cgc_setBlockInUse( unsigned int blockNum );
void cgc_setBlockAsFree( unsigned int blockNum );
unsigned int cgc_findFreeBlock( unsigned int *blockNum );
void cgc_eraseBlock( unsigned int blockNum );
unsigned int cgc_addNewBlock(fileHandleType fh); 
int cgc_writeBlock(void *blockData, unsigned int blockNum);
int cgc_readBlock(unsigned int blockNum, void **buffer); 
int cgc_wildcard_search(char *search, char *target);
int cgc_readMemoryFile(fileHandleType fh, char *buffer, unsigned int size, unsigned int *numRead );
int cgc_writeMemoryFile(fileHandleType fh, char *buffer, unsigned int size );

int cgc_initFileSystem( unsigned int sectorSize, unsigned int blockSize, unsigned int totalSize) {
	
unsigned int numSectors;
unsigned int numBlocks;
int retval;

	
	if (blockSize % sectorSize != 0) {

		return ERROR_BAD_GEOMETRY;

	}

	numBlocks = totalSize / blockSize;
	numSectors = totalSize / sectorSize;

	if (numBlocks > blockSize * 8) {

		return ERROR_BAD_GEOMETRY;

	}

	retval = cgc_allocate(totalSize, 0, &fileSystem);

	if (retval == EINVAL) {

		return ERROR_BAD_SIZE;

	}

	if (retval != 0) {

		return ERROR_BAD_GEOMETRY;

	}

	// if we got here, we have a suitable block of memory
	cgc_bzero(fileSystem, totalSize);

	// put the masterBlocks into the first block of the filesystem
	masterBlocks = (mbStructType *)fileSystem;

	masterBlocks->mblock0.inUse = 1;
	masterBlocks->mblock0.totalSize = totalSize;
	masterBlocks->mblock0.blockSize = blockSize;
	masterBlocks->mblock0.totalBlocks = numBlocks;
	masterBlocks->mblock0.rootDirBlock = 2;
	masterBlocks->mblock0.freeListBlock = 1;

#ifdef PATCHED_1
	masterBlocks->mblock0.dirEntriesPerBlock = (blockSize - 8)/sizeof(directoryEntryType);
#else
	masterBlocks->mblock0.dirEntriesPerBlock = blockSize /sizeof(directoryEntryType);
#endif
	masterBlocks->mblock0.blockEntriesPerCatalog = (blockSize - 8) / sizeof(int);
	masterBlocks->mblock0.checkValue = 0;    // unused for now

	// mblock1 and mblock2 unused for now

	// and the freelist in the second block of the filesystem
	freeList = (unsigned char *)(fileSystem + blockSize);

	// and the root directory to the third
	rootDir = (rootDirType *)(fileSystem + (blockSize * 2));


	// make sure these blocks are marked as in use
	cgc_setBlockInUse(0);  // master block
	cgc_setBlockInUse(1);  // free list block
	cgc_setBlockInUse(2);  // root directory

	// now setup the root directory

	// calculate the max number of entries given the size of a block, minus the space for a link to the next block
	rootDir->maxEntries = (blockSize - 8)/sizeof(directoryEntryType);

	rootDir->numEntries = 0;

	cgc_bzero( fileCursors, sizeof(fileCursors));

	return NO_ERROR;

}


// returns 0 if file found, -1 if not found
int cgc_statusFile(char *name, fileInfoType *info) {

int i;

	// if the filename is empty
	if ( name == 0 ) {

		return ERROR_BAD_VALUE;

	}

	// if the root dir is invalid, just return
	if ( rootDir == 0 ) {

		return ERROR_INIT;

	}

	for ( i = 0; i < rootDir->maxEntries; ++i ) {

		if ( cgc_strcmp(rootDir->entry[i].name, name) == 0) {


			if (info != 0 ) {

				info->size = rootDir->entry[i].fileSize;
				info->type = rootDir->entry[i].fileType;
			}

			return NO_ERROR;

		} // if strcmp

	}  // for

	return -1;

}

fileHandleType cgc_openFile(char *name, securityIdType securityID) {

int i;
int x;

	if (name == 0) 
		return ERROR_BAD_VALUE;

	if ( rootDir == 0)
		return ERROR_INIT;

	for ( i = 0; i < rootDir->maxEntries; ++i ) {

		// found a matching name in the directory
		if ( cgc_strcmp(rootDir->entry[i].name, name) == 0) {


			// if this file doesn't belong to this user and the user isn't "root"
			if ( securityID != ROOT_ID && rootDir->entry[i].securityID != securityID ) {

				// are any "others permissions" assigned?
				if ( rootDir->entry[i].othersPermissions == 0 ) {

					return ERROR_NO_PERMISSION;
				}
			}

			// first make sure there's not already an open handle to this file
			for (x = 0; x < MAX_OPEN_FILES; ++x ) {

				if (fileCursors[x].inUse == 1 && fileCursors[x].dirEntryNum == i) {

					return ERROR_FILE_OPEN;
				}

			}

			// find a free fileCursor and assign it to this file
			for ( x = 0; x < MAX_OPEN_FILES; ++x ) {

				if (fileCursors[x].inUse == 0)
					break;
			}

			if (x == MAX_OPEN_FILES)
				return ERROR_MAX_EXCEEDED;

			// default to reading from the beginning of the file, and writing at the end
			fileCursors[x].inUse = 1;
			fileCursors[x].dirEntryNum = i;
			fileCursors[x].readBlockNum = 0;
			fileCursors[x].writeBlockNum = 0;
			fileCursors[x].readPos = 0;
			fileCursors[x].writePos = 0;
			fileCursors[x].fileSize = rootDir->entry[i].fileSize;
			fileCursors[x].securityID = rootDir->entry[i].securityID;
			fileCursors[x].othersPermissions = rootDir->entry[i].othersPermissions;
			fileCursors[x].fileType = rootDir->entry[i].fileType;

			// if the file has data in it, position the cgc_write cursor at the end
			if (rootDir->entry[i].fileSize > 0) {
				
				fileCursors[x].writeBlockNum = rootDir->entry[i].fileSize / masterBlocks->mblock0.blockSize;
				fileCursors[x].writePos = rootDir->entry[i].fileSize;

			}

			return x;

		} // if strcmp

	}  // for

return (ERROR_NOT_FOUND);

}

int cgc_setPerms(fileHandleType fh, otherPermsType othersPermissions, securityIdType securityID) {


	if (fh > MAX_OPEN_FILES) {

		return ERROR_BAD_HANDLE;
	}

	if (fileCursors[fh].inUse == 0) {
	
		return ERROR_BAD_HANDLE;
	}

	if ( securityID != fileCursors[fh].securityID && securityID != ROOT_ID )  {

		return ERROR_NO_PERMISSION;
	}

	if ( othersPermissions > 3 ) {

		return ERROR_BAD_VALUE;
	}

	fileCursors[fh].othersPermissions = othersPermissions;

	return NO_ERROR;

}


int cgc_closeFile(fileHandleType fh) {


	if (fh > MAX_OPEN_FILES)
		return ERROR_BAD_HANDLE;

	if (fileCursors[fh].inUse == 0)
		return ERROR_BAD_HANDLE;

	cgc_flushFile(fh);

	fileCursors[fh].inUse = 0;
	fileCursors[fh].dirEntryNum = 0;
	fileCursors[fh].writePos = 0;
	fileCursors[fh].readPos = 0;
	fileCursors[fh].fileSize = 0;
	fileCursors[fh].othersPermissions = 0;

	return NO_ERROR;

}


int cgc_createFile(char *name, enum fileTypes type, securityIdType securityID) {

int i;
unsigned int catalogBlock;


	// if no filename give, return error
	if ( name == 0 ) {

		return ERROR_BAD_VALUE;

	}

	// if the root directory is invalid, return error
	if ( rootDir == 0 ) {

		return ERROR_INIT;

	}

	// if the file already exists, return error
	if ( cgc_statusFile(name, 0) == 0 ) {

		return ERROR_FILE_EXISTS;

	}

	// find the first empty directory entry

	for ( i = 0; i < masterBlocks->mblock0.dirEntriesPerBlock; ++i ) {

		if ( rootDir->entry[i].name[0] == 0) {

			cgc_strncpy(rootDir->entry[i].name, name, MAX_FILENAME_LEN);
			rootDir->entry[i].fileSize = 0;
			rootDir->entry[i].fileType = type;
			rootDir->entry[i].securityID = securityID;
			rootDir->entry[i].othersPermissions = 0;

			// now allocate a block for its first catalog block

			if (cgc_findFreeBlock(&catalogBlock) == 0 ) {

				cgc_eraseBlock(catalogBlock);

				cgc_setBlockInUse(catalogBlock);

				rootDir->entry[i].firstCatalogBlock = catalogBlock;

			}
			else {

				return ERROR_NO_BLOCKS;
			
			}

			rootDir->numEntries++;
			return NO_ERROR;

		} // if strcmp

	}  // for

	return ERROR_MAX_EXCEEDED;

}


int cgc_writeFile(fileHandleType fh, char *buffer, unsigned int size, securityIdType securityID) {

unsigned int leftToWrite;
unsigned int writePtr;
unsigned int blockOffset;
unsigned int writePos;
unsigned char *blockBuffer;
unsigned int blockSize;
void *blockForWrite;
unsigned int blockNumForWrite;
unsigned int remainingBlockSpace;
unsigned int dirEntry;
unsigned int *catalogBlock;
unsigned int blockIndexForWrite;
int retval;
int writeLength;
char tmpbuffer[32];
int retcode;

	if (fh > MAX_OPEN_FILES) {

		return ERROR_BAD_HANDLE;

	}

	if (fileCursors[fh].inUse == 0) {

		return ERROR_BAD_HANDLE;

	}

	if (buffer == 0) {

		return ERROR_BAD_VALUE;

	}

	if (size == 0) {

		return ERROR_BAD_VALUE;

	}

	if ( (securityID != fileCursors[fh].securityID) && securityID != ROOT_ID && (fileCursors[fh].othersPermissions&0x01) == 0) {

		return ERROR_NO_PERMISSION;
	}


	// treat a memory file specially 
	if (fileCursors[fh].fileType > 2 ) {

		retcode=cgc_writeMemoryFile( fh, buffer, size );

		return retcode;

	}


	leftToWrite = size;
	writePos = fileCursors[fh].writePos;

	// get a local of the blocksize just to keep code more readable
	blockSize = masterBlocks->mblock0.blockSize;

	while(leftToWrite > 0) {

		blockOffset = writePos % blockSize;

		// if blockOffset is 0 then a new block for writing needs to be allocated, unless we 
		// aren't at the end of the file

		if (blockOffset == 0 && writePos == fileCursors[fh].fileSize) {

			if (cgc_addNewBlock(fh) == -1) {

				return ERROR_NO_BLOCKS;

			}

		}

		// cgc_read block where writing will happen and go from there
		dirEntry = fileCursors[fh].dirEntryNum;

		// cgc_read the catalog for this file
		if (cgc_readBlock(rootDir->entry[dirEntry].firstCatalogBlock, (void **)&catalogBlock) != 0) {

			return ERROR_READ_ERROR;

		}

		blockNumForWrite = *(unsigned int *)(catalogBlock + (writePos / blockSize));

		cgc_deallocate(catalogBlock, blockSize);

		writeLength = cgc_minimum(blockSize - blockOffset, leftToWrite);

		if (cgc_readBlock(blockNumForWrite, &blockForWrite)!=0) {

			return ERROR_READ_ERROR;

		}

		cgc_memcpy(blockForWrite+blockOffset, buffer, writeLength);

		cgc_writeBlock(blockForWrite, blockNumForWrite);

		// free the memory for the buffer
		cgc_deallocate(blockForWrite, blockSize);

		leftToWrite -= writeLength;

		fileCursors[fh].fileSize += writeLength - (fileCursors[fh].fileSize - writePos);

		writePos += writeLength;

	}

	fileCursors[fh].writePos = writePos;

	return NO_ERROR;

}

// cgc_read up to size bytes from the file.  Stops reading if the end of file is reached.
// returns the actual number of bytes cgc_read, or -1 on error
int cgc_readFile(fileHandleType fh, char *buffer, unsigned int size, int relPosition, unsigned int *numRead, securityIdType securityID) {

int i;
int retval;
unsigned int leftToRead;
unsigned int bytesRead;
unsigned int readPos;
unsigned int blockIndexToRead;
unsigned int blockNumForRead;
void *blockToRead;
unsigned int *catalogBlock;
unsigned int dirEntry;
unsigned int readOffset;
unsigned int amountToRead;
unsigned int blockSize;
unsigned int remainingInFile;
unsigned int remainingInBlock;
int offset;
int retcode;

	*numRead = 0;

	if (fh > MAX_OPEN_FILES) {

		return ERROR_BAD_HANDLE;

	}

	if (fileCursors[fh].inUse == 0) {

		return ERROR_BAD_HANDLE;

	}

	if (buffer == 0) {

		return ERROR_BAD_VALUE;

	}

	if (size == 0) {

		return ERROR_BAD_VALUE;

	}

	if ( (securityID != fileCursors[fh].securityID) && securityID != ROOT_ID && (fileCursors[fh].othersPermissions&0x02) == 0) {

		return ERROR_NO_PERMISSION;
	}

	// treat a memory file specially 
	if (fileCursors[fh].fileType > 2 ) {

		retcode=cgc_readMemoryFile( fh, buffer, size, numRead );

		return retcode;

	}

	leftToRead = size;
	bytesRead = 0;

	if (relPosition != 0) {

		offset = relPosition;
	
		if (cgc_fileReadPosRelative(fh, offset) != 0 ) {

			return ERROR_BAD_VALUE;
	
		}		

	}

	// cgc_read the catalog of blocks for this file
	dirEntry = fileCursors[fh].dirEntryNum;
	
	readPos = fileCursors[fh].readPos;

	// get a local of the blocksize just to keep code more readable
	blockSize = masterBlocks->mblock0.blockSize;

	while(leftToRead) {

		// use the directory entry, not the fileCursor so that we get updated fileSize of writes occur.
		if (readPos == rootDir->entry[dirEntry].fileSize) {

			break;

		}

		// find what the relative (not the absolute) block number is
		// the later will be looked up in the block catalog for this file
		blockIndexToRead = readPos / blockSize;

		// cgc_read the catalog for this file
		// re-cgc_read it every time because it could also get written to, extending the EOF
		if (cgc_readBlock(rootDir->entry[dirEntry].firstCatalogBlock, (void **)&catalogBlock)!= 0) {

			return ERROR_READ_ERROR;

		}

		blockNumForRead = *(unsigned int *)(catalogBlock + blockIndexToRead);

		cgc_deallocate(catalogBlock, blockSize);

		if (cgc_readBlock(blockNumForRead, &blockToRead)!= 0) {

			return ERROR_READ_ERROR;

		}

		// now there are three cases on how much memory to copy--the smallest of:
		// 1) the remaining data in this block from the calculated offset
		// 2) the remaining data in this cgc_read request
		// 3) until the end of file is reached

		readOffset = readPos % blockSize;

		remainingInBlock = blockSize - readOffset;
		remainingInFile = rootDir->entry[dirEntry].fileSize - readPos;

		amountToRead = cgc_minimum( cgc_minimum(remainingInFile, remainingInBlock), leftToRead);

		cgc_memcpy(buffer+bytesRead, blockToRead+readOffset, amountToRead);

		// we are done with this block so release the memory
		cgc_deallocate((void *)blockToRead, blockSize);

		bytesRead += amountToRead;
		leftToRead -= amountToRead;
		readPos += amountToRead;


	} // while

	fileCursors[fh].readPos = readPos;
	*numRead = bytesRead;

	if (readPos == rootDir->entry[dirEntry].fileSize) {

		return ERROR_EOF;

	}
	else {

		return NO_ERROR;
	}
}

int cgc_readMemoryFile(fileHandleType fh, char *buffer, unsigned int size, unsigned int *numRead ) {

unsigned int *catalogBlock;
unsigned int copySize;

struct memoryFileInfo { 
	unsigned int address;
	unsigned int size;
	char accessType;

	} *memoryInfo;

	// all security validation has already been done, so just skip to reading

	// first load the memory region info from the special catalogblock
	if (cgc_readBlock(rootDir->entry[fileCursors[fh].dirEntryNum].firstCatalogBlock, (void **)&catalogBlock)!= 0) {

		return ERROR_READ_ERROR;

	}

	memoryInfo= (struct memoryFileInfo *)catalogBlock;

	// validate that the request is valid in terms of size and cgc_read position in the block
	if (fileCursors[fh].readPos >= fileCursors[fh].fileSize ) {

		return ERROR_EOF;

	}


	copySize = cgc_minimum(size, fileCursors[fh].fileSize - fileCursors[fh].readPos);

	// copy the memory into the buffer and return
	cgc_memcpy(buffer, (void *)memoryInfo->address+fileCursors[fh].readPos, copySize);

	*numRead = copySize;

	fileCursors[fh].readPos += copySize;

	// free the catalog block
	cgc_deallocate(catalogBlock, masterBlocks->mblock0.blockSize);

	if (fileCursors[fh].readPos >= fileCursors[fh].fileSize ) {

		return ERROR_EOF;

	}
	else {

	return NO_ERROR;

	}
}

int cgc_writeMemoryFile(fileHandleType fh, char *buffer, unsigned int size ) {

unsigned int *catalogBlock;
unsigned int copySize;

struct memoryFileInfo { 
	unsigned int address;
	unsigned int size;
	char accessType;

	} *memoryInfo;

	// all security validation has already been done, so just skip to writing

	// first load the memory region info from the special catalogblock
	if (cgc_readBlock(rootDir->entry[fileCursors[fh].dirEntryNum].firstCatalogBlock, (void **)&catalogBlock)!= 0) {

		return ERROR_READ_ERROR;

	}

	memoryInfo= (struct memoryFileInfo *)catalogBlock;

	// validate that the request is valid in terms of size and cgc_read position in the block
	if (size > fileCursors[fh].fileSize ) {

		return ERROR_BAD_SIZE;

	}

	// copy the memory into the buffer and return
	cgc_memcpy((void *)memoryInfo->address, buffer, size);


	fileCursors[fh].fileSize = size;

	// free the catalog block
	cgc_deallocate(catalogBlock, masterBlocks->mblock0.blockSize);

	return NO_ERROR;

}

// Updates the open fileCursor and directory entry to reflect any writes that have occurred.  
int cgc_flushFile(fileHandleType fh) {

	if (fh > MAX_OPEN_FILES) {

		return ERROR_BAD_HANDLE;
	}

	if (fileCursors[fh].inUse == 0) {

		return ERROR_BAD_HANDLE;
	}

	if (rootDir == 0 ) {

		return ERROR_INIT;
	}

	rootDir->entry[fileCursors[fh].dirEntryNum].fileSize = fileCursors[fh].fileSize;
	rootDir->entry[fileCursors[fh].dirEntryNum].othersPermissions = fileCursors[fh].othersPermissions;

	return NO_ERROR;
}

// update the fileCursor's cgc_read pointer to the offset specified
int cgc_fileReadPosition(fileHandleType fh, unsigned int offset) {

	if (fh > MAX_OPEN_FILES) {

		return ERROR_BAD_HANDLE;
	}

	if (fileCursors[fh].inUse == 0) {

		return ERROR_BAD_HANDLE;
	}

	if (offset > fileCursors[fh].fileSize) {

		return ERROR_BAD_VALUE;
	}

	fileCursors[fh].readPos = offset;

	return NO_ERROR;

}

// update the fileCursor's cgc_read pointer relative to the current value
int cgc_fileReadPosRelative(fileHandleType fh, int offset) {

	if (fh > MAX_OPEN_FILES) {

		return ERROR_BAD_HANDLE;
	}

	if (fileCursors[fh].inUse == 0) {

		return ERROR_BAD_HANDLE;
	}

	if (fileCursors[fh].readPos + offset > fileCursors[fh].fileSize) {

		return ERROR_BAD_VALUE;

	}

	if ((int)fileCursors[fh].readPos + offset < 0 ) {

		fileCursors[fh].readPos = 0;

	}
	else {

		fileCursors[fh].readPos += offset;

	}

	return NO_ERROR;
}

// update the fileCursor's cgc_write pointer to the absolute value
// going beyond the end of file is an error
int cgc_fileWritePosition(fileHandleType fh, unsigned int offset) {

	if (fh > MAX_OPEN_FILES) {

		return ERROR_BAD_HANDLE;
	}

	if (fileCursors[fh].inUse == 0) {

		return ERROR_BAD_HANDLE;
	}

	if (offset > fileCursors[fh].fileSize) {

		return ERROR_BAD_VALUE;
	}

	fileCursors[fh].writePos = offset;

	return NO_ERROR;
}

// update the cgc_write position relative to the current value
int cgc_fileWritePosRelative(fileHandleType fh, int offset) {

	if (fh > MAX_OPEN_FILES) {

		return ERROR_BAD_HANDLE;
	}

	if (fileCursors[fh].inUse == 0) {

		return ERROR_BAD_HANDLE;
	}

	if (fileCursors[fh].writePos + offset > fileCursors[fh].fileSize) {

		return ERROR_BAD_VALUE;

	}

	if ((int)fileCursors[fh].writePos + offset < 0 ) {

		fileCursors[fh].writePos = 0;

	}
	else {

		fileCursors[fh].writePos += offset;

	}

	return NO_ERROR;

}

int cgc_deleteFile( fileHandleType fh, securityIdType securityID ) {

unsigned int dirEntry;
unsigned int *catalogBlock;
unsigned int *entryPtr;
int retval;

struct memoryFileInfo { 
	unsigned int address;
	unsigned int size;
	char accessType;

	} *memoryInfo;

	if (fh > MAX_OPEN_FILES) {

		return ERROR_BAD_HANDLE;
	}

	if (fileCursors[fh].inUse == 0) {

		return ERROR_BAD_HANDLE;
	}

	if ( (securityID != fileCursors[fh].securityID) && securityID != ROOT_ID && (fileCursors[fh].othersPermissions&0x01) == 0) {

		return ERROR_NO_PERMISSION;

	}

	// cgc_read the catalog of blocks for this file
	dirEntry = fileCursors[fh].dirEntryNum;
	
	// cgc_read the catalog for this file
	retval = cgc_readBlock(rootDir->entry[dirEntry].firstCatalogBlock, (void **)&catalogBlock);

	if (retval != 0) {

		return ERROR_READ_ERROR;

	}

	if ( fileCursors[fh].fileType > 2 ) {

		memoryInfo = (struct memoryFileInfo *)catalogBlock;

		if (memoryInfo->address > 0 ) {

			cgc_free((void *)memoryInfo->address);

		}

	}
	else {
	entryPtr = catalogBlock;

		while(*entryPtr != 0) {

			cgc_eraseBlock(*entryPtr);
			cgc_setBlockAsFree(*entryPtr);
			++entryPtr;
		}
	}

	cgc_deallocate((void *)catalogBlock, masterBlocks->mblock0.blockSize);

	cgc_eraseBlock(rootDir->entry[dirEntry].firstCatalogBlock);

	cgc_setBlockAsFree(rootDir->entry[dirEntry].firstCatalogBlock);

	rootDir->entry[dirEntry].name[0] = 0;
	rootDir->entry[dirEntry].fileSize = 0;
	rootDir->entry[dirEntry].firstCatalogBlock = 0;
	rootDir->numEntries--;

	fileCursors[fh].dirEntryNum = 0;
	fileCursors[fh].inUse = 0;
	fileCursors[fh].writePos = 0;
	fileCursors[fh].readPos = 0;
	fileCursors[fh].fileSize = 0;
	fileCursors[fh].othersPermissions = 0;

	return NO_ERROR;
}


int cgc_truncateFile( fileHandleType fh, securityIdType securityID ) {

unsigned int dirEntry;
unsigned int *catalogBlock;
unsigned int *entryPtr;
int retval;

	if (fh > MAX_OPEN_FILES) {

		return ERROR_BAD_HANDLE;
	}

	if (fileCursors[fh].inUse == 0) {

		return ERROR_BAD_HANDLE;
	}

	// if its a memory file, just return
	if (fileCursors[fh].fileType > 2 ) {

		return NO_ERROR;

	}

	if ( (securityID != fileCursors[fh].securityID) && securityID != ROOT_ID && (fileCursors[fh].othersPermissions&0x01) == 0) {

		return ERROR_NO_PERMISSION;

	}

	// cgc_read the catalog of blocks for this file
	dirEntry = fileCursors[fh].dirEntryNum;
	
	// cgc_read the catalog for this file
	retval = cgc_readBlock(rootDir->entry[dirEntry].firstCatalogBlock, (void **)&catalogBlock);

	if (retval != 0) {

		return ERROR_READ_ERROR;

	}

	entryPtr = catalogBlock;

	while(*entryPtr != 0) {

		cgc_eraseBlock(*entryPtr);

		cgc_setBlockAsFree(*entryPtr);

		++entryPtr;
	}

	cgc_deallocate((void *)catalogBlock, masterBlocks->mblock0.blockSize);

	cgc_eraseBlock(rootDir->entry[dirEntry].firstCatalogBlock);

	rootDir->entry[dirEntry].fileSize = 0;

	fileCursors[fh].writePos = 0;
	fileCursors[fh].readPos = 0;
	fileCursors[fh].readBlockNum = 0;
	fileCursors[fh].writeBlockNum = 0;
	fileCursors[fh].fileSize = 0;

	return NO_ERROR;
}


int cgc_findFiles( char *filespec, findFileHandleType **findFileHandle ) {

int i;
directoryEntryType *currentFile;
char strcmpbuffer[MAX_FILENAME_LEN+1];
char tempbuffer[24];

static findFileHandleType fileHandle;

	if (rootDir == 0) {

		return ERROR_INIT;

	}

	currentFile = &rootDir->entry[0];

	for ( i = 0; i < rootDir->maxEntries; ++i ) {

		if (currentFile->name[0] != 0 ) {

			// nulls aren't necessariy stored in the directory if the filename has max length
			// so make a copy that we can use with the wildcard search function
			cgc_strncpy(strcmpbuffer, currentFile->name, MAX_FILENAME_LEN);
			strcmpbuffer[MAX_FILENAME_LEN] = 0;

			// now match against the filespec
			if (filespec[0] != 0 && cgc_wildcard_search(filespec, strcmpbuffer) != 1) {
				currentFile++;
				continue;
			}

			// its a match so copy it into another buffer so the caller doesn't get direct 
			// access to the real directory structure

			fileHandle.currentFile = currentFile;
			cgc_strncpy(fileHandle.filespec, filespec, MAX_FILENAME_LEN);

			*findFileHandle = &fileHandle;

			return NO_ERROR;

		} // if
		currentFile++;

	} // for

	return ERROR_NOT_FOUND;

} 

int cgc_findNextFile( findFileHandleType *findFileHandle) {

	if (findFileHandle == 0) {

		return ERROR_NOT_FOUND;

	}

	while(findFileHandle->currentFile < &rootDir->entry[rootDir->maxEntries]) {

		findFileHandle->currentFile++;

		if (findFileHandle->currentFile->name[0] != 0) {

			if (findFileHandle->filespec[0] != 0 && cgc_wildcard_search(findFileHandle->filespec, findFileHandle->currentFile->name ) != 1) {

				continue;
			}

			return NO_ERROR;

		}
	}

	return ERROR_NOT_FOUND;

}

void cgc_eraseBlock( unsigned int blockNum) {
unsigned int blockSize;

	blockSize = masterBlocks->mblock0.blockSize;
	cgc_bzero((unsigned char *)(fileSystem + (blockSize * blockNum)), blockSize);

}

void cgc_setBlockInUse(unsigned int blockNum) {

int byteNum;
int bitNum;

	byteNum = blockNum / 8;
	bitNum = blockNum % 8;

	freeList[byteNum] |= (1 << bitNum);

}

void cgc_setBlockAsFree(unsigned int blockNum) {

int byteNum;
int bitNum;

	byteNum = blockNum / 8;
	bitNum = blockNum % 8;

	freeList[byteNum] &=  (~(1 << bitNum));

}

unsigned int cgc_findFreeBlock(unsigned int *blockNum) {

int i;
int x;
unsigned char tempByte;

	if (blockNum == 0) {

		return ERROR_BAD_VALUE;

	}

	for (i=0; i < masterBlocks->mblock0.blockSize; ++i) {

		if (freeList[i] != 0xff) {

			break;

		}
	}

	if (i >= masterBlocks->mblock0.totalBlocks) {

		return ERROR_NO_BLOCKS;

	}

	tempByte = freeList[i];

	for (x=0; x < 8; ++x) {

		if ((tempByte & 0x01) == 0)
			break;
		else
			tempByte = tempByte >> 1;

	}

	*blockNum = i * 8 + x;

	if (*blockNum >= masterBlocks->mblock0.totalBlocks) {

		return ERROR_NO_BLOCKS;

	}

	return NO_ERROR;

}

int cgc_getFileSystemInfo(fileSystemInfoType *fsInfo) {

	if ( fsInfo == 0 ) {

		return ERROR_BAD_VALUE;
	}

	if ( masterBlocks == 0 ) {

		return ERROR_INIT;

	}

	fsInfo->totalSize = masterBlocks->mblock0.totalSize;
	fsInfo->blockSize = masterBlocks->mblock0.blockSize;
	fsInfo->totalBlocks = masterBlocks->mblock0.totalBlocks;
	fsInfo->freeBlocks = 0;
	fsInfo->maxEntriesPerDirectory = masterBlocks->mblock0.dirEntriesPerBlock;
	fsInfo->maxBlocksPerFile = masterBlocks->mblock0.blockEntriesPerCatalog;

	return NO_ERROR;

}

int cgc_readBlock(unsigned int blockNum, void **buffer) {

void *blockData;
unsigned int blockSize;
int retval;


	if (fileSystem == 0)
		return ERROR_INIT;

	blockSize = masterBlocks->mblock0.blockSize;

	retval = cgc_allocate(blockSize, 0, &blockData);

	if (retval == EINVAL) {

		return ERROR_BAD_SIZE;

	}

	if (retval != 0) {

		return ERROR_BAD_GEOMETRY;

	}

	cgc_memcpy(blockData, (fileSystem + (blockSize * blockNum)), blockSize);

	*buffer = blockData;

	return NO_ERROR;

}

int cgc_writeBlock(void *blockData, unsigned int blockNum) {

unsigned int blockSize;

	if (fileSystem == 0) {

		return ERROR_INIT;
	
	}
	
	blockSize = masterBlocks->mblock0.blockSize;

	cgc_memcpy(fileSystem + (blockSize * blockNum), blockData, blockSize);

	return NO_ERROR;

}


unsigned int cgc_addNewBlock(fileHandleType fh) {

unsigned int newBlockNum;
void *catalogBlock;
unsigned int dirEntry;
int i;
int retval;
	
	if (fh > MAX_OPEN_FILES) {

		return ERROR_BAD_HANDLE;

	}

	if (fileCursors[fh].inUse == 0) {

		return ERROR_BAD_HANDLE;

	}

	dirEntry = fileCursors[fh].dirEntryNum;

	// cgc_read the catalog for this file
	retval = cgc_readBlock(rootDir->entry[dirEntry].firstCatalogBlock, &catalogBlock);

	if (retval != 0) {

		return ERROR_READ_ERROR;

	}

	for (i=0; i < masterBlocks->mblock0.blockEntriesPerCatalog; ++i) {

		if (*((unsigned int *)(catalogBlock)+i) == 0)
			break;
	}

	if (i == masterBlocks->mblock0.blockEntriesPerCatalog) {

		return -1;

	}

	if (cgc_findFreeBlock(&newBlockNum) != NO_ERROR) {

		return ERROR_NO_BLOCKS;

	}

	cgc_setBlockInUse(newBlockNum);

	// add this new block to the catalog for this file
	*((unsigned int *)catalogBlock+i) = newBlockNum;

	// and cgc_write the block back 
	cgc_writeBlock(catalogBlock, rootDir->entry[dirEntry].firstCatalogBlock);

	// release the memory allocated by readBlock
	cgc_deallocate(catalogBlock, masterBlocks->mblock0.blockSize);

	return newBlockNum;

}

int cgc_makeMemoryFile(char *name, unsigned int address, unsigned int length, char accessType, securityIdType securityID ) {

int i;
unsigned int catalogBlock;
struct { 
	unsigned int address;
	unsigned int size;
	char accessType;

	} *memoryFileInfo;

	// if no filename give, return error
	if ( name == 0 ) {

		return ERROR_BAD_VALUE;

	}

	// if the root directory is invalid, return error
	if ( rootDir == 0 ) {

		return ERROR_INIT;

	}

	// if the file already exists, return error
	if ( cgc_statusFile(name, 0) == 0 ) {

		return ERROR_FILE_EXISTS;

	}


	// find the first empty directory entry
	for ( i = 0; i < rootDir->maxEntries; ++i ) {

		if ( rootDir->entry[i].name[0] == 0) {

			cgc_strncpy(rootDir->entry[i].name, name, MAX_FILENAME_LEN);
			rootDir->entry[i].fileSize = length;
			rootDir->entry[i].fileType = 0x3 + accessType;
			rootDir->entry[i].securityID = securityID;
			rootDir->entry[i].othersPermissions = 0;

			// now allocate a block for its first catalog block

			if (cgc_findFreeBlock(&catalogBlock) == 0 ) {

				cgc_eraseBlock(catalogBlock);

				cgc_setBlockInUse(catalogBlock);

				rootDir->entry[i].firstCatalogBlock = catalogBlock;

			}
			else {

				return ERROR_NO_BLOCKS;
			
			}

			rootDir->numEntries++;

			cgc_readBlock(catalogBlock, (void **)&memoryFileInfo);

			memoryFileInfo->address = address;
			memoryFileInfo->size = length;
			memoryFileInfo->accessType = accessType;

			cgc_writeBlock(memoryFileInfo, catalogBlock);

			return NO_ERROR;

		} // if strcmp

	}  // for

	return ERROR_MAX_EXCEEDED;

}


