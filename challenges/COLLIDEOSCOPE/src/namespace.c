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

#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_namespace.h"

int
cgc_namespace_init(struct namespace *ns, cgc_size_t size)
{
    ns->size = size;
    if ((size * sizeof(struct variable)) / sizeof(struct variable) != size)
        return EXIT_FAILURE;
    return cgc_allocate(size * sizeof(struct variable), 0, (void **)&ns->variables);
}

void
cgc_namespace_destroy(struct namespace *ns)
{
    cgc_deallocate(ns->variables, ns->size * sizeof(struct variable));
    ns->size = 0;
}

static unsigned int
hash(const char *str)
{
    unsigned int i, result = 0;

    for (i = 0; i < 4 && str[i]; i++)
        result = result * 52 + str[i];

    return result;
}

struct variable *
cgc_lookup_variable(struct namespace *ns, const char *name)
{
    cgc_size_t i, b;
    unsigned int h;
    struct variable *var;

    h = hash(name);

    for (i = 0; i < ns->size; i++) {
        b = (h + i * i) % ns->size;
        var = &ns->variables[b];

        if (var->type == VAR_EMPTY)
            return NULL;

        if (cgc_strncmp(var->name, name, 4) == 0)
            return var;
    }

    return NULL;
}

struct variable *
cgc_insert_variable(struct namespace *ns, const char *name, enum variable_type type)
{
    cgc_size_t i, b;
    unsigned int h;
    struct variable *var, *last_var = NULL;

    h = hash(name);

    for (i = 0; i < ns->size; i++) {
        b = (h + i * i) % ns->size;
        var = &ns->variables[b];

        if (var->type == VAR_EMPTY) {
            if (last_var)
                return last_var;

            cgc_memset(var->name, '\0', 4);
            cgc_strncpy(var->name, name, 4);
            var->type = type;
            return var;
        }

#ifdef PATCHED_1
        if (var->type != VAR_EMPTY && cgc_strncmp(var->name, name, 4) == 0) {
#else
        if (var->type == type && cgc_strncmp(var->name, name, 4) == 0) {
#endif 
            last_var = var;
        }
    }

    return NULL;
}

