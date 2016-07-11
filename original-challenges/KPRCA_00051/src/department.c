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
#include <stdlib.h>
#include <string.h>

#include "department.h"
#include "course.h"
#include "ptrlist.h"

static ptrlist_t *g_all_depts = NULL;

ptrlist_t *find_dept_courses_by_num(char *name, short course_num)
{
    if (!name)
        return NULL;

    department_t *dept = get_department(name);
    if (!dept)
        return NULL;

    int i = 0;
    course_t *iter;
    ptrlist_t *courses = create_ptrlist();
    for (i = 0; i < dept->courses_available->length; i++) {
        iter = get_item(course_t, dept->courses_available, i);
        if (course_num == iter->course_num)
            add_item(courses, iter);
    }

    return courses;
}

void add_department(department_t *dept)
{
    if (!dept)
        return;

    if (!g_all_depts)
        g_all_depts = create_ptrlist();

    add_item(g_all_depts, dept);
}

department_t *create_department(char *name)
{
    if (!name)
        return NULL;

    department_t *dept = malloc(sizeof(department_t));
    if (!dept)
        return NULL;

    dept->name = strdup(name);
    dept->courses_available = create_ptrlist();
    add_department(dept);

    return dept;
}

void add_course_to_department(department_t *dept, course_t *course)
{
    if(!dept || !course)
        return;

    add_item(dept->courses_available, course);
}

department_t *get_department(char *name)
{
    if (!name || !g_all_depts)
        return NULL;

    int i = 0;
    department_t *iter;
    for (i = 0; i < g_all_depts->length; i++) {
        iter = get_item(department_t, g_all_depts, i);
        if (strcasecmp(iter->name, name) == 0)
            return iter;
    }

    return NULL;
}

void list_departments()
{
    if (!g_all_depts)
        return;

    int i = 0;
    department_t *iter;
    printf("--All Departments--\n");
    for (i = 0; i < g_all_depts->length; i++) {
        iter = get_item(department_t, g_all_depts, i);
        printf("%s\n", iter->name);
    }
}

void list_dept_courses(department_t *dept)
{
    if (!dept)
        return;

    int i;
    course_t *iter;
    printf("--Department Availability--\n");
    print_course_banner();
    for (i = 0; i < dept->courses_available->length; i++) {
        printf("#%d|", i+1);
        iter = get_item(course_t, dept->courses_available, i);
        iter->print_course(iter);
    }
}
