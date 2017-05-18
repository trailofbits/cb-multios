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
#include "cgc_util.h"
#include "cgc_malloc.h"
#include "cgc_strtok.h"
#include "cgc_atoi.h"
#include "cgc_memcpy.h"
#include "cgc_cbstdio.h"
#include "cgc_strncmp.h"
#include "cgc_comms.h"
#include "libcgc.h"

Attribute* attributes;

/**
* Zeroize and deallocate all memory used for attributes
*
* @return None
*/
void cgc_clearAttributes() {
	Attribute* attr_ptr;
	void* next_attr;
	for(attr_ptr=attributes; attr_ptr != NULL; attr_ptr = next_attr) {
		next_attr = attr_ptr->next;
		attr_ptr->value = 0;
		attr_ptr->key = 0;
		attr_ptr->next = 0;
		cgc_free(attr_ptr);
	}
	attributes = NULL;
}

/**
* Parse the body of the requesting message and create key/value 
* pairs for each attribute
* 
* @param body The body of the requesting message containing the attributes
*
* @return None
*/
void cgc_initializeAttributes(char* body) {
	char *key, *value;
	Attribute *new_attr;
	cgc_size_t size;

	cgc_clearAttributes();

	key = cgc_strtok(body, "=");
	do {
		value = cgc_strtok(0, ";");
		if(!(new_attr = cgc_malloc(sizeof(Attribute))))
			cgc__terminate(1);
		cgc_bzero((char *)new_attr, sizeof(Attribute));
		size = cgc_strlen(key);
		if(!(new_attr->key = cgc_malloc(size+1)))
			cgc__terminate(1);
		cgc_bzero(new_attr->key, size+1);
		cgc_memcpy(new_attr->key, key, size);
		size = cgc_strlen(value);
		if(!(new_attr->value = cgc_malloc(size+1)))
			cgc__terminate(1);
		cgc_bzero(new_attr->value, size+1);
		cgc_memcpy(new_attr->value, value, size);
		new_attr->next = attributes;
		attributes = new_attr;
	} while((key = cgc_strtok(0, "=")));
}

/**
* Send an error response message to requestor
* 
* @param response The response message to send
*
* @return None
*/
void cgc_sendErrorResponse(const char* response) {
	char* buffer;
	cgc_size_t bytes;
	int ret;

	if(!(buffer = cgc_malloc(sizeof(RESPONSE_HDR)+cgc_strlen(response)+1)))
		cgc__terminate(1);

	cgc_bzero(buffer, sizeof(RESPONSE_HDR)+cgc_strlen(response)+1);
	cgc_sprintf(buffer, "!X=!X?", RESPONSE_HDR, response);
	if((ret = cgc_transmit_all(STDOUT, buffer, cgc_strlen(buffer)))) 
		cgc__terminate(1);

	cgc_free(buffer);
}

/**
* Store the value of the string attribute with name into buffer_ptr
* 
* @param buffer_prt The buffer to store the value
* @param name The name of the attribute 
*
* @return None
*/
void cgc_getStringAttribute(char** buffer_ptr, const char* name) {
	Attribute* attr_ptr;
	cgc_size_t size, size1, size2;

	for(attr_ptr=attributes; attr_ptr != NULL; attr_ptr = attr_ptr->next) {
		size1 = cgc_strlen(attr_ptr->key);
		size2 = cgc_strlen(name);
		size = size1 > size2 ? size1 : size2;
		if(!cgc_strncmp(attr_ptr->key, name, size)) {
			*buffer_ptr = attr_ptr->value;
			return;
		}
	}

	return;
}

/**
* Store the value of the integer attribute with name into buffer_ptr
* 
* @param buffer_prt The buffer to store the value
* @param name The name of the attribute 
*
* @return None
*/
void cgc_getIntegerAttribute(unsigned int* int_ptr, const char* name) {
	char* buffer=NULL;

	cgc_getStringAttribute((char **) &buffer, name);
	if(buffer)
		*int_ptr = cgc_atoi(buffer);
	else
		*int_ptr = 0;

}
