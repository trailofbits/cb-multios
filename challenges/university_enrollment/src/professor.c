/*
 * Copyright (c) 2015 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#include "cgc_professor.h"
#include "cgc_ptrlist.h"

#include "cgc_string.h"

ptrlist_t *cgc_g_all_profs = NULL;

void cgc_add_professor(professor_t *prof)
{
    if (!prof)
        return;

    if (!cgc_g_all_profs)
        cgc_g_all_profs = cgc_create_ptrlist();

    cgc_add_item(cgc_g_all_profs, prof);
}

professor_t *cgc_create_professor(char *name)
{
    if (!name)
        return NULL;

    professor_t *prof = cgc_malloc(sizeof(professor_t));
    if (!prof)
        return NULL;

    prof->name = cgc_strdup(name);
    prof->courses_taught = cgc_create_ptrlist();
    cgc_add_professor(prof);

    return prof;
}

void cgc_add_course_to_professor(professor_t *prof, course_t *course)
{
    if (!prof || !course)
        return;

    cgc_add_item(prof->courses_taught, course);
}

professor_t *cgc_get_professor(char *name)
{
    if (!name || !cgc_g_all_profs)
        return NULL;

    int i = 0;
    professor_t *iter;
    for (i = 0; i < cgc_g_all_profs->length; i++) {
        iter = get_item(professor_t, cgc_g_all_profs, i);
        if (cgc_strcasecmp(iter->name, name) == 0)
            return iter;
    }

    return NULL;
}

course_t *cgc_get_professor_class(professor_t *prof, cgc_size_t idx)
{
    if (!prof)
        return NULL;

    return get_item(course_t, prof->courses_taught, idx);
}

void cgc_list_professors()
{
    if (!cgc_g_all_profs)
        return;

    int i = 0;
    professor_t *iter;
    cgc_printf("--All Professors--\n");
    for (i = 0; i < cgc_g_all_profs->length; i++) {
        iter = get_item(professor_t, cgc_g_all_profs, i);
        cgc_printf("%s\n", iter->name);
    }
}

void cgc_list_classes_taught(professor_t *prof)
{
    if (!prof)
        return;

    int i = 0;
    course_t *iter;
    cgc_printf("--%s's Classes--\n", prof->name);
    cgc_print_course_banner();
    for (i = 0; i < prof->courses_taught->length; i++) {
        cgc_printf("#%d|", i+1);
        iter = get_item(course_t, prof->courses_taught, i);
        iter->print_course(iter); //brief?
    }
}

