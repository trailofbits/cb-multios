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

#ifndef NAMESPACE_H_
#define NAMESPACE_H_

#include <libcgc.h>

enum variable_type {
    VAR_EMPTY,
    VAR_INTEGER,
    VAR_POINTER
};

struct variable {
    char name[4];
    enum variable_type type;
    union {
        int i;
        void *p;
    } val;
};

struct namespace {
    size_t size;
    struct variable *variables;
};

/**
 * Initialize a namespace.
 *
 * @param ns The namespace to initialize
 * @param size The size of the namespace
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int namespace_init(struct namespace *ns, size_t size);

/**
 * Destroy a namespace.
 *
 * @param ns The namespace to destroy
 */
void namespace_destroy(struct namespace *ns);

/**
 * Lookup a variable in a namespace.
 *
 * @param ns The namespace to access
 * @param name The name of the variable
 * @return A pointer to the variable with the given name, or NULL on failure
 */
struct variable *lookup_variable(struct namespace *ns, const char *name);

/**
 * Insert a variable in a namespace.
 *
 * @param ns The namespace to access
 * @param name The name of the variable
 * @param type The type of the variable
 * @return A pointer to the variable, or NULL on failure
 */
struct variable *insert_variable(struct namespace *ns, const char *name,
        enum variable_type type);

#endif /* NAMESPACE_H_ */

