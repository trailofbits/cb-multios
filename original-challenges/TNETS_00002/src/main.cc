
/*
 * Copyright (c) 2014 Jason L. Wright (jason@thought.net)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * virtual pet service... complete with heap buffer over flow into vtables!
 * yea!
 */

extern "C" {
#include <libcgc.h>
#include "cgc_libc.h"
#include "cgc_malloc.h"
};

#undef NULL
#define NULL (0L)

void put(char);
void put(const char *s);
void put(void *v);
void put(int v);
void put(long v);

void call_inits(void);
void terminate(int) __attribute__((__noreturn__));

int first = 1;
int seq;

class Pet {
protected:
	char name[200];

public:
	Pet() { name[0] = '\0'; transmit_all(1, "init..\n", 7); }
	virtual ~Pet() = 0;

	virtual void Rollover() = 0;
	virtual void Speak() = 0;
	virtual void Flush() = 0;

	void Debug();
	void Name(const char *s) {
#ifdef PATCHED
		if (strlen(s) < sizeof(name))
			strlcat(name, s, sizeof(name));
#else
		if (strlen(s) < sizeof(name)) {
			char *n = name + strlen(name);
			memcpy(n, s, strlen(s) + 1);
		}
#endif
	}
};

template <typename T>
class listnode {
private:
	listnode<T> *nxt;
	T datax;

public:
	listnode<T> *next() { return nxt; }
	void next(listnode<T> *p) { nxt = p; }
	listnode(T d, listnode<T> *p) { datax = d; nxt = p; }
	listnode(T d) { datax = d; nxt = NULL; }
	T data() { return datax; }
};

class petlist {
	listnode<Pet *> *head;
	int n;

public:
	petlist() { head = NULL; n = 0; put("list init...\n"); }
	~petlist();

	void append(Pet *);
	void remove(int n);
	Pet *nth(int n);
	int len() { return n; }
} myList;

Pet::~Pet() {
}

void
Pet::Debug() {
	put((void *)this);
	put(' ');
	put((int)sizeof(Pet));
	put("\n");
}

class Cat: public Pet {
public:
	~Cat() {};
	virtual void Rollover();
	virtual void Speak();
	virtual void Flush();
};

class Dog: public Pet {
public:
	~Dog() {}
	virtual void Rollover();
	virtual void Speak();
	virtual void Flush();
};

class Hotdog: public Dog {
public:
	~Hotdog() { };
	virtual void Rollover();
	virtual void Speak();
	virtual void Flush();
};

void
Cat::Rollover() {
	put(name);
	put(" will not roll over\n");
	
}

void
Cat::Speak() {
	put(name);
	put(" meows\n");
}

void
Cat::Flush() {
	put(name);
	put(" purrs takes a nap\n");
}

void
Dog::Rollover() {
	put(name);
	put(" rolls over\n");
	
}

void
Dog::Speak() {
	put(name);
	put(" barks\n");
}

void
Dog::Flush() {
	put(name);
	put(" goes to sleep... permanently\n");
}

void
Hotdog::Rollover() {
	put(name);
	put(" rolls over on the grill\n");
	
}

void
Hotdog::Speak() {
	put(name);
	put(" can't speak\n");
}

void
Hotdog::Flush() {
	put(name);
	put(" tastes great with ketchup and mustard\n");
}

petlist::~petlist() {
	while (head) {
		listnode<Pet *> *p = head;
		head = head->next();
		delete p->data();
		delete p;
	}
}

void
petlist::append(Pet *pet) {
	if (n == 100) {
		put("too many pets already... put one to sleep\n");
		return;
	}

	n++;

	listnode<Pet *> *p = new listnode<Pet *>(pet);
	if (head == NULL)
		head = p;
	else {
		listnode<Pet *> *q;

		for (q = head; q->next(); q = q->next())
			/* empty */;
		q->next(p);
	}
}

Pet *
petlist::nth(int x) {
	listnode<Pet *>*p = head;

	if (n == 0) {
		put("you don't have any pets\n");
		return (NULL);
	}
	if (x < 0) {
		put("no imaginary pets allowed\n");
		return (NULL);
	}

	for (int i = 0; i < x; p = p->next(), i++)
		/* empty */;
	return p->data();
}

void
petlist::remove(int nth) {
	listnode<Pet *> *prev = NULL, *p;
	int i;

	if (n == 0) {
		put("you don't have any pets\n");
		return;
	}

	if (n < 0) {
		put("no imaginary pets allowed\n");
		return;
	}

	if (nth >= n) {
		put("you don't have that many pets\n");
		return;
	}

	for (i = 0, p = head; i < nth; i++, p = p->next())
		prev = p;

	n--;

	if (prev == NULL) {
		p = head;
		head = head->next();
		p->data()->Flush();
		delete p->data();
		delete p;
		return;
	}

	p->data()->Flush();
	delete p->data();
	prev->next(p->next());
	delete p;
}

void
do_rollover(const char *cmd, const char *opt) {
	for (int i = 0; i < myList.len(); i++)
		myList.nth(i)->Rollover();
}

void
do_speak(const char *cmd, const char *opt) {
	for (int i = 0; i < myList.len(); i++)
		myList.nth(i)->Speak();
}

void
do_create(const char *cmd, const char *opt) {
	Pet *p;

	if (!opt) {
		put("missing option\n");
		return;
	}

	if (!strcmp(opt, "hotdog"))
		p = new Hotdog();
	else if (!strcmp(opt, "cat"))
		p = new Cat();
	else if (!strcmp(opt, "dog"))
		p = new Dog();
	else {
		put("unknown pet\n");
		return;
	}

	myList.append(p);
}

void
do_name(const char *cmd, const char *opt) {
	int n = 0, i;
	const char *name;

	if (!opt) {
		printf("missing option\n");
		return;
	}

	if (opt[0] < '0' || opt[0] > '9') {
bad_num:
		put("bad number\n");
		return;
	}

	for (i = 0; opt[i]; i++) {
		if (opt[i] >= '0' && opt[i] <= '9')
			n = (n * 10) + opt[i] - '0';
		else if (opt[i] == ' ')
			break;
		else
			goto bad_num;
	}

	name = &opt[i + 1];
	if (opt[i] == '\0' || strlen(name) == 0) {
		put("missing name\n");
		return;
	}

	if (n >= myList.len()) {
		put("you don't have that many pets\n");
		return;
	}

	Pet *p = myList.nth(n);
	if (p == NULL)
		return;
	p->Name(name);
}

void
do_debug(const char *cmd, const char *opt) {
	for (int i = 0; i < myList.len(); i++)
		myList.nth(i)->Debug();
}

void
do_delete(const char *cmd, const char *opt) {
	int n = 0;

	if (!opt) {
		printf("missing option\n");
		return;
	}

	if (opt[0] < '0' || opt[0] > '9')
		goto bad_number;
	for (int i = 0; opt[i]; i++) {
		if (opt[i] >= '0' && opt[i] <= '9')
			n = n * 10 + opt[i] - '0';
		else
			goto bad_number;
	}

	myList.remove(n);

	return;

bad_number:
	put("bad number\n");
}

int
get_number(const char *str) {
	int n = 0, neg = 0;

	if (str[0] == '-') {
		neg = 1;
		str++;
	}
	if (str[0] < '0' || str[0] > '9')
		goto bad;

	n = str[0] - '0';
	for (str++; *str; str++) {
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str) - '0';
		else
			goto bad;
	}
	if (neg)
		n = -n;

	if (first) {
		seq = n;
		first = 0;
	} else {
		if (n != seq + 1)
			goto bad;
		seq = n;
	}

	return (0);

bad:
	put("bad sequence\n");
	return (-1);
}

void
do_line(char *line) {
	const char *number = NULL;
	const char *cmd = NULL;
	const char *opt = NULL;
	int nextiscmd = 0, nextisopt = 0, len = strlen(line);

	number = line;
	for (int i = 0; i < len; i++) {
		if ((nextiscmd || nextisopt) && line[i] == '\0')
			continue;
		if (nextiscmd) {
			if (line[i] == ' ')
				continue;
			cmd = &line[i];
			nextiscmd = 0;
		}

		if (nextisopt) {
			if (line[i] == ' ')
				continue;
			opt = &line[i];
			nextisopt = 0;
			break;
		}

		if (line[i] == ' ') {
			if (cmd == NULL) {
				line[i] = '\0';
				nextiscmd = 1;
				continue;
			}
			if (opt == NULL) {
				line[i] = '\0';
				nextisopt = 1;
			}
		}
	}

	if (!cmd) {
		printf("no command?\n");
		return;
	}

	if (get_number(number))
		return;

	if (!strcmp(cmd, "create"))
		do_create(cmd, opt);
	else if (!strcmp(cmd, "delete"))
		do_delete(cmd, opt);
	else if (!strcmp(cmd, "speak"))
		do_speak(cmd, opt);
	else if (!strcmp(cmd, "rollover"))
		do_rollover(cmd, opt);
	else if (!strcmp(cmd, "debug"))
		do_debug(cmd, opt);
	else if (!strcmp(cmd, "name"))
		do_name(cmd, opt);
	else {
		put("invalid cmd\n");
	}
}

int
main() {
	char buf[1024], c;
	int nbuf = 0;
	size_t nr;

	call_inits();

	for (;;) {
		if (receive(0, &c, 1, &nr))
			break;
		if (nr != 1)
			break;
		if (c == '\n') {
			buf[nbuf] = '\0';
			do_line(buf);
			memset(buf, 0, sizeof(buf));
			nbuf = 0;
		} else
			buf[nbuf++] = c;
		if (nbuf == sizeof(buf)) {
			put("you talk too much.\n");
			break;
		}
	}

	terminate(0);
}



static char hex[] = "0123456789abcdef";

void
put(char c) {
	transmit_all(1, &c, 1);
}

void
put(const char *s) {
	transmit_str(1, s);
}

void
put(void *v) {
	put((long)v);
}

void
put(int v) {
	put((long)v);
}

void
put(long v) {
	int i;

	for (i = 28; i >= 0; i -= 4)
		put(hex[(v >> i) & 0xf]);
}
