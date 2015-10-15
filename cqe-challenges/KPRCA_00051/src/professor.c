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
#include "professor.h"
#include "ptrlist.h"

#include <string.h>

ptrlist_t *g_all_profs = NULL;

void add_professor(professor_t *prof)
{
    if (!prof)
        return;

    if (!g_all_profs)
        g_all_profs = create_ptrlist();

    add_item(g_all_profs, prof);
}

professor_t *create_professor(char *name)
{
    if (!name)
        return NULL;

    professor_t *prof = malloc(sizeof(professor_t));
    if (!prof)
        return NULL;

    prof->name = strdup(name);
    prof->courses_taught = create_ptrlist();
    add_professor(prof);

    return prof;
}

void add_course_to_professor(professor_t *prof, course_t *course)
{
    if (!prof || !course)
        return;

    add_item(prof->courses_taught, course);
}

professor_t *get_professor(char *name)
{
    if (!name || !g_all_profs)
        return NULL;

    int i = 0;
    professor_t *iter;
    for (i = 0; i < g_all_profs->length; i++) {
        iter = get_item(professor_t, g_all_profs, i);
        if (strcasecmp(iter->name, name) == 0)
            return iter;
    }

    return NULL;
}

course_t *get_professor_class(professor_t *prof, size_t idx)
{
    if (!prof)
        return NULL;

    return get_item(course_t, prof->courses_taught, idx);
}

void list_professors()
{
    if (!g_all_profs)
        return;

    int i = 0;
    professor_t *iter;
    printf("--All Professors--\n");
    for (i = 0; i < g_all_profs->length; i++) {
        iter = get_item(professor_t, g_all_profs, i);
        printf("%s\n", iter->name);
    }
}

void list_classes_taught(professor_t *prof)
{
    if (!prof)
        return;

    int i = 0;
    course_t *iter;
    printf("--%s's Classes--\n", prof->name);
    print_course_banner();
    for (i = 0; i < prof->courses_taught->length; i++) {
        printf("#%d|", i+1);
        iter = get_item(course_t, prof->courses_taught, i);
        iter->print_course(iter); //brief?
    }
}

