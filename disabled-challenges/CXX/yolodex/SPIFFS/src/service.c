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

#include "libcgc.h"
#include "cgc_stdarg.h"
#include "cgc_stdlib.h"
#include "cgc_stdint.h"
#include "cgc_mymath.h"
#include "cgc_malloc.h"
#include "cgc_service.h"
#include "cgc_ui.h"


void cgc_die(char *message){
	cgc_printf("\n******************\n@s\n*****************\n",message);
	cgc__terminate( 1 );
}

void *cgc_mallocOrDie( int size, char *message ){
	void *retval = cgc_malloc( size );
	if ( retval == NULL ){cgc_die( message );}
	cgc_bzero(retval, size);
	return retval;
}

pDataStruct cgc_init_data(){
	pDataStruct workingData = NULL;
	workingData = cgc_mallocOrDie( sizeof( sDataStruct ), "Failed to malloc workingData" );
	workingData->root = cgc_mallocOrDie( sizeof( sNode ), "Failed to malloc root node" );
	workingData->root->parent = NULL;
	workingData->root->prev = NULL;
	workingData->root->date = 0;
	workingData->date = 0;
	workingData->root->type = DIRECTORY;
	workingData->workingDir = workingData->root;
	workingData->user = cgc__add_user( "root", NULL );
	workingData->group = cgc__add_group("root", NULL);
	workingData->currentUser = workingData->user;
	workingData->currentGroup = workingData->group;
	cgc_add_user_to_group(workingData->user, workingData->group);
	workingData->root->perms = cgc_add_perm( workingData->user, NULL, workingData->root );
	cgc_add_perm( NULL, workingData->group, workingData->root );
	workingData->root->file = NULL;
	workingData->root->parent = NULL;
	workingData->root->directoryHeadNode = NULL;
	char *name = cgc_mallocOrDie( 5, "Failed to malloc root name" );
	workingData->root->name = name;	
	cgc_strcpy(name, "");
	return workingData;
}

pPerms cgc_find_perm_by_name(char *name, pNode node, pDataStruct workingData){
	//if user and group have same name, user is returned
	cgc_validate_current_perms(node, workingData);
	pPerms tempPerm = node->perms;
	while( tempPerm != NULL ){
		if ( tempPerm->user != NULL ){
			if ( cgc_strcmp(tempPerm->user->name,name) == 0 ){
				return tempPerm;
			}
		} 
		if ( tempPerm->group != NULL ){
			if ( cgc_strcmp(tempPerm->group->name,name) == 0 ){
				return tempPerm;
			}
		}
		tempPerm = tempPerm->next;
	}
	return NULL;
}

pPerms cgc_add_perm(pUser user, pGroup group, pNode node){
	if (  (  ( user == NULL ) && (  group == NULL ) ) || (  ( user != NULL ) && (  group != NULL ) )  ) {cgc_die("Bad call to _add_perm");}
	pPerms newPerms = cgc_mallocOrDie( sizeof( sPerms ), "Failed to malloc pPerms" );
	if ( user != NULL ){
		newPerms->user = user;
	} 
	if ( group != NULL ){
		newPerms->group = group;
	}
	if ( node->perms == NULL ){
		node->perms = newPerms;
	} else {
		pPerms lastPerm = node->perms;
		pPerms tempPerm = lastPerm;
		while ( tempPerm != NULL ){
			if (  ( lastPerm->user  != NULL ) && ( lastPerm->user == user  )  ){//test if perm already exists
				return NULL;
			} 
			if (  ( lastPerm->group != NULL ) && ( lastPerm->group == group ) ){//test if perm already exists
				return NULL;
			}
			lastPerm = tempPerm;
			tempPerm = lastPerm->next;
		}
		lastPerm->next = newPerms;
		newPerms->prev = lastPerm;
		newPerms->next = NULL;
	}
	return newPerms;
}

pPerms cgc_delete_perms(pNode node,pPerms temp){//returns next perm or null if no next
	if (temp == NULL){
		return NULL;
	}
	pPerms retval = temp->next;
	if (temp->prev != NULL){
		temp->prev->next = temp->next;
	} 
#ifdef PATCHED
	if (temp->prev == NULL) {//first perm in list
		node->perms = temp->next;
	}	
#endif
	if (temp->next != NULL){
		temp->next->prev = temp->prev;
#ifndef PATCHED
		if (temp->prev ==NULL){
			node->perms = temp->next;
		}
#endif
	}	
	cgc_free(temp);
	return retval;

}
void cgc_validate_current_perms(pNode node, pDataStruct workingData){
	pPerms temp = node->perms;
	pPerms tempNxt = NULL;

	if (temp == NULL){
		return;
	}
	if (  (temp->user == NULL) && (temp->group == NULL)  ){
		cgc_printf("Bad perm @s\n",node->name);
		return;
	}
	while(temp != NULL){
		if (temp->user != NULL){
			if ( !cgc_is_user_valid(temp->user, workingData) ){
				tempNxt = cgc_delete_perms(node, temp);
			} else {
				tempNxt = temp->next;
			}
		}
		if (temp->group != NULL){
			if ( !cgc_is_group_valid(temp->group, workingData) ){
				tempNxt = cgc_delete_perms(node, temp);
			} else {
				tempNxt = temp->next;
			}
		}
		temp = tempNxt;
	}
	return;
}

pNode cgc__add_node( char type, unsigned int date, char *name, pNode parent, pUser user ){
	//adding a node to either an exising node list or a new nodelist.
	//if parent.directoryHeadNode is NULL this is a new nodelist
	//_addNode does not add pFile or directoryHeadNode
	//DOES NOT add file, directoryHeadNode.. that is handled by add_file and add_directory
	pNode newNode = cgc_mallocOrDie( sizeof( sNode ), "Failed to mallod node");
	newNode->parent = parent;
	newNode->next = NULL;
	newNode->directoryTailNode = NULL;
	newNode->directoryHeadNode = NULL;
	newNode->type = type;
	newNode->date = date;
	newNode->perms = cgc_add_perm(user, NULL, newNode);
	char *newName = cgc_mallocOrDie( cgc_strlen(name) + 1, "Failed to malloc name");
	cgc_strcpy( newName, name );
	newNode->name = newName;
	newNode->file = NULL;
	newNode->parent = parent;
	//first entry in directory
	if ( parent->directoryHeadNode == NULL ){
		parent->directoryHeadNode = newNode;
		parent->directoryTailNode = newNode;
		newNode->prev = NULL;
	} else {
		parent->directoryTailNode->next = newNode;
		newNode->prev = parent->directoryTailNode;
		parent->directoryTailNode = newNode;
	}
	return newNode;
}

int cgc_get_file_size(pFile file){
	pFileChunk temp = file->head;
	unsigned int size = 0;
	while ( temp != NULL ){
		size += temp->chunkSize;
		temp = temp->next;
	}
	return size;
}

void cgc_delete_file_bytes(pFile file, unsigned int newSize){
	pFileChunk temp = file->head;
	pFileChunk last = file->head;
	unsigned int remainderbytes = 0;
	unsigned int size = 0;
	int flag = 0;
	while ( temp != NULL ){
		size += temp->chunkSize;
		//all the remaining chunks are to be deleted
		if (flag == 1){
			temp = cgc_delete_chunk(file, temp);
		}else{
			//is this the last good chunk?
			if (size >= newSize){
				last = temp;
				flag = 1;
				remainderbytes = size - newSize;//how many bytes to delete from this chunk
			} //if this chunk is a keeper and we need more
			temp = temp->next;			
		}
	}
	size = last->chunkSize - remainderbytes;
	char *newChunk = cgc_mallocOrDie( size , "Failed to malloc filechunk" );
	cgc_memcpy(newChunk,last->chunk,size);
	cgc_free(last->chunk);
	last->chunkSize = size;
	last->chunk = newChunk;
}

pFileChunk cgc_add_file_chunk(char *data, pFile file, unsigned int size ){
	//allocate a new fileChunk and insert into file chunk list
	//update file node with new head/tail/count as necessary
	pFileChunk newFileChunk =  cgc_mallocOrDie( sizeof( sFileChunk ), "Failed to malloc filechunk" );
	newFileChunk->chunk = cgc_mallocOrDie( size, "Failed to malloc chunk" );
	cgc_memcpy( newFileChunk->chunk, data, size );
	newFileChunk->chunkSize = size;
	if ( file->tail == NULL ){
		file->head = newFileChunk;
		file->tail = newFileChunk;
		newFileChunk->prev = NULL;
		file->chunkCount = 1;
	} else {
		file->chunkCount += 1;
		file->tail->next = newFileChunk;
		newFileChunk->prev = file->tail;
		file->tail = newFileChunk;
	}
	newFileChunk->next = NULL;
	return newFileChunk;
}

pNode cgc_add_file( pNode directory,unsigned int date, unsigned int size, char *name, char* data, pUser user ){
	//if size is 0, data is null, create new empty file
	pFile newFile = cgc_mallocOrDie( sizeof( sFile ), "Failed to malloc file" );
	if ( size > 0) {
		pFileChunk newFileChunk = cgc_add_file_chunk(data, newFile, size );
	}
	pNode newNode = cgc__add_node( FILE, date, name, directory, user);
	newNode->file = newFile;
	return newNode;
}

pFileChunk cgc_delete_chunk(pFile file, pFileChunk chunk){
	//return next or NULL;
	pFileChunk retval = chunk->next;
	if (chunk == NULL){
		cgc_puts("delete_chunk called with NULL");
		return NULL;
	}
	if (chunk->prev == NULL){//first chunk
		file->head = chunk->next;
		if (chunk->next == NULL){//if it is the only element
			file->tail = NULL;
			file->chunkCount = 0;
		} else {//first but not last
			chunk->next->prev = NULL;
			file->chunkCount -= 1;
		}
	} else {//not first chunk
		chunk->prev->next = chunk->next;
		if (chunk->next == NULL){//last no next
			file->tail = NULL;
		}else {//not last
			chunk->next->prev = chunk->prev;	
		}
		file->chunkCount -= 1;
	}

	cgc_free(chunk->chunk);
	cgc_free(chunk);
	return retval;
}

void cgc_delete_file(pFile file){
	pFileChunk tempChunk = file->head;
	while(tempChunk != NULL){
		tempChunk = cgc_delete_chunk(file, tempChunk);
	}
	cgc_free(file);
	return;
}

pNode cgc_delete_node(pNode node, pDataStruct workingData){
	pNode retval = node->next;
	//returns pointer to next node or NULL
	if ( node == workingData->root ){//can not delete 'root' directory
		cgc_puts("can not delete root directory");
	}
	if ( node->type == FILE ){
		pFile tempFile = node->file;
		cgc_delete_file( tempFile );
	}
	if ( node->type == DIRECTORY ){//delete all files and subdirs
		pNode tempNode = node->directoryHeadNode;
		while ( tempNode != NULL ){//daily dose of recursion
			tempNode = cgc_delete_node( tempNode, workingData );
		}
	}
	if (node->prev == NULL){//first
			node->parent->directoryHeadNode = node->next;
		if (node->next == NULL){//only
			node->parent->directoryHeadNode = NULL;
			node->parent->directoryTailNode = NULL;
		} else {//first but not only
			node->next->prev = NULL;			
		}		
	} else {//not first
		node->prev->next = node->next;
		if (node->next == NULL){//last
			node->parent->directoryTailNode = node->prev;
		} else {//not first or last
			node->next->prev = node->prev;
		}
	}
	pPerms perms = node->perms;
	while(perms != NULL){
		perms = cgc_delete_perms(node, perms);
	}
	cgc_free(node->name);
	cgc_free(node);
	return retval;
}

pNode cgc_add_directory( unsigned int date, char *name, pNode parent, pUser user ){
	//add a directory with current user as perm
	pNode newDirectory = cgc__add_node( DIRECTORY, date, name, parent, user );
	newDirectory->directoryHeadNode = NULL;
	newDirectory->directoryTailNode = NULL;
	return newDirectory;
}

pUser cgc__add_user( char *name, pUser userList ){
	//add user to userList, 
	//if userList is NULL, create single element list
	pUser newUser = cgc_mallocOrDie( sizeof( sUser ), "Failed to allocate user");
	char *newName = cgc_mallocOrDie( cgc_strlen( name ) + 1, "Failed to allocate username");
	//cgc_printf("_add_user cgc_strlen(name):@d",cgc_strlen( name ));
	cgc_strcpy ( newName, name );
	newUser->name = newName;
	if ( userList == NULL ){
		//not necessary, but looks nice
		newUser->prev = NULL;
		newUser->next = NULL;
		return newUser;
	} else {
		pUser lastUser = userList;
		pUser tempUser = userList->next;
		while ( tempUser != NULL ){
			lastUser = tempUser;
			tempUser = tempUser->next;
		}
		lastUser->next = newUser;
		newUser->prev = lastUser;
		//unnecessary but looks nice
		newUser->next = NULL;
	}
	return newUser;
}

pUser cgc_add_user( char *name, pDataStruct workingData ){
	return cgc__add_user( name, workingData->user );
}

pGroupUserList cgc_is_user_in_group( pUser user, pGroup group ){
	//returns pGroupUserList if found, or NULL if not found
	pGroupUserList temp = group->userList;
	while (temp != NULL ){
		if ( temp->user == user ){return temp;}
		temp = temp->next;
	}
	return NULL; 
}

int cgc_is_user_valid(pUser user, pDataStruct workingData){
	//returns 1 if user is valid (in users)
	pUser temp = workingData->user;
	while( temp != NULL ){
		if ( temp == user ){return 1;}
		temp = temp->next;
	}
	return 0;
}

int cgc_is_group_valid(pGroup group, pDataStruct workingData){
	pGroup temp = workingData->group;
	while( temp != NULL ){
		if ( temp == group ){return 1;}
		temp = temp->next;
	}
	return 0;
}

pGroupUserList cgc_remove_user_from_group(pUser user, pGroup group){
	//returns prev groupUserList or NULL
	pGroupUserList temp = cgc_is_user_in_group(user, group);
	pGroupUserList retval = NULL;
	if ( temp == NULL){return NULL;}
	if ( temp->prev == NULL){//first element
		if ( temp->next ==NULL){//only element
			group->userList = NULL;//head is NULL
			group->userCount = 0;
		} else {//first but not only
			group->userList = temp->next;
			temp->next->prev = NULL;
			group->userCount -= 1;
		}
	} else {//not first
		if ( temp->next == NULL ){//last
			temp->prev->next = NULL;
			group->userCount -= 1;
		} else {//not first or last
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			group->userCount -= 1;
		}
	}
	retval = temp->prev; //if first, next is null
	cgc_free(temp);
	return retval;
}


pUser cgc_remove_user(pUser user, pDataStruct workingData){
	//returns prev or null 
	pGroup groupList = workingData->group;
	pUser retval = NULL;
	pUser last = NULL;
	if (user == NULL){cgc_puts("Bad call:remove_user");return NULL;}//bad call to remove user
	if ( user->prev == NULL ){cgc_puts("Can not delete root");return NULL;}
	if (user == workingData->user){//never delete root
		return NULL;
	}
	while ( groupList != NULL ){//remove user from any groups
		cgc_remove_user_from_group(user,groupList);
		groupList = groupList->next;
	}
	user->prev->next = user->next;
	if ( user->next != NULL ){//not last
		user->next->prev = user->prev;
	}
	retval = user->prev;
	cgc_free (user->name);
	cgc_free (user);
	return retval;
}

pGroup cgc_remove_group(pGroup group, pDataStruct workingData){
	pGroup retval = NULL;
	pGroupUserList temp = NULL;
	pGroupUserList last = NULL;
	if ( group == NULL){
		cgc_puts("bad call to remove_group");
		return NULL;
	}
	if (group == workingData->group){
		cgc_puts("Unable to delete group root");
		return NULL;
	}
	temp = group->userList;
	last = temp;
	while ( temp != NULL ){//get last user
		last = temp;
		temp = temp->next;
	}
	while (last != NULL ){//delete all users
		last = cgc_remove_user_from_group(last->user, group);
	}
	if (group->prev != NULL){
		group->prev->next = group->next;
	}
	if ( group->next != NULL){//not last
		group->next->prev = group->prev;
	}
	retval = group->prev;
	cgc_free(group->name);
	cgc_free(group);
	return retval;
}

pUser cgc_find_user_by_name( char *name, pDataStruct workingData){
	//returns NULL or first user with name
	pUser retval = NULL;
	pUser last = workingData->user;
	while ( last != NULL ){
		if ( cgc_strcmp(name, last->name ) == 0 ){
			return last;
		} else{
			last = last->next;
		}
	}
	return retval;
}

pUser cgc_find_user_by_number( int number, pDataStruct workingData){
	pUser retval = NULL;
	pUser last = workingData->user;
	int count = 0;
	while ( last != NULL ){
		if ( count == number ){
			return last;
		} else {
			count += 1;
			last = last->next;
		}
	}
	return retval;
}

pGroup cgc__add_group( char *name, pGroup group ){
	//add empty group of users, no users are added, empty group is returned
	//group is dllist of groups to add group to, if null, create and return
	pGroup newGroup = cgc_mallocOrDie( sizeof( sGroup ), "Failed to allocate group");
	char *newName = cgc_mallocOrDie( cgc_strlen( name ) + 1, "Failed to allocate groupName");
	cgc_strcpy( newName, name );
	newGroup->name = newName;
	newGroup->userCount = 0;
	newGroup->userList = NULL;
	newGroup->next = NULL;
	if (group == NULL){
		//used in init state
		group = newGroup;
		return newGroup;
	}
	//walk to the end of grouplist
	pGroup last = group;
	pGroup temp = last;
	while( temp != NULL ){
		last = temp;
		temp = last->next;
	}
	newGroup->prev = last;
	last->next = newGroup;
	return newGroup;
}

pGroup cgc_add_group( char *name, pDataStruct workingData ){
	return cgc__add_group ( name, workingData->group );
}

pGroupUserList cgc_add_user_to_group( pUser user, pGroup group ){
	pGroupUserList newGroupUserListNode = cgc_mallocOrDie( sizeof( sGroupUserList ), "Failed to allocate newUser");
	newGroupUserListNode->user = user;
	newGroupUserListNode->next = NULL;
	//if group has no users
	if ( group->userList == NULL ){
		group->userList = newGroupUserListNode;
		newGroupUserListNode->prev = NULL;
		group->userCount = 1;
	} else {
		pGroupUserList last = group->userList;
		pGroupUserList temp = last;
		while( temp != NULL){
			last = temp;
			temp = temp->next;
		}
		last->next = newGroupUserListNode;
		newGroupUserListNode->prev = last;
		group->userCount += 1;
	}
	return newGroupUserListNode;
}


pGroup cgc_find_group_by_number( int number, pDataStruct workingData){
	pGroup retval = NULL;
	pGroup last = workingData->group;
	int count = 0;
	while ( last != NULL ){
		if ( count == number ){
			retval = last;
			last = NULL;
		} else {
			count += 1;
			last = last->next;
		}
	}
	return retval;
}

pGroup cgc_find_group_by_name( char *name, pDataStruct workingData){
	//returns NULL or first user with name
	pGroup retval = NULL;
	if ( workingData->group != NULL ){
		pGroup last = workingData->group;
		while ( last != NULL ){
			if ( cgc_strcmp(name, last->name) == 0 ){
				return last;
			}
			last = last->next;
		}
	}
	return retval;
}

char *cgc_recursive_path(pNode start, pNode end){
	if (end == start){
		char *path = cgc_mallocOrDie(cgc_strlen(end->name) + 2, "Failed to allocate endName");
		cgc_strcpy(path, end->name);
		return path; 
	}
	if ( end->parent == NULL ){
		return NULL;
	}

	char *path = cgc_recursive_path(start, end->parent);
	if (path == NULL){
		return NULL;
	}
	char *retpath = cgc_mallocOrDie(  ( cgc_strlen(path) + cgc_strlen(end->name) + 2 ), "Failed to allocate retpath"); 	
	cgc_strcpy(retpath, path);
	cgc_strcat(retpath, "/");
	cgc_strcat(retpath, end->name);
	cgc_free(path);
	return retpath;
}

void cgc_str_of_path(char *path, pDataStruct workingData, pNode end){
	char *newPath = cgc_recursive_path(workingData->root, end);
#ifdef PATCHED
	unsigned int size = cgc_strlen(newPath);
	if (size >= MAXPATH){
		size = MAXPATH-1;
		cgc_puts("Path exceeds max path size and has been truncated");
	}
	strncpy(path, newPath, size );
#endif
#ifndef PATCHED
	cgc_strcpy(path, newPath );	
#endif
	cgc_free ( newPath );
	return;
}

pNode cgc_find_node_by_name(char *name, pNode directoryNode){
	pNode temp = directoryNode;
	while( temp != NULL ){
		if (cgc_strcmp(name,temp->name) == 0){
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

pNode cgc_find_directory_by_name(char *name, pNode directory){
	pNode temp = cgc_find_node_by_name(name, directory->directoryHeadNode);
	while( temp != NULL){
		if ( temp->type == DIRECTORY ) {
			return temp;
		}
		temp = cgc_find_node_by_name(name, temp->next);
	}
	return NULL;
}

pFile cgc_find_file_by_name(char *name, pNode directory){
	pNode temp = cgc_find_node_by_name(name,directory->directoryHeadNode);
	while(temp!= NULL){
		if ( temp->type == FILE ) {
			return temp->file;
		}
		temp = cgc_find_node_by_name(name,temp->next);
	}
	return NULL;
}

pNode cgc_find_file_node_by_name(char *name, pNode directory){
	pNode temp = cgc_find_node_by_name(name,directory->directoryHeadNode);
	while(temp != NULL){
		if ( temp->type == FILE ) {
			return temp;
		}
		temp = cgc_find_node_by_name(name,temp->next);
	}
	return NULL;	
}


int main(int cgc_argc, char *cgc_argv[]){
	pDataStruct workingData = cgc_init_data();
	cgc_start_UI(workingData);
	return 0;
}