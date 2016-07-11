/*

Author: James Connor (jymbo@cromulence.co)

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

#ifndef service_h
#define service_h
#define GROUP 		0x47
#define USER 		0x55
#define DIRECTORY 	0x44
#define LINK 		0x4c
#define FILE 		0x46
#define READ 		0x01
#define WRITE 		0x02
#define EXECUTE 	0x04
#define MAXPATH		4000
#define MAXCOMMAND 	256
#define MAXUPLOAD 	1000000 //1M

//dllist of users
typedef struct User_s {
	struct User_s *prev;
	struct User_s *next;
	char *name;
} sUser, *pUser;

//dllist of users in a group
typedef struct GroupUserList_s {
	struct GroupUserList_s *prev;
	struct GroupUserList_s *next;
	pUser user;
} sGroupUserList, *pGroupUserList;

//dllist of groups
typedef struct Group_s {
	unsigned int userCount;
	struct Group_s *prev;
	struct Group_s *next;
	pGroupUserList userList; 
	char *name;
} sGroup, *pGroup; 

//dllist of file chunks
typedef struct FileChunk_s {
	char *chunk;
	unsigned int chunkSize;
	struct FileChunk_s *prev;
	struct FileChunk_s *next;
} sFileChunk, *pFileChunk;

//list Head and count for file chunks
typedef struct File_s {
	unsigned int chunkCount;
	pFileChunk head;
	pFileChunk tail;
} sFile, *pFile;

//dllist of pointers to allowed users and perms
typedef struct Perms_s {
	struct Perms_s *prev;
	struct Perms_s *next;
	pUser user;
	pGroup group;
} sPerms, *pPerms;

//ddlist of files, links, and directories (another dllist)
typedef struct Node_s {
	//interesting bug would allow changing type without changing pointer
	struct Node_s *next;
	struct Node_s *prev;
	//type is directory, link (pointer to existing node), or file
	//if type is directory, element is node
	char type;
	unsigned int linkCount;
	unsigned int date;
	pPerms perms;
	char *name;
	pFile file;
	//parent is pointer to ../
	struct Node_s *parent;
	struct Node_s *directoryHeadNode;
	struct Node_s *directoryTailNode;
} sNode, *pNode;

//directory is a linked list of nodes, nodes are pointers to files or directories
//interesting bug would result from mv a directory to itself or its subdirs

//program data / all peristent context

typedef struct DataStruct_s {
	pNode root;
	pNode workingDir;
	pUser currentUser;
	pGroup currentGroup;
	pUser user;
	pGroup group;
	unsigned int date;
} sDataStruct, *pDataStruct;

void die(char *);
void *mallocOrDie(int, char *);
pDataStruct init_data();
pPerms find_perm_by_name(char *name, pNode node, pDataStruct workingData);
pPerms add_perm(pUser, pGroup, pNode);
pPerms delete_perms(pNode, pPerms);
void validate_current_perms(pNode node, pDataStruct workingData);
pNode _add_node( char, unsigned int, char *, pNode, pUser );
int get_file_size(pFile file);
void delete_file_bytes(pFile file, unsigned int newSize);
pFileChunk add_file_chunk( char *, pFile, unsigned int );
pNode add_file( pNode, unsigned int, unsigned int, char *, char *, pUser );
pFileChunk delete_chunk(pFile file, pFileChunk chunk);
void delete_file(pFile file);
pNode delete_node(pNode node, pDataStruct workingData);
pNode add_directory( unsigned int, char *, pNode, pUser );
pUser _move_user(pUser before, pUser moved, pDataStruct workingData);
pUser move_user(pUser, pUser, pDataStruct );
pUser _add_user( char *, pUser );
pUser add_user( char *, pDataStruct);
pGroupUserList is_user_in_group( pUser user, pGroup group );
int is_user_valid(pUser user, pDataStruct workingData);
int is_group_valid(pGroup group, pDataStruct workingData);
pGroupUserList remove_user_from_group(pUser user, pGroup group);
pUser remove_user(pUser, pDataStruct );
pGroup remove_group(pGroup group, pDataStruct workingData);
pUser find_user_by_name( char *, pDataStruct );
pUser find_user_by_number( int , pDataStruct );
pGroup _add_group( char *, pGroup );
pGroup add_group( char *, pDataStruct);
pGroupUserList add_user_to_group( pUser, pGroup );
pGroup find_group_by_number( int number, pDataStruct workingData);
pGroup find_group_by_name( char *, pDataStruct );
char *recursive_path(pNode, pNode);
pNode find_node_by_name(char *name, pNode directory);
pNode find_directory_by_name(char *name, pNode directory);
pFile find_file_by_name(char *name, pNode directory);
pNode find_file_node_by_name(char *name, pNode directory);
void str_of_path(char *, pDataStruct, pNode);
void destroy_data( pDataStruct );



#endif