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
#define DELIM 0x0A 	//\n

int cgc_strict_atoi(char *a){
	for(int i = 0;i<cgc_strlen(a);i++){
		if ( ( a[i] > 0x39 ) || ( a[i] < 0x30 ) ){
			return 0x0;
		}
	}
	return cgc_atoi(a);
}

unsigned int cgc_get_int(char *prompt){
	//get number from user as unsigned int
	char numBuf[10];
	cgc_printf("@s :",prompt);
	int result = cgc_receive_until(numBuf, DELIM, 9);
	numBuf[result] = 0;
	//bad way to clear signs, but unique(hopefully)
	for (int i = 0; i<result; i++ ){
		if (  ( numBuf[i] > 0x39 ) || ( numBuf[i] < 0x30 )  ){
			numBuf[i] = 0x30;
		}
	}
	result = cgc_atoi(numBuf);
	return result;	
}


unsigned int cgc_get_string(char *strBuf, unsigned int size, char *prompt){
	cgc_printf("@s >",prompt);
	int result = cgc_receive_until(strBuf, DELIM, size);
	strBuf[result] = 0;
	return result;
}


void cgc_print_prompt(pDataStruct workingData){
	char temp[MAXPATH];
	cgc_bzero(temp,MAXPATH);
	cgc_str_of_path( temp, workingData, workingData->workingDir);
	cgc_printf("@s@@SPIFF:@s/",workingData->currentUser->name, temp );
	return;
}

void cgc_print_help(char **commandList, int size){
	cgc_printf("< ");
	for (int i = 0;i < size-1; i++){
		cgc_printf("@s, ",commandList[i]);
	}
	cgc_printf("@s >\n",commandList[size-1]);
}

int cgc_parse_arg(char arg[16][MAXCOMMAND], char *command){
		int argnum = 0;
		int lpos = 0;
		int lspace = 1; //last position was space
		int i;
		int cmdSize = cgc_strlen(command);
		//tokenize command 
		for (i = 0;i < cmdSize;i++){
			if (command[i] == 32){
				if ( lspace == 0 ) {//was in a word
					cgc_bzero(arg[argnum],sizeof(arg[argnum]));
					cgc_strncpy(arg[argnum],&command[lpos], (i-lpos));
					if (argnum == 15){break;}
					argnum += 1;
				} 
				lspace = 1;
				lpos = i;	
			} else {//not a space
				//if it was a space before, move lpos
				if (lspace == 1){
					lpos = i;
				}
				lspace = 0;				
			}
		}
		if (lpos < i ){
			cgc_bzero(arg[argnum],sizeof(arg[argnum]));
			cgc_strncpy(arg[argnum],&command[lpos],(i-lpos));
			argnum += 1;
		} 

	return argnum;
}

void cgc_print_perms(pNode node, pDataStruct workingData){
	pPerms tempPerms = node->perms;
	cgc_validate_current_perms(node, workingData);
	while(tempPerms != NULL){
		if (tempPerms->user != NULL){
			cgc_printf(" @s",tempPerms->user->name);
		}
		if (tempPerms->group != NULL){
			cgc_printf(" @s",tempPerms->group->name);
		}
		tempPerms = tempPerms->next;
	}
}

void cgc_print_user_list(pDataStruct workingData){
	pUser last = workingData->user;
	int count = 0;
	cgc_printf("UID    NAME\n__________\n");//10 underscores
	while ( last != NULL ){
		cgc_printf("@d @s\n",count,last->name);
		count += 1;
		last = last->next;
	}
	return;	
}

void cgc_print_group_list( pDataStruct workingData ){
	pGroup last = workingData->group;
	int count = 0;
	cgc_printf("GUID     NAME\n____________________\n");//20 underscores
	while ( last != NULL ){
		cgc_printf("@d @s\n",count,last->name);
		count += 1;
		last = last->next;
	}
	return;
}

void cgc_print_users_in_group( pGroup group ){
	pGroupUserList temp = group->userList;
	int count = 0;
	cgc_printf("Count Name\n____________________\n");
	while ( temp != NULL ){
		cgc_printf("@d @s\n",count, temp->user->name);
		count += 1;
		temp = temp->next;
	}
	return;
}

pGroup cgc_find_group(char *nameNum, pDataStruct workingData){
	pGroup tempGroup = NULL;
	int tempNum = cgc_strict_atoi(nameNum);
	if ( ( cgc_strcmp(nameNum,"root") == 0 ) || ( cgc_strcmp(nameNum,"0") == 0 )){
		return workingData->group;
	}
	if ( tempNum != 0 ){
		tempGroup = cgc_find_group_by_number( tempNum, workingData );
		if ( tempGroup != NULL ){
			return tempGroup;
		}
	}

	tempGroup = cgc_find_group_by_name( nameNum, workingData);
	return tempGroup;
}

pUser cgc_find_user(char *nameNum, pDataStruct workingData){
	pUser tempUser = NULL;
	int tempNum = cgc_strict_atoi(nameNum);
	if (    (  ( cgc_strcmp(nameNum,"root") ) && ( cgc_strcmp(nameNum,"0") )  ) == 0    ){
		return workingData->user;
	}
	if ( tempNum != 0 ){
		tempUser = cgc_find_user_by_number( tempNum, workingData );
		if ( tempUser != NULL ){
			return tempUser;
		}
	}

	tempUser = cgc_find_user_by_name( nameNum, workingData);
	return tempUser;
}	

void cgc_print_working_dir(pDataStruct workingData){
	pNode temp = workingData->workingDir->directoryHeadNode;
	cgc_printf("Type  Size     Date     Name       Perms\n_______________________________________\n");//40_
	while ( temp != NULL ){
		if(temp->type == FILE){
			cgc_printf("FILE @d  @x   @s  ",cgc_get_file_size(temp->file), temp->date, temp->name);
			cgc_print_perms(temp,workingData);
			cgc_printf("\n");
		}
		if(temp->type == DIRECTORY){
			cgc_printf("DIR  @d  @x   @s ",sizeof(sNode), temp->date, temp->name);
			cgc_print_perms(temp,workingData);
			cgc_printf("\n");
		}

		temp = temp->next;

	}
}

void cgc_main_loop(pDataStruct workingData){
	char *commandList[] = {"set", "get", "add", "delete","exit","help","ls","cat","cd"};
	char *setList[] = {"date", "user", "group","help"};
	char *getList[] = {"date", "user", "group", "workingDir","help", "userlist", "grouplist", "usersingroup"};
	char *addList[] = {"user", "group", "file", "directory", "usertogroup","perm", "appendfile","help"};
	char *deleteList[] = {"user", "group", "file", "directory", "usertogroup","perm", "filebytes","help"};
	char arg[16][MAXCOMMAND];
	char command[MAXCOMMAND];
	int argnum, i, j, tempNum, cmd, size;
	char *c;
	char temp[MAXPATH];
	char *tempBuf;
	unsigned char *rcvBuf;
	pNode tempNode = NULL;
	pUser tempUser = NULL;
	pGroup tempGroup = NULL;
	pFile tempFile = NULL;
	pPerms tempPerms = NULL;
	pFileChunk tempFileChunk = NULL;
	pGroupUserList tempGroupUserList = NULL;

	while(1){
		argnum = i = j = tempNum = cmd = 0;
		c = 0;
		cgc_bzero(temp, sizeof(temp));
		tempBuf = NULL;
		tempNode = NULL;
		tempUser = NULL;
		tempGroup = NULL;
		tempFile = NULL;
		tempPerms = NULL;
		tempFileChunk = NULL;
		tempGroupUserList = NULL;		
		cgc_bzero(command, sizeof(command));
		cgc_print_prompt(workingData);
		cgc_get_string(command, MAXCOMMAND-1, "");
		for (j = 0;j<16;j++){
			cgc_bzero(arg[j],MAXCOMMAND);
		}
		argnum = cgc_parse_arg(arg, command);
		tempNum = 0;
		cmd = 100;

		for (i=0;i<sizeof(commandList)/4;i++){
			if (cgc_strcmp(commandList[i],arg[0]) == 0 ){
				cmd = i;
			}
		}
		switch(cmd)
		{
			case 0x0 : //set
				cmd = 100;
				for (i=0;i<sizeof(setList)/4;i++){
					if (cgc_strcmp(setList[i],arg[1]) == 0){
						cmd = i;
					}
				}
				switch(cmd)
				{

					case 0 : //set date
						workingData->date = cgc_get_time();
						break;//end set date

					case 1 : //set user

						if ( cgc_strcmp(arg[2],"") == 0){
							cgc_puts("missing user name or number");
							break;
						}
						tempUser = cgc_find_user(arg[2],workingData);
						if ( tempUser != NULL ){
							workingData->currentUser = tempUser;
						} else { 
							cgc_printf("unknown user: @s\n",arg[2]);
						}
						break;//end set user

					case 2 : //set group

						if ( cgc_strcmp(arg[2], "") == 0){
							cgc_puts("missing group name or number");
							break;
						}
						tempGroup = cgc_find_group(arg[2], workingData);
						if ( tempGroup != NULL){
							workingData->currentGroup = tempGroup;
						} else {
							cgc_printf("unknown group: @s\n",arg[2]);
						}
						break;

					case 3 : //set help
						cgc_print_help(setList,(sizeof(setList)/4));
						break;//end set help

					default :
						cgc_printf("Invalid command: @s\n",arg[1]);

				}

				break;//end set 

			case 1 ://get
				cmd = 100;
				for (i=0;i<sizeof(getList)/4;i++){
					if (cgc_strcmp(getList[i],arg[1]) == 0){
						cmd = i;
					}
				}
				switch(cmd)
				{

					case 0 : //get date
						cgc_strofdate( workingData->date);
						break;//end get date

					case 1 : //get user
						cgc_printf("@s\n",workingData->currentUser->name);
						break;//end get user

					case 2 : //get group
						cgc_printf("@s\n",workingData->currentGroup->name);
						break;//end get group

					case 3 : //get workingDir
						cgc_bzero(temp,MAXPATH);
						cgc_str_of_path( temp, workingData, workingData->workingDir);
						cgc_printf("@s/\n",temp);
						break;//end get workingDir

					case 4 : //get help
						cgc_print_help(getList,(sizeof(getList)/4));
						break;//end get help

					case 5 : //get userlist
						cgc_print_user_list(workingData);

						break;//end get userlist

					case 6 : //get grouplist
						cgc_print_group_list(workingData);
						break;//end get grouplist

					case 7 : //get usersingroup
						if ( cgc_strcmp(arg[2], "") == 0){
							cgc_puts("missing group name or number");
							break;
						}
						tempGroup = cgc_find_group(arg[2], workingData);
						if ( tempGroup != NULL ){
							cgc_print_users_in_group(tempGroup);
							break;
						}
						cgc_printf("unknown group: @s\n",arg[2]);
						break;//end get useringroup						

					default :
						cgc_printf("Invalid command: @s\n",arg[1]);
				}

				break;//end get

			case 2 ://add
				cmd = 100;
				for (i=0;i<sizeof(addList)/4;i++){
					if ( cgc_strcmp(addList[i],arg[1]) == 0 ){
						cmd = i;
					}
				}
				switch(cmd)
				{
					case 0 : //add user

						if ( cgc_strcmp(arg[2],"") == 0 ){
							cgc_bzero(temp,MAXPATH);
							cgc_get_string(temp, 128, "UserName");
							cgc_strcpy(arg[2],temp);
						}
						tempUser = cgc_find_user( arg[2], workingData);
						if ( tempUser == NULL ){
							cgc_add_user( arg[2], workingData );
						} else {
							cgc_puts("Username already in use");
						}
						break;//end add user

					case 1 : //add group
						if ( cgc_strcmp(arg[2],"") == 0 ){
							cgc_bzero(temp,MAXPATH);
							cgc_get_string(temp, 128, "GroupName");
							cgc_strcpy(arg[2], temp);
						}
						tempGroup = cgc_find_group( arg[2], workingData);
						if ( tempGroup == NULL ){
							cgc_add_group( arg[2], workingData );
						} else {
							cgc_puts("Groupname already in use");
						}
						break;//end add group

					case 2 : //add file
						//add file name size
						tempNum = cgc_atoi(arg[3]);
						if (cgc_strcmp(arg[2],"") == 0){
							cgc_puts("Filename required");
							break;
						}
						if ( tempNum > MAXUPLOAD ){
							cgc_puts("Too big");
							break;
						}
						if ( cgc_find_node_by_name(arg[2],workingData->workingDir->directoryHeadNode) != NULL ){
							cgc_puts("There is another file or directory with that name");
							break;
						}
						if ( tempNum > 0){
							rcvBuf = cgc_mallocOrDie(tempNum,"Failed to allocate tempBuf");
							cgc_puts("-----Begin File-----");//five - 
							if ( tempNum != cgc_receive_bytes(rcvBuf,tempNum) ){
								cgc_die("Failed to reveive file");
								break;
							}
						} else {rcvBuf = NULL;}
						tempNode = cgc_add_file( workingData->workingDir, workingData->date, tempNum, arg[2], (char *)rcvBuf, workingData->currentUser );
						break;//end add file

					case 3 : //add directory

						if (cgc_strcmp(arg[2],"") == 0){
							cgc_puts("Directory name required");
							break;
						}
						if ( cgc_find_node_by_name(arg[2],workingData->workingDir->directoryHeadNode) != NULL ){
							cgc_puts("There is another file or directory with that name");
							break;
						}
						tempNode = cgc_add_directory( workingData->date, arg[2], workingData->workingDir, workingData->currentUser );
						break;//end add directory

					case 4 : //add useringroup
						if (cgc_strcmp(arg[2],"") == 0){
							cgc_puts("username or number required");
							break;
						}
						tempUser = cgc_find_user( arg[2], workingData);
						if ( tempUser != NULL ){//user exists
							tempGroupUserList = cgc_is_user_in_group( tempUser, workingData->currentGroup );
							if ( tempGroupUserList == NULL ){//user is not already in group	
								cgc_add_user_to_group( tempUser, workingData->currentGroup );
							} else {cgc_printf("@s is already in @s\n",arg[2], workingData->currentGroup->name);}
						} else {
							cgc_puts("User does not exist, add user first");
						}

						break;//end add useringroup
						
					case 5 : //add perm
						if (  ( cgc_strcmp(arg[2],"") == 0 )||( cgc_strcmp(arg[2]," ") == 0 )  ){//arg[2] name of file or dir
							cgc_puts("name of file or directory required");
							break;
						}
						if (!(  (cgc_strcmp(arg[3],"user") == 0) ^ (cgc_strcmp(arg[3],"group") == 0) )) {//arg[3] user, group
							cgc_puts("'user' or 'group'");
							break;
						}
						if (cgc_strcmp(arg[4],"") == 0){
							cgc_puts("user name, group name, or number required");//arg[4] name or number of user or group
							break;
						}
						tempNode = cgc_find_node_by_name(arg[2],workingData->workingDir->directoryHeadNode );//validate file or dir
						if (tempNode == NULL){
							cgc_puts("Invalid file or directory");
							break;
						}
						if (tempNode->type == LINK){
							tempNode = tempNode->directoryHeadNode;
							break;
						}
						if (cgc_strcmp(arg[3],"user") == 0){
							tempUser = cgc_find_user(arg[4],workingData);
							tempGroup = NULL;
							if (tempUser == NULL){
								cgc_printf("user @s not found\n",arg[4]);
								break;
							}
						} else {
							tempGroup = cgc_find_group(arg[4],workingData);
							tempUser = NULL;
							if (tempGroup == NULL){
								cgc_printf("group @s not found\n",arg[4]);
								break;
							}
						}

						cgc_validate_current_perms(tempNode, workingData);
						tempPerms = cgc_add_perm(tempUser, tempGroup, tempNode ); 
						break;//end add perm

					case 6 : //add appendfile
						tempNum = cgc_atoi(arg[3]);
						if (cgc_strcmp(arg[2],"") == 0){
							cgc_puts("Filename required");
							break;
						}
						if ( tempNum > MAXUPLOAD ){
							cgc_puts("Too big");
							break;
						}
						tempFile = cgc_find_file_by_name(arg[2],workingData->workingDir);
						if (  tempFile == NULL ){
							cgc_puts("No file in working directory by that name");
							break;
						}
						if ( tempNum > 0){
							tempBuf = cgc_mallocOrDie(tempNum,"Failed to allocate tempBuf");
							cgc_puts("-----Begin File-----");//five - 
							if ( tempNum != cgc_receive_bytes((unsigned char *)tempBuf,tempNum) ){
								cgc_die("Failed to reveive file");
								break;
							}
						} else {
							tempBuf = NULL;
							cgc_puts("Can not add 0 bytes to file");
							break;
						}
						tempFileChunk = cgc_add_file_chunk( tempBuf, tempFile, tempNum );
						break;//end add appendfile

					case 7 : //add help
						cgc_print_help(addList, (sizeof(addList)/4));	
						break;//end add help

					default :
						cgc_printf("Invalid command: @s\n",arg[1]);
				}

				break;//end add
			case 3 ://delete 	
				cmd = 100;
				for (i=0;i<sizeof(deleteList)/4;i++){
					if ( cgc_strcmp(deleteList[i],arg[1]) == 0 ){
						cmd = i;
					}
				}
				switch(cmd)
				{

					case 0 : //delete user
						cgc_bzero(temp,MAXPATH);
						if ( cgc_strcmp(arg[2],"") == 0 ){
							cgc_get_string(temp, 128, "User Name or number");
							cgc_strcpy(arg[2],temp);
						}
						tempUser = cgc_find_user( arg[2], workingData);
						if ( tempUser != NULL ){
							cgc_remove_user(tempUser , workingData );
						} else {
							cgc_puts("No such user found");
						}
						break;//end delete user

					case 1 : //delete group
						cgc_bzero(temp,MAXPATH);
						if ( cgc_strcmp(arg[2],"") == 0 ){
							cgc_get_string(temp, 128, "Group Name or number");
							cgc_strcpy(arg[2],temp);
						}
						tempGroup = cgc_find_group( arg[2], workingData);
						if ( tempGroup != NULL ){
							cgc_remove_group(tempGroup , workingData );
						} else {
							cgc_puts("no such group found");
						}
						break;//end delete group 

					case 2 : //delete file 
						if (cgc_strcmp(arg[2],"") == 0){
							cgc_puts("Filename required");
							break;
						}
						tempNode = cgc_find_file_node_by_name(arg[2],workingData->workingDir);
						if (tempNode == NULL){
							cgc_puts("No such file");
							break;
						}
						cgc_delete_node(tempNode, workingData);
						break;//end delete file 

					case 3 : //delete directory
						if (cgc_strcmp(arg[2],"") == 0){
							cgc_puts("Directory name required");
							break;
						}
						tempNode = cgc_find_directory_by_name(arg[2],workingData->workingDir);
						if (tempNode == NULL){
							cgc_puts("No such directory");
							break;
						}
						cgc_delete_node(tempNode, workingData);
						break;//end delete directory

					case 4 : //delete usertogroup
						if (cgc_strcmp(arg[2],"") == 0){
							cgc_puts("User name required");
							break;
						}
						if (cgc_strcmp(arg[3],"") == 0){
							cgc_puts("group name required");
							break;
						}
						tempUser = cgc_find_user(arg[2],workingData);
						if (tempUser == NULL){
							cgc_puts("No such user");
							break;
						}
						tempGroup = cgc_find_group(arg[3],workingData);
						if (tempGroup == NULL){
							cgc_puts("No such group");
							break;
						}
						tempGroupUserList = cgc_is_user_in_group(tempUser, tempGroup);
						if (tempGroupUserList == NULL){
							cgc_puts("User is not in group");
							break;
						}
						cgc_remove_user_from_group(tempUser, tempGroup);
						break;//end delete usertogroup

					case 5 : //delete perm
						if (cgc_strcmp(arg[3],"") == 0){
							cgc_puts("User or group name required");
							break;
						}
						if (cgc_strcmp(arg[2],"") == 0){
							cgc_puts("file name required");
							break;
						}
						tempNode = cgc_find_node_by_name(arg[2],workingData->workingDir->directoryHeadNode);
						if (tempNode == NULL){
							cgc_puts("No such file");
							break;
						}
						tempPerms = cgc_find_perm_by_name(arg[3],tempNode,workingData);
						if (tempPerms != NULL){
							cgc_delete_perms(tempNode, tempPerms);
						} else {
							cgc_puts("No such user permission on file");
						}
						break;//end delete perm

					case 6 : //delete filebytes [file] [numbytes]
						if (cgc_strcmp(arg[2],"") == 0){
							cgc_puts("Filename required");
							break;
						}
						size = cgc_strict_atoi(arg[3]);
						if (size == 0){
							cgc_puts("zero bytes deleted");
							break;
						}
						//validate file						
						tempNode = cgc_find_file_node_by_name(arg[2],workingData->workingDir);
						tempFile = tempNode->file;
						if (tempNode == NULL){
							cgc_puts("No such file");
							cgc_printf("@s\n",arg[2]);
							break;
						}
						tempNum = cgc_get_file_size(tempFile);
						if (size > tempNum){
							cgc_puts("Too many bytes");
						} 
						//tempNum is new file size
						tempNum = tempNum - size;
						cgc_delete_file_bytes(tempFile, tempNum);
						break;//end delete file 

					case 7 : //delete help
						cgc_print_help(deleteList, (sizeof(deleteList)/4));	
						break;//end delete help

					default:
						cgc_print_help(deleteList, (sizeof(deleteList)/4));	
						//break;//end delete help

				}
				break;//end delete
				

			case 4 ://cgc_exit
				cgc_puts("exiting");
				goto cgc_exit;
				break;

			case 5 ://help
				cgc_print_help(commandList, (sizeof(commandList)/4));
				break;
			case 6 ://ls
				cgc_print_working_dir(workingData);
				break;
			case 7 ://cat
				if (cgc_strcmp(arg[1],"") == 0){
					cgc_puts("Filename required");
					break;
				}
				tempFile = cgc_find_file_by_name(arg[1], workingData->workingDir);							
				if ( tempFile != NULL ){
					tempFileChunk = tempFile->head;
					cgc_puts("-----Begin File-----");//five - 
					while ( tempFileChunk != NULL ){
						if (tempFileChunk->chunkSize != cgc_write(tempFileChunk,tempFileChunk->chunkSize)){
							cgc_puts("file write failed");
						}
/*
						c = tempFileChunk->chunk;
						for ( i = 0; i < tempFileChunk->chunkSize; i++ ){//putc each byte of every chunk
							putc( *c);
							c++;
						}
*/						
						tempFileChunk = tempFileChunk->next;	
					}
					cgc_puts("-----END File-----");//five - 
				}
				break;
			case 8 ://cd
				if (cgc_strcmp(arg[1],"") == 0){
					cgc_puts("directory required");
					break;
				}
				if (cgc_strcmp(arg[1],"..") == 0){
					if (workingData->workingDir->parent != NULL){
						workingData->workingDir = workingData->workingDir->parent;
					}
					break;
				}
				tempNode = cgc_find_directory_by_name(arg[1],workingData->workingDir);
				if ( tempNode != NULL ){
					workingData->workingDir = tempNode;
					break;
				}
				cgc_puts("No such directory in working directory");
				break;//end cd

			default :
				cgc_printf("Invalid command @s\n",arg[0]);
				cgc_print_help(commandList, (sizeof(commandList)/4));
				
		}
	}
	cgc_exit:
	return;
}

void cgc_date_from_epoch(unsigned int epoch, int date[6]){
	//date is date[6]
	int year = 1970;
	int month = 1;
	int day = 1;
	int hour = 0;
	int minute = 0;
	int second = 0;

	unsigned int remainder = epoch;
	int flag = 1;
	while (flag){
		int yearSeconds = 31622400;
		if (  ( year % 4 ) || ( year == 2100 )  ){
			yearSeconds = 31536000;
		}
		if ( remainder > yearSeconds ){
			remainder -= yearSeconds;
			year += 1;
		} else {
			flag = 0;
		}
	}
	int daysInEachMonth[] = {31,29,31,30,31,30,31,31,30,31,30,31};
	//not leap year
	if (  ( year % 4 ) || ( year == 2100 )  ){
		daysInEachMonth[1] = 28; 
	}
	flag = 1;
	while (flag){
		if ( remainder > ( daysInEachMonth[month-1] * 86400 )  ){
			remainder -= ( daysInEachMonth[month-1] * 86400 );
			month += 1;
		} else {
			flag = 0;
		}
	}
	while ( remainder >= 86400 ){
		remainder -= 86400;
		day += 1;
	}
	while ( remainder >= 3600 ){
		remainder -= 3600;
		hour += 1;
	}
	while ( remainder >= 60 ){
		remainder -= 60;
		minute += 1;
	}
	second = remainder;

	date[0] = year;
	date[1] = month;
	date[2] = day;
	date[3] = hour;
	date[4] = minute;
	date[5] = second;
	return;
}

void cgc_strofdate( unsigned int epoch ){

	char *days[7] = {"Thursday","Friday","Saturday","Sunday","Monday","Tuesday","Wednesday"};
	char *months[12] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
	int date[6];
	cgc_date_from_epoch(epoch, date);
	unsigned int dayOfWeek = ( ( epoch/86400 ) % 7 );
	char *weekday = days[dayOfWeek];
	char *month = months[date[1]-1];
	cgc_printf( "@s, @s @d @d @d:@d:@d GMT\n", weekday, month, date [0], date[2], date[3], date[4], date[5] );
	return;
}

unsigned int cgc_make_epoch( int year, int month, int day, int hour, int minute, int second ){
	unsigned int retval = 0;
	//leap year
	int daysInEachMonth[] = {31,29,31,30,31,30,31,31,30,31,30,31};
	//not leap year
	if (  ( year % 4 ) || ( year == 2100 )  ){
		daysInEachMonth[1] = 28; 
	}
	//add seconds in years from 1970 to now
	for (int i = 1970; i < year; i++){
		//not leap year
		if (  ( i % 4 ) || ( i == 2100 )  ){
			retval += 31536000;
		}else {
			retval += 31622400;
		}
	}
	//add seconds in months for current year
	for (int i = 1; i < month; i++){
		retval += (daysInEachMonth[i-1] * 86400);
	}
	//add seconds in days of current month
	retval += ( (day - 1) * 86400);
	//add seconds in hours of current day
	retval += (hour * 3600);
	//add seconds in minutes of current hour
	retval += (minute * 60);
	//add remaining seconds
	retval += second;
	return retval;
}

unsigned int cgc_get_time(){
	int year = 0;
	int month = 0;
	int day = 0;
	int hour = 100;
	int minute = 100;
	int second = 100;
	cgc_puts("Please enter the date as prompted");
	while ( year == 0 ){
		year = cgc_get_int("Enter year between 1970 and 2105");
		if (  ( year < 1970 ) || ( year > 2105 )  ){
			cgc_puts("Bad value for year");
			year = 0;
		}
	}
	while ( month == 0 ){
		month = cgc_get_int("Enter month");
		if (  ( month < 1 ) || ( month > 12 )  ){
			cgc_puts("Bad value for month");
			month = 0;
		}
	}
	while ( day == 0 ){
		//leap year 
		int daysInEachMonth[] = {31,29,31,30,31,30,31,31,30,31,30,31};
		//not leap year
		if  (  ( year % 4 ) || ( year == 2100 )  ){
			daysInEachMonth[1] = 28; 
		}
		day = cgc_get_int("Enter day");
		if (  ( day < 1 ) || ( day > daysInEachMonth[month-1] )  ){
			day = 0;
		}
	}
	while ( hour == 100 ){
		hour = cgc_get_int("Enter hour (00-23)");
		if ( hour > 23 ){
			hour = 100;
		}
	}
	while ( minute == 100 ){
		minute = cgc_get_int("Enter Minute (00-59)");
		if ( minute > 59 ){
			minute = 100;
		}
	}
	while ( second == 100 ){
		second = cgc_get_int("Enter second (00-59)");
		if ( second > 59 ){
			second = 100;
		}
	}
	return cgc_make_epoch(year, month, day, hour, minute, second);
}

void cgc_start_UI(pDataStruct workingData){
	cgc_puts("Welcome to SPIFFS (Somewhat Poorly Implemented Fast File System)");
	workingData->date = cgc_get_time();
	cgc_main_loop(workingData);
	return;
}