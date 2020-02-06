#include "libcgc.h"
#include "cgc_stdlib.h"

/*

Author: John Berry <john.n.berry@gmail.com>

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

/* Service that allows people to post messages to each other
 * Create User
 * Delete User
 * Login
 * Logout
 * Read Message
 * Send Message
 * List Messages
 * Delete Message
 *
*/

#define MESSAGE_LENGTH 0x20
#define USERNAME_LENGTH 0x10

/**
 * Structure to store an individual message and necessary metadata
 **/
typedef struct message {
	struct message *next;
	unsigned int message_id;
	unsigned int cgc_read;
	char message[MESSAGE_LENGTH];
} message, *pmessage;

/**
 * Structure to manage the messages for a single user
 **/
typedef struct message_manager {
	pmessage root;
	unsigned int message_count;
} message_manager, *pmessage_manager;

/**
 * Structure with necessary data for an individual user.
 **/
typedef struct user {
	char name[USERNAME_LENGTH];
	pmessage_manager pmm;	
	struct user *next;
} user, *puser;

/**
 * Structure to manage all users. Only one instance of this per application execution.
 **/
typedef struct user_manager {
	puser root;
	unsigned int user_count;
} user_manager, *puser_manager;

pmessage_manager cgc_init_manager( void );

/**
 * Lists all existing users. This functions is for debugging purposes only. Normal
 *   execution will never call here.
 * @param pum List all existing usernames.
 * @return Returns nothing.
 **/
void cgc_list_users( puser_manager pum )
{
	puser walker = NULL;

	if ( pum == NULL ) {
		goto end;
	}

	walker = pum->root;

	while ( walker ) {
		cgc_puts(walker->name);
		walker = walker->next;
	}
end:
	return;
}

/**
 * Initialize the global user management structure. This should only be called once
 * @return Returns the user management structure for a give execution or NULL on error.
 **/
puser_manager cgc_init_users( void )
{
	puser_manager pum = NULL;

	if ( cgc_allocate( sizeof(user_manager), 0, (void**)&pum ) != 0) {
		cgc_puts( "[-] Error Failed to allocate buffer\n" );
		goto end;
	}

	pum->root = NULL;
	pum->user_count = 0;
end:
	return pum;
}

/**
 * Creates a new user and adds it to the user management structure.
 * @param pum A pointer to the global user management structure.
 * @param username Pointer to an ascii username.
 * @return Returns the newly created user id or 0 on failure.
 **/
cgc_size_t cgc_create_user( puser_manager pum, char *username )
{
	cgc_size_t id = 0;
	puser walker = NULL;
	puser newuser = NULL;

	if ( pum == NULL ) {
		goto end;
	}

	if ( username == NULL ) {
		goto end;
	}

	if ( cgc_strlen(username) > USERNAME_LENGTH - 1 ) {
		cgc_puts("[-] Error username too long\n");
		goto end;
	}

	// Check for existing username
	walker = pum->root;

	while ( walker ) {
		if ( cgc_strcmp( walker->name, username ) == 0) {
			cgc_puts("[-] Error user exists\n");
			goto end;
		}
		walker = walker->next;
	}

	// Create user stucture
	if ( cgc_allocate( sizeof(user), 0, (void**)&newuser) != 0 ) {
		cgc_puts("[-] Error allocating user structure\n");
		goto end;
	}
	
	newuser->next = NULL;
	newuser->name[0] = 0x00;
	newuser->pmm = cgc_init_manager();

	cgc_strncat( newuser->name, username, USERNAME_LENGTH );

	// Check root user first
	if ( pum->root == NULL ) {
		pum->root = newuser;
		pum->user_count++;
		id = pum->user_count;
		goto end;
	}

	// Link in new user
	newuser->next = pum->root;
	pum->root = newuser;

	pum->user_count++;
	id = pum->user_count;
	
end:
	return id;
}

/**
 * Initializes the message manager structure. This will be called once per new user.
 * @return Returns the new message manager structure or NULL on failure.
 **/
pmessage_manager cgc_init_manager( void )
{
	pmessage_manager pmm = NULL;

	if ( cgc_allocate( sizeof(message_manager), 0, (void**)&pmm ) != 0) {
		cgc_puts( "[-] Error Failed to allocate buffer\n" );
		goto end;
	}

	pmm->root = NULL;
	pmm->message_count = 0;
end:
	return pmm;
}

/**
 * Adds a new message to a users message manager.
 * @param pman Pointer to a users message management structure.
 * @param pm Pointer to the message to add
 * @return Id of the new message or 0 on failure.
 **/
cgc_size_t cgc_add_message( pmessage_manager pman, pmessage pm )
{
	cgc_size_t id = 0;
	pmessage walker = NULL;

	if ( pm == NULL ) {
		goto end;
	}

	if ( pman == NULL ) {
		goto end;
	}

	// If there are no additional messages, this one goes
	//	on the root
	if ( pman->root == NULL ) {
		pman->root = pm;
		pman->message_count++;
		pm->message_id = pman->message_count;
		id = pm->message_id;
		goto end;
	}

	walker = pman->root;

	while ( walker->next != NULL ) {
		walker = walker->next;
	}

	walker->next = pm;
	pman->message_count++;
	pm->message_id = pman->message_count;
	id = pm->message_id;

end:
	return id;
}

/**
 * Creates a new message with the given text.
 * @param msg_string String containing the data to store in the message.
 * @return Returns a message structure that must be added to the message manager or NULL on failure.
 **/
pmessage cgc_create_message( char * msg_string )
{
	pmessage pmsg = NULL;
	int counter = 0;

	if ( msg_string == NULL ) {
		goto end;
	}

	if ( cgc_strlen( msg_string ) > MESSAGE_LENGTH - 1 ) {
		cgc_puts("[-] Error Message too long\n");
		goto end;
	}

	if ( cgc_allocate( sizeof(message), 0, (void**)&pmsg)  != 0 ) {
		cgc_puts("[-] Error Failed to allocate message struct\n");
		goto end;
	}

	pmsg->next = NULL;
	pmsg->message_id = 0;
	pmsg->cgc_read = 0;

	cgc_bzero( pmsg->message, MESSAGE_LENGTH );

	for ( counter = 0; counter < cgc_strlen( msg_string ); counter++ ) {
		pmsg->message[counter] = msg_string[counter];
	}

end:
	return pmsg;
}

/**
 * Deletes a message with a given id from a users message list.
 * @param pmm Pointer to a users message management structure.
 * @param message_id Id of the message to be deleted.
 * @return Only returns void. Any errors are displayed to the user.
 **/
void cgc_delete_message( pmessage_manager pmm, cgc_size_t message_id )
{
	pmessage walker = NULL;
	pmessage prev = NULL;

	if ( pmm == NULL ) {
		goto end;
	}

	if ( message_id > pmm->message_count ) {
		cgc_puts( "[-] Message ID out of range\n");
		goto end;
	}

	walker = pmm->root;

	while ( walker ) {
		if ( walker->message_id == message_id ) {
			// If prev is null that means the root message
			//   is the one to be deleted
			if ( prev == NULL ) {
				pmm->root = walker->next;
			} else {
				prev->next = walker->next;
			}

			cgc_deallocate( walker, sizeof( message ) );
			goto end;
		}

		prev = walker;
		walker = walker->next;
	}

	if ( walker == NULL ) {
		cgc_puts("[-] Message ID not found\n");
	}
end:
	return;
}

/**
 * Displays a single message to a user
 * @param pmm Pointer to the message manager structure of a user.
 * @param message_id Id of the message to be displayed.
 **/
void cgc_read_message( pmessage_manager pmm, cgc_size_t message_id )
{
	cgc_size_t retval = 0;
	pmessage walker = NULL;
	char buffer[0x100];

	if ( pmm == NULL ) {
		goto end;
	}

	if ( message_id > pmm->message_count ) {
		cgc_puts( "[-] Message ID out of range\n");
		goto end;
	}

	cgc_bzero( buffer, 0x100 );
	cgc_strncat( buffer, "***********************************\n", 0x100 );
	
	walker = pmm->root;

	while ( walker ) {
		if ( walker->message_id == message_id ) {
			retval = cgc_strlen(buffer);
			cgc_itoa( buffer + retval, message_id, 0x100-retval );
			cgc_strncat(buffer, ":  ", 0x100 );
			cgc_strncat(buffer, walker->message, 0x100 );
			cgc_strncat( buffer, "\n***********************************\n", 0x100 );
			cgc_puts( buffer );
			walker->cgc_read = 1;
			goto end;
		}

		walker = walker->next;
	}

	if ( walker == NULL ) {
		cgc_puts("[-] Message ID not found\n");
	}

end:
	return;
}

/**
 * Lists all unread messages of a user. This function is where the bug is. The variable
 *  used to store the number of unread messages is an unsigned char so if more than 255
 *  messages are waiting to be displayed this counter will overflow. The counter is used
 *  to calculate the size of the buffer necessary to display the messages. A counter
 *  that has overflowed will result in the allocation of a buffer that is too small to
 *  contain the entire stream of messages.
 * @param pmm A pointer to the message manager of a user
 **/
void cgc_list_unread_messages( pmessage_manager pmm )
{
	pmessage walker = NULL;
	cgc_size_t size = 0;
#ifdef PATCHED
	unsigned int count = 0;
#else
	unsigned char count = 0;
#endif

	if ( pmm == NULL ) {
		return;
	}
	walker = pmm->root;

	while ( walker ) {
		if ( walker->cgc_read == 0 ) {
			count++;
		}
		walker= walker->next;
	}

	if ( count == 0 ) {
		return;
	}

	cgc_puts("Unread messages:\n");

	// Calculate size
	// Message Text
	size = count * MESSAGE_LENGTH;
	// Message border
	size += count * (72);
	// Message id and trailing newline
	// "###:  "
	size += count * 8;

	char data[size];

	cgc_bzero( data, size );

	walker = pmm->root;

	while ( walker ) {
		if ( walker->cgc_read == 0 ) {

			// Mark the message as cgc_read
			walker->cgc_read = 1;
			cgc_strcat( data, "***********************************\n");
			cgc_itoa( data + cgc_strlen(data), walker->message_id, 4 );
			cgc_strcat( data, ":  " );
			cgc_strcat( data, walker->message );
			cgc_strcat( data, "\n");
			cgc_strcat( data, "***********************************\n");
		}
		walker = walker->next;
	}

	cgc_puts( data );
end:
	return;
}

/**
 * List all existing messages of a user including those already cgc_read.
 * @param pmm Pointer to the message management structure of a user.
 **/
void cgc_list_messages( pmessage_manager pmm )
{
	pmessage walker = NULL;

	if ( pmm == NULL ) {
		goto end;
	}

	walker = pmm->root;

	while ( walker ) {
		cgc_read_message( pmm, walker->message_id );
		walker = walker->next;
	}
end:
	return;
}

/**
 * Retrieve a specific user structure from the manager
 * @param pum Pointer to the global user management structure
 * @param username Pointer to the username of the user to locate
 * @return Returns a pointer to the requested user management structure or NULL on failure.
 **/
puser cgc_get_user( puser_manager pum, char *username )
{
	puser pu = NULL;

	if ( pum == NULL || username == NULL ) {
		goto end;
	}

	pu = pum->root;

	while ( pu ) {
		if ( cgc_strcmp( pu->name, username ) == 0 ) {
			goto end;
		}
		pu = pu->next;
	}
end:
	return pu;
}

/**
 * Stores a message for a specific user
 * @param pum Pointer to the global user management structure
 * @param username Username of the user to send the message to
 * @param msg Pointer to the message to send to the user.
 * @return Returns the id of the sent message or 0 on failure.
 **/
cgc_size_t cgc_send_user_message( puser_manager pum, char *username, char *msg )
{
	cgc_size_t id = 0;
	puser pu = NULL;
	pmessage pmsg = NULL;

	if ( pum == NULL || username == NULL || msg == NULL ) {
		goto end;
	}

	pu = cgc_get_user( pum, username );

	if ( pu == NULL ) {
		cgc_puts("[-] Error invalid user\n");
		goto end;
	}

	pmsg = cgc_create_message( msg );

	if ( pmsg == NULL ) {
		cgc_puts("[-] Failed to create message\n");
		goto end;
	}

	if ( (id = cgc_add_message( pu->pmm, pmsg )) == 0 ) {
		cgc_puts("[-] Failed to add message\n");
		goto end;
	}	
end:
	return id;
}

/**
 * Handles the sub menu for a logged in user
 * @param pum Pointer to the global user management structure
 * @param pu Pointer to the user structure for the logged in user
 **/
void cgc_handle_loggedin( puser_manager pum, puser pu )
{
	cgc_size_t choice = 0;
	char message[MESSAGE_LENGTH];
	char username[USERNAME_LENGTH];
	
	if ( pum == NULL || pu == NULL ) {
		goto end;
	}

	while ( 1 ) {
		cgc_list_unread_messages( pu->pmm );

		cgc_puts("1) Send Message\n");
		cgc_puts("2) Read Message\n");
		cgc_puts("3) List Messages\n");
		cgc_puts("4) Delete Message\n");
		cgc_puts("5) Logout\n");
		cgc_puts("6) Exit\n");
		cgc_puts(": ");

		choice = 0;

		if ( cgc_receive_until( (char*)&choice, 0x0a, 2 ) == 0 ) {
			cgc_puts("[-] Receive failed\n");
			cgc__terminate(0);
		}

		choice -= 0x30;

		if ( choice > 6 || choice < 1 ) {
			cgc_puts("[-] Invalid choice\n");
			continue;
		}

		if ( choice == 6 ) {
			cgc_puts("Exiting...\n");
			cgc__terminate(0);
		} else if ( choice == 5 ) {
			cgc_puts("Logging out...\n");
			goto end;
		} else if ( choice == 4 ) {
			cgc_puts("ID: ");
			cgc_bzero( message, MESSAGE_LENGTH);
			cgc_receive_until( message, '\n', 4 );
			choice = cgc_atoi( message );
			cgc_delete_message( pu->pmm, choice );
		} else if ( choice == 3 ) {
			cgc_list_messages( pu->pmm );
		} else if ( choice == 2 ) {
			cgc_puts("ID: ");
			cgc_bzero( message, MESSAGE_LENGTH );
			cgc_receive_until( message, '\n', 4 );
			choice = cgc_atoi( message );
			cgc_read_message( pu->pmm, choice );
		} else if ( choice == 1 ) {
			cgc_bzero( message, MESSAGE_LENGTH );
			cgc_bzero( username, USERNAME_LENGTH );

			cgc_puts("To: ");
			cgc_receive_until( username, '\n', USERNAME_LENGTH-1);
			cgc_puts("Message: ");
			cgc_receive_until( message, '\n', MESSAGE_LENGTH-1);
			cgc_send_user_message( pum, username, message );
		}
	}

end:
	return;
}

/**
 * Function to handle the main user interface loop
 **/
void cgc_handle_menu ( )
{
	puser_manager pum = NULL;
	puser current_user = NULL;
	cgc_size_t choice = 0;
	cgc_size_t received = 0;
	char username[USERNAME_LENGTH];

	pum = cgc_init_users( );

	if ( pum == NULL ) {
		goto end;
	}

	while ( 1 ) {
		choice = 0;

		cgc_puts("1) Create User\n");
		cgc_puts("2) Login\n");
		cgc_puts("3) Exit\n");
		cgc_puts(": ");

		if ( cgc_receive_until( (char*)&choice, '\n', 2 ) == 0 ) {
			cgc_puts("[-] Receive Failed\n");
			cgc__terminate(0);
		}

		choice -= 0x30;

		if ( choice > 3 || choice < 1 ) {
			cgc_puts("[-] Invalid choice\n");
			continue;
		}

		cgc_bzero( username, USERNAME_LENGTH );

		if ( choice == 3 ) {
			cgc_puts("Exiting...\n");
			cgc__terminate( 0 );
		} else if ( choice == 1 ) {
			cgc_puts("username: ");
			cgc_receive_until( username, '\n', USERNAME_LENGTH - 1);
			cgc_create_user( pum, username );
		} else if ( choice == 2 ) {
			cgc_puts("username: ");
			cgc_receive_until( username, '\n', USERNAME_LENGTH - 1);
			current_user = cgc_get_user( pum, username );
			if ( current_user != NULL ) {
				cgc_puts("Login Success\n");
				cgc_handle_loggedin( pum, current_user );
				current_user = NULL;
			} else {
				cgc_puts("Login Failed\n");
			}
		}
	}

end:
	return;
}

/**
 * Main function just calls handle_menu
 * @return Always returns 0
 **/
int main(int cgc_argc, char *cgc_argv[]) {
	cgc_handle_menu();
	return 0;
}
