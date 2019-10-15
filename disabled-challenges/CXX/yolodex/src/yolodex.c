/*

Author: Dustin Fraze (df@cromulence.co)

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

#include "libcgc.h"
#include "cgc_stdlib.h"

#define YOLO_ADD 0x40
#define YOLO_DEL 0x41
#define YOLO_EDIT 0x42
#define YOLO_SHOW 0x43
#define YOLO_LIST 0x44
#define YOLO_SORT 0x45
#define YOLO_EXIT 0x46

unsigned int cgc_cookie = 0;

typedef struct _contact {
	char first[32];
	char last[32];
	char phone[16];
	unsigned short officenum;
	char gender;
	char hacker;
	unsigned int cookie;
	int pad;
	struct _contact *prev;
	struct _contact *next;
} contact;

contact *cgc_head = NULL;

void cgc_put(char *str) {
	cgc_transmit(1, str, cgc_strlen(str), 0);
}

int cgc_validateName(char *name)
{
	//let's make it title case.  And lets yell if its not.
	if(name[0] >= 'A' && name[0] <= 'Z')
		return 1;
	else
		return 0;
}

int cgc_validatePhone(char *phonenumber)
{
	int i;
	char *digit;

	digit = phonenumber;
	if(*digit++ != '(')
		return 0;
	for(i=0;i<3;i++,digit++)
	{
		if(*digit < '0' || *digit > '9')
			return 0;
	}
	if(*digit++ != ')')
		return 0;
	for(i=0;i<3;i++,digit++)
	{
		if(*digit < '0' || *digit > '9')
			return 0;
	}
	if(*digit++ != '-')
		return 0;
	for(i=0;i<4;i++,digit++)
		if(*digit < '0' || *digit > '9')
			return 0;
	return 1;
}

contact *cgc_createContact(char *first, char *last, char *phone, unsigned short officenum, char gender, char hacker)
{
	contact *ret = NULL;
	ret = (contact *)cgc_calloc(1, sizeof(contact));
	if(ret == NULL)
	{
		cgc_puts("Couldn't allocate contact.  Something's wrong.");
		cgc__terminate(-1);
	}
	if(cgc_validateName(first)) {
		cgc_memcpy(ret->first, first, cgc_strlen(first));
	} else {
		cgc_puts("Invalid first name.  Must begin with a capital letter.");
		cgc_free(ret);
		ret = NULL;
		return NULL;
	}
	if(cgc_validateName(last)) {
		cgc_memcpy(ret->last, last, cgc_strlen(last));
	} else {
		cgc_puts("Invalid last name.  Must begin with a capital letter.");
		cgc_free(ret);
		ret = NULL;
		return NULL;
	}
	if(cgc_validatePhone(phone)) {
		cgc_memcpy(ret->phone, phone, cgc_strlen(phone));
	} else {
		cgc_puts("Invalid phone number...must look like (nnn)nnn-nnnn");
		cgc_free(ret);
		ret = NULL;
		return NULL;
	}
	ret->officenum = officenum;
	ret->gender = gender;
	ret->hacker = hacker;
	ret->cookie = cgc_cookie;
	ret->pad = 0;
	ret->next = NULL;
	ret->prev = NULL;
	return ret;
}

void cgc_insert(contact *toAdd)
{
	contact *tmp;
	if(cgc_head == NULL) {
		cgc_head = toAdd;
		return;
	}
	tmp = cgc_head;
	while(tmp->next != NULL) {
		tmp = tmp->next;
	}
	tmp->next = toAdd;
	toAdd->prev = tmp;
}

contact *cgc_remove(contact *toRemove)
{
	if((toRemove->next == NULL) && (toRemove->prev == NULL)) {
		cgc_head = NULL;
		return toRemove;
	}

	if(toRemove->prev == NULL) {
		cgc_head = toRemove->next;
		toRemove->next->prev = NULL;
	}
	else
		toRemove->prev->next = toRemove->next;

	if(toRemove->next == NULL)
		toRemove->prev->next = NULL;
	else
		toRemove->next->prev = toRemove->prev;

	toRemove->next = NULL;
	toRemove->prev = NULL;
	return toRemove;
}

void cgc_printGender(char gender)
{
	switch(gender)
	{
		case 'M':
			cgc_puts("Male");
			break;
		case 'F':
			cgc_puts("Female");
			break;
		case 'T':
			cgc_puts("Trans-Gender");
			break;
		default:
			cgc_puts("Other");
	}
}

void cgc_printContact(contact *toPrint)
{
	cgc_put("First Name: \t");
	cgc_puts(toPrint->first);
	cgc_put("Last Name: \t");
	cgc_puts(toPrint->last);
	cgc_put("Phone Number: \t");
	cgc_puts(toPrint->phone);
}

void cgc_printList() {
	contact *ptr;
	ptr = cgc_head;
	if(cgc_head == NULL)
		cgc_puts("Empty yolodex.");
	while(ptr != NULL)
	{
		cgc_puts("========================================");
		cgc_printContact(ptr);
		ptr = ptr->next;
	}
	cgc_puts("========================================");
}

void cgc_sortYolodex() {
	contact *ptr;
	contact *tmp;
	contact *first;
	contact *other;
	contact *sorted = NULL;
	int i;

	ptr = cgc_head;
	first = cgc_head;
	tmp = cgc_head;

	while(tmp != NULL)
	{
		while(ptr != NULL)
		{
			i = 0;
			while(first->last[i] && ptr->last[i])
			{
				if(first->last[i] > ptr->last[i]) {
					first = ptr;
					break;
				}
				if(first->last[i] == ptr->last[i])
					i++;
				else
					break;
			}
			if(!ptr->last[i] && first->last[i])
				first = ptr;
			ptr = ptr->next;
		}
		tmp = cgc_remove(first);
		if(sorted == NULL)
		{
			sorted = first;
		} else {
			other = sorted;
			while(other->next != NULL)
				other = other->next;
			other->next = tmp;
			tmp->prev = other;
		}
	first = cgc_head;
	ptr = cgc_head;
	tmp = cgc_head;
	}
	cgc_head = sorted;
}

void cgc_initYolodex() {
	cgc_head = cgc_createContact("Robert", "Morris", "(617)253-5982", 32972, 'M', 'y');
	cgc_insert(cgc_createContact("Chareth", "Cutestory", "(123)456-7890", 4242, 'M', 'n'));
	cgc_insert(cgc_createContact("Tim", "Berners-Lee", "(638)844-2074", 404, 'M','y'));
	cgc_insert(cgc_createContact("Pwnies", "McPwn", "(222)223-1337", 31337, 'F','y'));
	cgc_insert(cgc_createContact("Jenny", "Fakename", "(555)867-5309", 31337, 'F','n'));
}

int cgc_recvUntil(char *dst, int n, char delim)
{
	char *tmp;
	cgc_size_t gotBytes;
	tmp = dst;
	while(n--)
	{
		cgc_receive(STDIN, tmp, 1, &gotBytes);
		if(gotBytes == 0) {
			cgc__terminate(-1);
		}
		if(*tmp == delim) {
			*tmp = 0;
			break;
		}
		tmp++;
	}
	return tmp-dst;
}

void cgc_promptAdd() {
	char first[32];
	char last[32];
	char phone[16];
	char officetmp[8];
	short officenum;
	char gender;
	char hacker;
	char tmp[2];

	contact *ptr;
	cgc_memset(phone, 0, 16);
	cgc_memset(officetmp, 0, 8);
	ptr = NULL;
	while(ptr == NULL) {
		cgc_put("First: ");
		cgc_recvUntil(first, 32, '\n');
		cgc_put("Last: ");
		cgc_recvUntil(last, 32, '\n');
		cgc_put("Phone Number: ");
		cgc_recvUntil(phone, 14, '\n');
		cgc_put("Office Number: ");
		cgc_memset(officetmp, 0, 8);
		cgc_recvUntil(officetmp, 6, '\n');
		officenum = (unsigned short)cgc_atoi(officetmp);
		cgc_put("Gender: ");
		cgc_recvUntil(tmp, 2, '\n');
		gender = tmp[0];
		hacker = '?';
		while(hacker == '?')
		{
			cgc_put("Hacker: ");
			cgc_recvUntil(tmp, 2, '\n');
			if(tmp[0] == 'n' || tmp[0] == 'y')
				hacker = tmp[0];
			else
				cgc_puts("Please enter y or n for hacker.");
		}
		ptr = cgc_createContact(first, last, phone, officenum, gender, hacker);
	}
	if(ptr->cookie != cgc_cookie)
	{
		cgc_puts("Contact corruption detected.");
		cgc__terminate(-1);
	}
	cgc_insert(ptr);
}

contact *cgc_findContact() {
	char first[32];
	char last[32];
	contact *ptr;
	contact *ret = NULL;
	cgc_put("First: ");
	cgc_recvUntil(first, 32, '\n');
	cgc_put("Last: ");
	cgc_recvUntil(last, 32, '\n');

	ptr = cgc_head;
	while(ptr != NULL) {
		if(cgc_strcmp(first, ptr->first) == 0) {
			if(cgc_strcmp(last, ptr->last) == 0) {
				ret = ptr;
				break;
			}
		}
		ptr = ptr->next;
	}
	return ret;
}

void cgc_promptDel() {
	contact *ptr;

	ptr = cgc_findContact();
	if(ptr != NULL) {
		ptr = cgc_remove(ptr);
		cgc_free(ptr);
		cgc_puts("Contact removed.");
	} else {
		cgc_puts("No such contact found.");
	}
}

void cgc_editUser(contact *ptr) {
	char data[32];
	char number[8];

	if(ptr != NULL) {
		cgc_puts("Updating fields.  Send just a newline to keep old data.");
		cgc_put("New first name: ");
		cgc_recvUntil(data, 32, '\n');
		if(data[0] && cgc_validateName(data) == 0){
			cgc_puts("Not a legal first name.  Stopping edit.");
			return;
		}
#ifdef PATCHED
		data[31] = 0;
#endif
		if(data[0] != 0) {
			cgc_memset(ptr->first, 0, 32);
			cgc_memcpy(ptr->first, data, cgc_strlen(data));
		}
		cgc_put("New last name: ");
		cgc_recvUntil(data, 32, '\n');
#ifdef PATCHED
		data[31] = 0;
#endif

		if(data[0] && cgc_validateName(data) == 0) {
			cgc_puts("Not a legal last name.  Stopping edit.");
			return;
		}
		if(data[0] != 0){
			cgc_memset(ptr->last, 0, 32);
			cgc_memcpy(ptr->last, data, cgc_strlen(data));
		}
		cgc_put("New phone number: ");
		cgc_recvUntil(data, 14, '\n');
#ifdef PATCHED
		data[13] = 0;
#endif
		if(data[0] && cgc_validatePhone(data) == 0) {
			cgc_puts("Not a legal phone number.  Stopping edit.");
			return;
		}
		if(data[0] != 0) {
			cgc_memset(ptr->phone, 0, 16);
			cgc_memcpy(ptr->phone, data, cgc_strlen(data));
		}
		cgc_put("New office number: ");
		cgc_recvUntil(data, 6, '\n');
		if(data[0]) {
			cgc_memcpy(number, data, 5);
			ptr->officenum = cgc_atoi(number);
		}
		cgc_put("New gender: ");
		cgc_recvUntil(data, 2, '\n');
		if(data[0])
			ptr->gender = data[0];
		cgc_put("Is the user a hacker? ");
		cgc_recvUntil(data, 2, '\n');
		if(data[0])
			ptr->hacker = data[0];
	}
	if(ptr->cookie != cgc_cookie)
	{
		cgc_puts("Contact corruption detected.");
		cgc__terminate(-1);
	}

}

void cgc_promptEdit() {
	contact *ptr;
	char data[32];
	char number[8];

	cgc_memset(number, 0, 8);
	ptr = cgc_findContact();
	if(ptr == NULL) {
		cgc_puts("No such contact.");
		return;
	}
	cgc_editUser(ptr);
}

void cgc_promptShow() {
	contact *ptr;
	char office[8];
	char useraction[2];

	ptr = cgc_findContact();
	if(ptr == NULL) {
		cgc_puts("No such contact.");
		return;
	}
	cgc_memset(useraction, 0, 2);
	useraction[0] = 's';
	while(useraction[0] != 'q') {
		cgc_memset(office, 0, 6);
		cgc_puts("****************************************");
		cgc_put("First name:\t");
		cgc_puts(ptr->first);
		cgc_put("Last name:\t");
		cgc_puts(ptr->last);
		cgc_put("Phone num:\t");
		cgc_puts(ptr->phone);
		cgc_itoa(office, ptr->officenum, 6);
		cgc_put("Office Number:\t");
		cgc_puts(office);
		cgc_put("Gender:\t\t");
		cgc_printGender(ptr->gender);
		if(ptr->hacker == 'y')
		{
			cgc_puts("[\x1B[31m!\x1B[0m]This user known to be a hacker[\x1B[31m!\x1B[0m]");
		}
		cgc_puts("****************************************");
		cgc_recvUntil(useraction, 2, '\n');
		switch(useraction[0]) {
			case 'q':
				break;
			case 'd':
				if(ptr->next == NULL && ptr->prev == NULL) {
					cgc_remove(ptr);
					cgc_puts("No more contacts.  Leaving detail view.");
					useraction[0]='q';
				} else if (ptr->next == NULL) {
					ptr = ptr->prev;
					cgc_remove(ptr->next);
				} else {
					ptr = ptr->next;
					cgc_remove(ptr->prev);
				}
				break;
			case 'e':
				cgc_editUser(ptr);
				break;
			case 'n':
				if(ptr->next != NULL)
					ptr = ptr->next;
				else
					cgc_puts("No next contact.");
				break;
			case 'p':
				if(ptr->prev != NULL)
					ptr = ptr->prev;
				else
					cgc_puts("No previous contact.");
		}
	}
}

void cgc_initCookies() {
	cgc_size_t bytes;
	int got = 0;
	int shift = 0;

	contact *ptr;

	cgc_random(&cgc_cookie, 4, &bytes);
	if(bytes != 4)
	{
		cgc_puts("Couldn't get 4 random bytes.  Panic!");
		cgc__terminate(-1);
	}
	cgc_cookie |= 0x10204080;
}

void cgc_inputLoop() {
	char action[2];
	while(1)
	{
		cgc_memset(action, 0, 2);
		cgc_recvUntil(action, 2, '\n');
		switch(action[0])
		{
			case YOLO_ADD:
				cgc_promptAdd();
				break;
			case YOLO_DEL:
				cgc_promptDel();
				break;
			case YOLO_EDIT:
				cgc_promptEdit();
				break;
			case YOLO_EXIT:
				cgc_puts("Thank you for using the yolodex.");
				cgc__terminate(0);
			case YOLO_LIST:
				cgc_printList();
				break;
			case YOLO_SORT:
				cgc_sortYolodex();
				break;
			case YOLO_SHOW:
				cgc_promptShow();
				break;
			default:
				cgc_puts("Unrecognized Command.");
		}
	}
}

int main(int cgc_argc, char *cgc_argv[])
{
	cgc_initCookies();
	cgc_puts("Welcome to the yolodex.");
	cgc_initYolodex();
	cgc_inputLoop();
	cgc__terminate(0);
}
