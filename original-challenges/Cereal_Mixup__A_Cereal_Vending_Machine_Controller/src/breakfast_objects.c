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

#include <libcgc.h>
#include <stdint.h>
#include "libc.h"
#include "char.h"
#include "strlen.h"
#include "memcpy.h"


#include "breakfast_objects.h"

const char *typeName[] = {"Liquids", "Cereals", "Toppings", "GenericString",
							"PrinterString", "CommandRunner"};

// Serialized content, SVU as UINT32, STI as UINT32, and name as series of chars.

/**
 * Set values in a Liquids object
 *
 * @param g 				Liquids object (this)
 * @param serialVersionUID 	UID of this serialized type
 * @param subTypeID			subTypeID number
 * @return 0 on SUCCESS
 */
int set_data_liquids(Liquids *l, svu_t serialVersionUID, l_sti_t subTypeID) {
	l->serialVersionUID = serialVersionUID;
	memcpy(l->typeName, typeName[LIQUID], strlen(typeName[LIQUID]));
	l->subTypeID = subTypeID;
	return 0;
}

/**
 * Destroy a Liquids object
 *
 * @param l 	Liquids object (this)
 */
void destructor_liquids(Liquids *l) {
	free(l);
}

Liquids *constructor_liquids(void) {

	Liquids *l = malloc(sizeof(Liquids));
	MALLOC_OK(l);
	l->set_data = &set_data_liquids;
	l->destroy = &destructor_liquids;
	return l;
}

/**
 * Set values in a Cereals object
 *
 * @param g 				Cereals object (this)
 * @param serialVersionUID 	UID of this serialized type
 * @param subTypeID			subTypeID number
 * @return 0 on SUCCESS
 */
int set_data_cereals(Cereals *c, svu_t serialVersionUID, c_sti_t subTypeID) {
	c->serialVersionUID = serialVersionUID;
	memcpy(c->typeName, typeName[CEREAL], strlen(typeName[CEREAL]));
	c->subTypeID = subTypeID;
	return 0;
}

/**
 * Destroy a Cereals object
 *
 * @param c 	Cereals object (this)
 */
void destructor_cereals(Cereals *c) {
	free(c);
}

Cereals *constructor_cereals(void) {

	Cereals *c = malloc(sizeof(Cereals));
	MALLOC_OK(c);
	c->set_data = &set_data_cereals;
	c->destroy = &destructor_cereals;
	return c;
}

/**
 * Set values in a Toppings object
 *
 * @param g 				Toppings object (this)
 * @param serialVersionUID 	UID of this serialized type
 * @param subTypeID			subTypeID number
 * @return 0 on SUCCESS
 */
int set_data_toppings(Toppings *t, svu_t serialVersionUID, t_sti_t subTypeID) {
	t->serialVersionUID = serialVersionUID;
	memcpy(t->typeName, typeName[TOPPINGS], strlen(typeName[TOPPINGS]));
	t->subTypeID = subTypeID;
	return 0;
}

/**
 * Destroy a Toppings object
 *
 * @param t 	Toppings object (this)
 */
void destructor_toppings(Toppings *t) {
	free(t);
}

Toppings *constructor_toppings(void) {

	Toppings *t = malloc(sizeof(Toppings));
	MALLOC_OK(t);
	t->set_data = &set_data_toppings;
	t->destroy = &destructor_toppings;
	return t;
}

/**
 * Set values in a GenericString object
 *
 * @param g 				GenericString object (this)
 * @param serialVersionUID 	UID of this serialized type
 * @param str 				String to load into object
 * @return 0 on SUCCESS
 */
int set_data_generic_string(GenericString *g, svu_t serialVersionUID, char *str) {
	unsigned int s_len = strlen(str);
	g->serialVersionUID = serialVersionUID;
	memcpy(g->typeName, typeName[GENERIC_STRING], strlen(typeName[GENERIC_STRING]));
	// no protection against very very long strings
	g->str = malloc(s_len);
	MALLOC_OK(g->str);
	// no requirements on str content (except NULL is the terminator)
	memcpy(g->str, str, s_len);
	return 0;
}

/**
 * Destroy a GenericString object
 *
 * @param g 	GenericString object (this)
 */
void destructor_generic_string(GenericString *g) {
	if (NULL != g->str)
		free(g->str);
	free(g);
}

/**
 * Construct an empty GenericString object
 *
 * @return VA of object
 */
GenericString *constructor_generic_string(void) {
	GenericString *g = calloc(sizeof(GenericString));
	MALLOC_OK(g);
	g->set_data = &set_data_generic_string;
	g->destroy = &destructor_generic_string;
	return g;
}

/**
 * Set values in a PrinterString object (printable ASCII chars)
 *
 * @param p 				PrinterString object (this)
 * @param serialVersionUID 	UID of this serialized type
 * @param str 				String to load into object
 * @return 0 on SUCCESS, else -1 on error
 */
int set_data_printer_string(PrinterString *p, svu_t serialVersionUID, char *str) {
	unsigned int s_len = strlen(str);
	p->serialVersionUID = serialVersionUID;
	memcpy(p->typeName, typeName[PRINTER_STRING], strlen(typeName[PRINTER_STRING]));

	for (unsigned int i = 0; i < s_len; i++) {
		if (FALSE == is_printable((unsigned char)str[i])) {
			return -1;
		}
	}

	p->str = malloc(s_len);
	MALLOC_OK(p->str);
	memcpy(p->str, str, s_len);

	return 0;
}

/**
 * Destroy a PrinterString object
 *
 * @param p 	PrinterString object (this)
 */
void destructor_printer_string(PrinterString *p) {
	if (NULL != p->str)
		free(p->str);
	free(p);
}

/**
 * Construct an empty PrinterString object
 *
 * @return VA of object
 */
PrinterString *constructor_printer_string(void) {
	PrinterString *p = calloc(sizeof(PrinterString));
	MALLOC_OK(p);
	p->set_data = &set_data_printer_string;
	p->destroy = &destructor_printer_string;
	return p;
}

/**
 * Fucntion to execute a given command with the given args.
 *
 * @param fn 		Function to be executed
 * @param arg1 		First arg to fn
 * @param arg2 		Second arg to fn
 * @param arg3 		Third arg to fn
 * @return 0
 */
int os_exec(run_fn fn, int arg1, int arg2, int arg3) {
	fn(arg1, arg2, arg3);
	return 0;
}

/**
 * Set values in a CommandRunner object
 *
 * @param c 				CommandRunner object (this)
 * @param serialVersionUID 	UID of this serialized type
 * @param argc 				Number of args in argv + 1 for program
 * @param argv 				Buffer with arguments
 * @return 0 on SUCCESS, else -1 on error
 */
int set_data_command_runner(CommandRunner *c, svu_t serialVersionUID, unsigned short argc, char *argv) {
	c->serialVersionUID = serialVersionUID;
	memcpy(c->typeName, typeName[COMMAND_RUNNER], strlen(typeName[COMMAND_RUNNER]));

	int args[3] = {0};

	// hacky argv tokenizer
	char *c_p_argv;

	c->argc = argc;
	if ((argc < 2) || (4 < argc)) return -1; // need fn name and 1 arg (can have up to 3 args)

	c_p_argv = argv;
	c->fn = *(void **)c_p_argv; // first 4 bytes of argv is fn addr (fn ptr)

	unsigned int idx = 0;
	while (idx < (argc - 1)) { // argv -> int space int [space int]... NULL
		c_p_argv = c_p_argv + sizeof(int) + sizeof(char);
		c->argv[idx++] = *(int *)c_p_argv;
	}

	// run command with given args
	os_exec(c->fn, c->argv[0], c->argv[1], c->argv[2]);

	return 0;
}

/**
 * Destroy a CommandRunner object
 *
 * @param c 	CommandRunner object (this)
 */
void destructor_command_runner(CommandRunner *c) {
	free(c);
}

/**
 * Construct an empty CommandRunner object
 *
 * @return VA of object
 */
CommandRunner *constructor_command_runner(void) {
	CommandRunner *c = calloc(sizeof(CommandRunner));
	MALLOC_OK(c);
	c->set_data = &set_data_command_runner;
	c->destroy = &destructor_command_runner;
	return c;
}

Liquids *deserialize_liquids(char **in) {
	svu_t *p_svu;
	l_sti_t *p_l_sti;
	int ret;

	p_svu = (svu_t *)*in;
	*in += sizeof(svu_t);
	*in += strlen(typeName[LIQUID]);
	p_l_sti = (l_sti_t *)*in;
	*in += sizeof(l_sti_t);

	Liquids *p_liquids = constructor_liquids();
	ret = p_liquids->set_data(p_liquids, *p_svu, *p_l_sti);
	if (0 > ret) {
		p_liquids->destroy(p_liquids);
		p_liquids = NULL;
	}
	return p_liquids;
}

Cereals *deserialize_cereals(char **in) {
	svu_t *p_svu;
	c_sti_t *p_c_sti;
	int ret;

	p_svu = (svu_t *)*in;
	*in += sizeof(svu_t);
	*in += strlen(typeName[CEREAL]);
	p_c_sti = (c_sti_t *)*in;
	*in += sizeof(c_sti_t);

	Cereals *p_cereals = constructor_cereals();
	ret = p_cereals->set_data(p_cereals, *p_svu, *p_c_sti);
	if (0 > ret) {
		p_cereals->destroy(p_cereals);
		p_cereals = NULL;
	}
	return p_cereals;
}

Toppings *deserialize_toppings(char **in) {
	svu_t *p_svu;
	t_sti_t *p_t_sti;
	int ret;

	p_svu = (svu_t *)*in;
	*in += sizeof(svu_t);
	*in += strlen(typeName[TOPPINGS]);
	p_t_sti = (t_sti_t *)*in;
	*in += sizeof(t_sti_t);

	Toppings *p_toppings = constructor_toppings();
	ret = p_toppings->set_data(p_toppings, *p_svu, *p_t_sti);
	if (0 > ret) {
		p_toppings->destroy(p_toppings);
		p_toppings = NULL;
	}
	return p_toppings;
}

/**
 * Deserialize a GenericString object from a given buffer
 *
 * @param in 	Pointer to input buffer
 * @return VA of deserialized object or NULL on error
 */
GenericString *deserialize_generic_string(char **in) {
	svu_t *p_svu;
	char *str;
	int ret;

	p_svu = (svu_t *)*in;
	*in += sizeof(svu_t);
	*in += strlen(typeName[GENERIC_STRING]);
	str = *in;
	*in += strlen(str) + 1; // include count for NULL term

	GenericString *p_generic_string = constructor_generic_string();
	ret = p_generic_string->set_data(p_generic_string, *p_svu, str);
	if (0 > ret) {
		p_generic_string->destroy(p_generic_string);
		p_generic_string = NULL;
	}
	return p_generic_string;
}

/**
 * Deserialize a PrinterString object from a given buffer
 *
 * @param in 	Pointer to input buffer
 * @return VA of deserialized object or NULL on error
 */
PrinterString *deserialize_printer_string(char **in) {
	svu_t *p_svu;
	char *str;
	int ret;

	p_svu = (svu_t *)*in;
	*in += sizeof(svu_t);
	*in += strlen(typeName[PRINTER_STRING]);
	str = *in;
	*in += strlen(str) + 1; // include count for NULL term

	PrinterString *p_printer_string = constructor_printer_string();
	ret = p_printer_string->set_data(p_printer_string, *p_svu, str);
	if (0 > ret) {
		p_printer_string->destroy(p_printer_string);
		p_printer_string = NULL;
	}
	return p_printer_string;
}

/**
 * Deserialize a CommandRunner object from a given buffer
 *
 * @param in 	Pointer to input buffer
 * @return VA of deserialized object or NULL on error
 */
CommandRunner *deserialize_command_runner(char **in) {
	svu_t *p_svu;
	char *argv;
	unsigned short argc; // number of 4 byte values in argv
	int ret;

	p_svu = (svu_t *)*in;
	*in += sizeof(svu_t);
	*in += strlen(typeName[COMMAND_RUNNER]);
	argc = *(unsigned short *)*in;
	if ((argc < 2) || (4 < argc)) return NULL; // need fn name and 1 arg (can have up to 3 args)

	*in += sizeof(unsigned short);
	argv = *in;
	*in += (argc + 1) * (sizeof(unsigned int) + sizeof(char)); // int space int [space int]... NULL

	CommandRunner *p_command_runner = constructor_command_runner();
	ret = p_command_runner->set_data(p_command_runner, *p_svu, argc, argv);
	if (0 > ret) {
		p_command_runner->destroy(p_command_runner);
		p_command_runner = NULL;
	}
	return p_command_runner;
}

ssize_t check_inherited_types(svu_t serialVersionUID, char **cur) {

	// inherited types
	GenericString *p_generic_string;
	PrinterString *p_printer_string;
	CommandRunner *p_command_runner;

	switch(serialVersionUID) {
		case GENERIC_STRING:
			p_generic_string = deserialize_generic_string(cur);
			if (NULL == p_generic_string) return -1;
			p_generic_string->destroy(p_generic_string);
			break;
		case PRINTER_STRING:
			p_printer_string = deserialize_printer_string(cur);
			if (NULL == p_printer_string) return -1;
			p_printer_string->destroy(p_printer_string);
			break;
		case COMMAND_RUNNER:
			p_command_runner = deserialize_command_runner(cur);
			if (NULL == p_command_runner) return -1;
			p_command_runner->destroy(p_command_runner);
			break;
		default:
			return -1;
	}	
	return 0;
}

