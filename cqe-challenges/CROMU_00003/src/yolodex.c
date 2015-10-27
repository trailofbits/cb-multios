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

#include <libcgc.h>
#include <stdlib.h>

#define YOLO_ADD 0x40
#define YOLO_DEL 0x41
#define YOLO_EDIT 0x42
#define YOLO_SHOW 0x43
#define YOLO_LIST 0x44
#define YOLO_SORT 0x45
#define YOLO_EXIT 0x46

unsigned int cookie = 0;

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

contact *head = NULL;

void cgc_put(char *str) {
	transmit(1, str, cgc_strlen(str), 0);
}

int validateName(char *name)
{
	//let's make it title case.  And lets yell if its not.
	if(name[0] >= 'A' && name[0] <= 'Z')
		return 1;
	else
		return 0;
}

int validatePhone(char *phonenumber)
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

contact *createContact(char *first, char *last, char *phone, unsigned short officenum, char gender, char hacker)
{
	contact *ret = NULL;
	ret = (contact *)cgc_calloc(1, sizeof(contact));
	if(ret == NULL)
	{
		cgc_puts("Couldn't allocate contact.  Something's wrong.");
		_terminate(-1);
	}
	if(validateName(first)) {
		cgc_memcpy(ret->first, first, cgc_strlen(first));
	} else {
		cgc_puts("Invalid first name.  Must begin with a capital letter.");
		cgc_free(ret);
		ret = NULL;
		return NULL;
	}
	if(validateName(last)) {
		cgc_memcpy(ret->last, last, cgc_strlen(last));
	} else {
		cgc_puts("Invalid last name.  Must begin with a capital letter.");
		cgc_free(ret);
		ret = NULL;
		return NULL;
	}
	if(validatePhone(phone)) {
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
	ret->cookie = cookie;
	ret->pad = 0;
	ret->next = NULL;
	ret->prev = NULL;
	return ret;
}

void insert(contact *toAdd)
{
	contact *tmp;
	if(head == NULL) {
		head = toAdd;
		return;
	}
	tmp = head;
	while(tmp->next != NULL) {
		tmp = tmp->next;
	}
	tmp->next = toAdd;
	toAdd->prev = tmp;
}

contact *remove(contact *toRemove)
{
	if((toRemove->next == NULL) && (toRemove->prev == NULL)) {
		head = NULL;
		return toRemove;
	}

	if(toRemove->prev == NULL) {
		head = toRemove->next;
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

void printGender(char gender)
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

void printContact(contact *toPrint)
{
	cgc_put("First Name: \t");
	cgc_puts(toPrint->first);
	cgc_put("Last Name: \t");
	cgc_puts(toPrint->last);
	cgc_put("Phone Number: \t");
	cgc_puts(toPrint->phone);
}

void printList() {
	contact *ptr;
	ptr = head;
	if(head == NULL)
		cgc_puts("Empty yolodex.");
	while(ptr != NULL)
	{
		cgc_puts("========================================");
		printContact(ptr);
		ptr = ptr->next;
	}
	cgc_puts("========================================");
}

void sortYolodex() {
	contact *ptr;
	contact *tmp;
	contact *first;
	contact *other;
	contact *sorted = NULL;
	int i;

	ptr = head;
	first = head;
	tmp = head;

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
		tmp = remove(first);
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
	first = head;
	ptr = head;
	tmp = head;
	}
	head = sorted;
}

void initYolodex() {
	head = createContact("Robert", "Morris", "(617)253-5982", 32972, 'M', 'y');
	insert(createContact("Chareth", "Cutestory", "(123)456-7890", 4242, 'M', 'n'));
	insert(createContact("Tim", "Berners-Lee", "(638)844-2074", 404, 'M','y'));
	insert(createContact("Pwnies", "McPwn", "(222)223-1337", 31337, 'F','y'));
	insert(createContact("Jenny", "Fakename", "(555)867-5309", 31337, 'F','n'));
}

int recvUntil(char *dst, int n, char delim)
{
	char *tmp;
	size_t gotBytes;
	tmp = dst;
	while(n--)
	{
		receive(STDIN, tmp, 1, &gotBytes);
		if(gotBytes == 0) {
			_terminate(-1);
		}
		if(*tmp == delim) {
			*tmp = 0;
			break;
		}
		tmp++;
	}
	return tmp-dst;
}

void promptAdd() {
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
		recvUntil(first, 32, '\n');
		cgc_put("Last: ");
		recvUntil(last, 32, '\n');
		cgc_put("Phone Number: ");
		recvUntil(phone, 14, '\n');
		cgc_put("Office Number: ");
		cgc_memset(officetmp, 0, 8);
		recvUntil(officetmp, 6, '\n');
		officenum = (unsigned short)atoi(officetmp);
		cgc_put("Gender: ");
		recvUntil(tmp, 2, '\n');
		gender = tmp[0];
		hacker = '?';
		while(hacker == '?')
		{
			cgc_put("Hacker: ");
			recvUntil(tmp, 2, '\n');
			if(tmp[0] == 'n' || tmp[0] == 'y')
				hacker = tmp[0];
			else
				cgc_puts("Please enter y or n for hacker.");
		}
		ptr = createContact(first, last, phone, officenum, gender, hacker);
	}
	if(ptr->cookie != cookie)
	{
		cgc_puts("Contact corruption detected.");
		_terminate(-1);
	}
	insert(ptr);
}

contact *findContact() {
	char first[32];
	char last[32];
	contact *ptr;
	contact *ret = NULL;
	cgc_put("First: ");
	recvUntil(first, 32, '\n');
	cgc_put("Last: ");
	recvUntil(last, 32, '\n');

	ptr = head;
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

void promptDel() {
	contact *ptr;

	ptr = findContact();
	if(ptr != NULL) {
		ptr = remove(ptr);
		cgc_free(ptr);
		cgc_puts("Contact removed.");
	} else {
		cgc_puts("No such contact found.");
	}
}

void editUser(contact *ptr) {
	char data[32];
	char number[8];

	if(ptr != NULL) {
		cgc_puts("Updating fields.  Send just a newline to keep old data.");
		cgc_put("New first name: ");
		recvUntil(data, 32, '\n');
		if(data[0] && validateName(data) == 0){
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
		recvUntil(data, 32, '\n');
#ifdef PATCHED
		data[31] = 0;
#endif

		if(data[0] && validateName(data) == 0) {
			cgc_puts("Not a legal last name.  Stopping edit.");
			return;
		}
		if(data[0] != 0){
			cgc_memset(ptr->last, 0, 32);
			cgc_memcpy(ptr->last, data, cgc_strlen(data));
		}
		cgc_put("New phone number: ");
		recvUntil(data, 14, '\n');
#ifdef PATCHED
		data[13] = 0;
#endif
		if(data[0] && validatePhone(data) == 0) {
			cgc_puts("Not a legal phone number.  Stopping edit.");
			return;
		}
		if(data[0] != 0) {
			cgc_memset(ptr->phone, 0, 16);
			cgc_memcpy(ptr->phone, data, cgc_strlen(data));
		}
		cgc_put("New office number: ");
		recvUntil(data, 6, '\n');
		if(data[0]) {
			cgc_memcpy(number, data, 5);
			ptr->officenum = atoi(number);
		}
		cgc_put("New gender: ");
		recvUntil(data, 2, '\n');
		if(data[0])
			ptr->gender = data[0];
		cgc_put("Is the user a hacker? ");
		recvUntil(data, 2, '\n');
		if(data[0])
			ptr->hacker = data[0];
	}
	if(ptr->cookie != cookie)
	{
		cgc_puts("Contact corruption detected.");
		_terminate(-1);
	}

}

void promptEdit() {
	contact *ptr;
	char data[32];
	char number[8];

	cgc_memset(number, 0, 8);
	ptr = findContact();
	if(ptr == NULL) {
		cgc_puts("No such contact.");
		return;
	}
	editUser(ptr);
}

void promptShow() {
	contact *ptr;
	char office[8];
	char useraction[2];

	ptr = findContact();
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
		printGender(ptr->gender);
		if(ptr->hacker == 'y')
		{
			cgc_puts("[\x1B[31m!\x1B[0m]This user known to be a hacker[\x1B[31m!\x1B[0m]");
		}
		cgc_puts("****************************************");
		recvUntil(useraction, 2, '\n');
		switch(useraction[0]) {
			case 'q':
				break;
			case 'd':
				if(ptr->next == NULL && ptr->prev == NULL) {
					remove(ptr);
					cgc_puts("No more contacts.  Leaving detail view.");
					useraction[0]='q';
				} else if (ptr->next == NULL) {
					ptr = ptr->prev;
					remove(ptr->next);
				} else {
					ptr = ptr->next;
					remove(ptr->prev);
				}
				break;
			case 'e':
				editUser(ptr);
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

void initCookies() {
	size_t bytes;
	int got = 0;
	int shift = 0;

	contact *ptr;

	cgc_random(&cookie, 4, &bytes);
	if(bytes != 4)
	{
		cgc_puts("Couldn't get 4 random bytes.  Panic!");
		_terminate(-1);
	}
	cookie |= 0x10204080;
}

void inputLoop() {
	char action[2];
	while(1)
	{
		cgc_memset(action, 0, 2);
		recvUntil(action, 2, '\n');
		switch(action[0])
		{
			case YOLO_ADD:
				promptAdd();
				break;
			case YOLO_DEL:
				promptDel();
				break;
			case YOLO_EDIT:
				promptEdit();
				break;
			case YOLO_EXIT:
				cgc_puts("Thank you for using the yolodex.");
				_terminate(0);
			case YOLO_LIST:
				printList();
				break;
			case YOLO_SORT:
				sortYolodex();
				break;
			case YOLO_SHOW:
				promptShow();
				break;
			default:
				cgc_puts("Unrecognized Command.");
		}
	}
}

int main(void)
{
	initCookies();
	cgc_puts("Welcome to the yolodex.");
	initYolodex();
	inputLoop();
	_terminate(0);
}
