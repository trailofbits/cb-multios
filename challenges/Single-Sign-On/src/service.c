/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "libcgc.h"
#include "cgc_libc.h"
#include "cgc_service.h"

void cgc_reportMessage(char* message, cgc_size_t message_size) {
	int ret;
	ret = cgc_transmit_all(STDOUT, message, message_size);
	if(ret != 0)
		cgc__terminate(TRANSMIT_ERROR);
}

unsigned long cgc_getAuthVal() {

	unsigned long auth_val;
	cgc_size_t rnd_bytes;
	int ret;

	int b;
	for(b = 0; b<4; b++) {
		char byte = 0;
		while (byte == 0 || byte == 0x0a) {
			ret = cgc_random((void *)&byte, sizeof(byte), &rnd_bytes);
			if(ret != 0)
				cgc__terminate(RANDOM_ERROR);	
		}
		((unsigned char*)(&auth_val))[b] = byte;
	}


	return auth_val;
}

void cgc_receiveCommand(Command* command) {
	int bytesReceived = 0;
	int ret;

	bytesReceived = cgc_recv(STDIN, (char *) command, CMD_TYPE_SIZE+sizeof(unsigned long)*2);
	if(bytesReceived < 0)
		cgc__terminate(RECEIVE_ERROR);

	// Work-around for receive() race condition bug
	for(ret = 0; ret < 100; ret++)
		cgc_getAuthVal();

	bytesReceived = cgc_recvline(STDIN, command->input, MAX_ARGS_SIZE);	
	if(bytesReceived < 0)
		cgc__terminate(RECEIVE_ERROR);

}

void cgc_auth_failure(char* resource) {	
	char temp_buf[201];
	char* message_buf=NULL;
	int ret;
	cgc_size_t message_size; 

	message_size = cgc_strlen(resource)+sizeof(FAILED_AUTH_STR)+sizeof(EOL);

	if(message_buf == NULL) {
		message_buf = cgc_malloc(message_size);
		if(message_buf == NULL)
			cgc__terminate(ALLOCATE_ERROR);
		cgc_memset(message_buf, 0, message_size);
	}

	cgc_strcat(message_buf, FAILED_AUTH_STR);
	cgc_strcat(message_buf, resource);
	cgc_strcat(message_buf, EOL);

	cgc_reportMessage(message_buf, cgc_strlen(message_buf));

#ifdef PATCHED
	cgc_free(message_buf);
#else
#endif

}

unsigned long cgc_auth_success(char* resource) {
	char temp_buf[200]; // aligns message_buf
#ifdef PATCHED
	char* message_buf = NULL;
#else
	char* message_buf; 
#endif
	int ret;
	int message_size;
	int zero = 0; // Null terminates token
	unsigned long token[] = {0,0};

	message_size = sizeof(ACCESS_STR) + cgc_strlen(resource)+sizeof(SUCCESS_AUTH_STR)+sizeof(token)+sizeof(EOL);

	// Vuln 1: Bypass check due to unititialized buffer
	if(message_buf == NULL) {
		message_buf = cgc_malloc(message_size);
		if(message_buf == NULL)
			cgc__terminate(ALLOCATE_ERROR);
	}

	token[0] = cgc_getAuthVal();
	// Vuln 1: Overflow buffer that is < message_size
	cgc_memset(message_buf, 0, message_size);
	cgc_strcat(message_buf, ACCESS_STR);
	cgc_strcat(message_buf, resource);
	cgc_strcat(message_buf, SUCCESS_AUTH_STR);
	cgc_strcat(message_buf, (char *)token);
	cgc_strcat(message_buf, EOL);

	cgc_reportMessage(message_buf, cgc_strlen(message_buf));

#ifdef PATCHED
	cgc_free(message_buf);
#else
#endif

	return token[0];

}


int cgc_do_auth(unsigned long val, unsigned long auth_attempt, char* res)
{
	int ret=0;
	unsigned long auth_val;
	auth_val = val;

	if(auth_val != auth_attempt)
	{
		//Vuln 0: Copies message + auth_val for mem_leak
		char resource[RESOURCE_SIZE];
		cgc_memset(resource, 0, RESOURCE_SIZE);
		cgc_memcpy(resource, res, cgc_strnlen(res, RESOURCE_SIZE));
		cgc_auth_failure(resource);
		return AUTH_FAIL;
	} else {
		return cgc_auth_success(res);
	}
}

unsigned long cgc_getResourceToken(Resource* resourceList, char* resource) {

	Resource* resource_ptr;
	for(resource_ptr=resourceList; resource_ptr!= NULL; resource_ptr=resource_ptr->next) {
		if(resource_ptr->name && cgc_strncmp(resource_ptr->name, resource, RESOURCE_SIZE) == 0)
			return resource_ptr->token;
	}

	return NOT_FOUND;
}

void cgc_addResource(User** user, unsigned long token, char* resource) {

	Resource* resource_ptr;
	for(resource_ptr=(*user)->resourceList; resource_ptr!= NULL; resource_ptr=resource_ptr->next) {
		if(resource_ptr->name && cgc_strncmp(resource_ptr->name, resource, RESOURCE_SIZE) == 0) {
			resource_ptr->token = token;
			return;
		}
	}

	Resource* newResource;
	newResource = (Resource *) cgc_malloc(sizeof(Resource));
	if(!newResource)
		cgc__terminate(ALLOCATE_ERROR);

	cgc_memcpy(newResource->name, resource, RESOURCE_SIZE);
	newResource->token = token;
	newResource->next = (*user)->resourceList;
	(*user)->resourceList = newResource;
}

User* cgc_createNewUser(User** userList, unsigned long token, unsigned long id) {
	User* newUser;
	newUser = (User *) cgc_malloc(sizeof(User));
	if(!newUser)
		cgc__terminate(ALLOCATE_ERROR);

	newUser->id = id;
	newUser->token = token;
	newUser->resourceList = NULL;
	newUser->next = *userList;
	*userList = newUser;

	return newUser;
}

User* cgc_getUser(User* userList, unsigned long id) {

	User* user_ptr;
	for(user_ptr=userList; user_ptr!= NULL; user_ptr=(User *)user_ptr->next) {
		if(user_ptr->id  == id)
			return user_ptr;
	}

	return 0;
}

void cgc_revokeResource(User** user, unsigned long resourceToken, char* resourceName) {
	Resource* resource_ptr;
	for(resource_ptr=(*user)->resourceList; resource_ptr!= NULL; resource_ptr=resource_ptr->next) {
		if(resource_ptr->name && (cgc_strncmp(resource_ptr->name, resourceName, RESOURCE_SIZE) == 0)) {
			if(resource_ptr->token == resourceToken){
				resource_ptr->token = ACCESS_REVOKED;		
				cgc_reportMessage(RES_REVOKED_STR, sizeof(RES_REVOKED_STR)-1);
				return;
			} else {
				cgc_reportMessage(REVOKE_DENIED_STR, sizeof(REVOKE_DENIED_STR)-1);
				return;
			}
		}
	}

	cgc_reportMessage(REVOKE_DENIED_STR, sizeof(REVOKE_DENIED_STR)-1);
	return;

}

int cgc_logoutUser(User** userList, unsigned long id) {

	User *user_prev, *user_ptr;
	user_prev = *userList;
	for(user_ptr=*userList; user_ptr!=NULL; user_ptr=(User *)user_ptr->next) {
		if(user_ptr->id == id) {
			Resource *resource_ptr, *next_ptr;
			resource_ptr=user_ptr->resourceList;
			while(resource_ptr!=NULL) {
				next_ptr = resource_ptr->next;
				cgc_free(resource_ptr);
				resource_ptr=next_ptr;
			}
			if(user_ptr != *userList)
				user_prev->next = user_ptr->next;
			else
				*userList = user_ptr->next;
			cgc_free(user_ptr);
			return 0;
		}
		user_prev = user_ptr;
	}

	return 1;
}

int main(int cgc_argc, char *cgc_argv[]) {

	Command command;
	unsigned long auth_val=0;
	User* userList=NULL;
	int newRequest=0;
	int ret;

	while(1) {
		User* user=NULL;
		cgc_memset(command.input, 0, MAX_ARGS_SIZE);
		cgc_receiveCommand(&command);

		user = cgc_getUser(userList, command.id);

		if(cgc_strcmp(AUTH_CMD, command.type) == 0) {
			unsigned long result;
			unsigned long resource_val;

			if(!user) {
				auth_val = cgc_getAuthVal();
				user = cgc_createNewUser(&userList, auth_val, command.id);
			}
			
			auth_val = user->token;
			result = cgc_do_auth(user->token, command.token, command.input);
			if(result > AUTH_FAIL) {
				newRequest = 0;
				cgc_addResource(&user, result, command.input);
				auth_val = 0;
			}
			continue;
		}

		if(!user) {
			cgc_reportMessage(CMD_FAIL_STR, sizeof(CMD_FAIL_STR)-1);
			continue;

		}

		if(cgc_strcmp(LOGOUT_CMD, command.type) == 0) {
			cgc_logoutUser(&userList, command.id);
			cgc_reportMessage(LOGGED_OUT_STR, sizeof(LOGGED_OUT_STR)-1);
			
			if(userList == NULL)
				return 0;
			else
				continue;
		}

		if(cgc_strcmp(REQUEST_CMD, command.type) == 0) {
			unsigned long result=0;
			unsigned long resource_val = 0;

			resource_val = cgc_getResourceToken(user->resourceList, command.input);
			if(resource_val == ACCESS_REVOKED) 
				result = AUTH_FAIL;
			else if(resource_val > ACCESS_REVOKED && command.token > ACCESS_REVOKED)
				result = cgc_do_auth(resource_val, command.token, command.input);
			
			if(result > AUTH_SUCCESS)
				continue;
			else if(result == AUTH_FAIL) {
				cgc_reportMessage(REAUTH_STR, sizeof(REAUTH_STR)-1);
				continue;
			} else {
				cgc_reportMessage(AUTH_STR, sizeof(AUTH_STR)-1);
				continue;
			}

		}

		if(cgc_strcmp(REVOKE_RESOURCE_CMD, command.type) == 0) {
			cgc_revokeResource(&user, command.token, command.input);
			continue;
		}

	}
}
