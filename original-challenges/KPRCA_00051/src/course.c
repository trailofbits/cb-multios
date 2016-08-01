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
#include "course.h"
#include <string.h>

static ptrlist_t *g_all_courses = NULL;

void _print_course(course_t *course)
{
    if (!course) {
        printf("Bad Course\n");
        return;
    }

    char daystr[9];
    daystostr(course->days, daystr);
    printf("%d|%s %d|%s|CR:%d|CE:%d|MC:%d|%s|%02d:%02d|%02d:%02d|%s",
            course->course_id, course->dept->name, course->course_num, course->prof->name,
            course->credits, course->current_enrollment, course->max_enrollment, daystr,
            course->start.hour, course->start.minute, course->end.hour, course->end.minute,
            course->title);
    printf("\n");
}

ptrlist_t *find_courses_by_id(int course_id)
{
    if (!g_all_courses)
        return NULL;

    int i = 0;
    course_t *iter;
    ptrlist_t *courses = create_ptrlist();
    for (i = 0; i < g_all_courses->length; i++) {
        iter = get_item(course_t, g_all_courses, i);
        if (course_id == iter->course_id)
            add_item(courses, iter);
    }

    return courses;
}

ptrlist_t *find_courses_by_num(char *name, short course_num)
{
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


void add_course(course_t *course)
{
    if (!course)
        return;

    if (!g_all_courses)
        g_all_courses = create_ptrlist();

    if (add_item(g_all_courses, course) != 0) {
        printf("Out of Memory. Terminating\n");
        exit(1);
    }
}

course_t *create_course(unsigned int course_id, char *prof_name, char *dept_name, short course_num,
                        short credits, short current_enrollment, short max_enrollment,
                        days_t days, time_t start, time_t end, char *title)
{
    if (!prof_name || !dept_name || !title)
        return NULL;

    professor_t *prof = get_professor(prof_name);
    if (!prof)
        return NULL;
    department_t *dept = get_department(dept_name);
    if (!dept)
        return NULL;
    course_t *course = malloc(sizeof(course_t));
    if (!course)
        return NULL;

    course->course_id = course_id;
    course->prof = prof;
    course->dept = dept;
    course->course_num = course_num;
    course->credits = credits;
    course->current_enrollment = current_enrollment;
    course->max_enrollment = max_enrollment;
    course->days = days;
    course->start = start;
    course->end = end;
    course->title = strdup(title);
    course->print_course = &_print_course;

    add_course(course);
    add_course_to_professor(prof, course);
    add_course_to_department(dept, course);
    return course;
}

ptrlist_t *get_courses(int course_id)
{
    if (!g_all_courses)
        return NULL;

    int i = 0;
    course_t *iter;
    ptrlist_t *courses = create_ptrlist();
    for (i = 0; i < courses->length; i++) {
        iter = get_item(course_t, g_all_courses, i);
        if (iter->course_id == course_id)
            add_item(courses, iter);
    }

    return courses;
}

course_t *select_course_id(int course_id, size_t idx)
{
    course_t *course = NULL;
    ptrlist_t *courses = find_courses_by_id(course_id);

    if (idx < courses->length)
        course = get_item(course_t, courses, idx);

    if (courses)
        free(courses);

    return course;
}

course_t *select_course_num(char *name, int course_num, size_t idx)
{
    course_t *course = NULL;
    ptrlist_t *courses = find_courses_by_num(name, course_num);

    if (courses && idx < courses->length)
        course = get_item(course_t, courses, idx);

    if (courses)
        free(courses);

    return course;
}

void list_courses_by_num(char *name, short course_num)
{
    ptrlist_t *courses = find_courses_by_num(name, course_num);
    print_course_list(courses);
    if (courses)
        free(courses);
}

void list_courses_by_id(int course_id)
{
    ptrlist_t *courses = find_courses_by_id(course_id);
    print_course_list(courses);
    if (courses)
        free(courses);
}

void print_course_banner()
{
    printf("IDX|CID|Course|Professor|Credits|Enrolled|Max|Days|Start|End|Title\n");
}

void print_course_list(ptrlist_t *courses)
{
    if (!courses)
        return;

    int i = 0;
    course_t *iter;
    print_course_banner();
    for (i = 0; i < courses->length; i++) {
        iter = get_item(course_t, courses, i);
        printf("#%d|", i+1);
        iter->print_course(iter);
    }
}

int check_time_conflict(course_t *course1, course_t *course2)
{
    if (!days_intersect(course1->days, course2->days))
        return 0;

    if (timecmp(course1->start, course2->start) >= 0 && timecmp(course1->end, course2->end) <= 0)
        return -1;
    if (timecmp(course2->start, course1->start) >= 0 && timecmp(course2->end, course1->end) <= 0)
        return -1;

    return 0;
}

