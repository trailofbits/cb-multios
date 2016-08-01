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
#include "student.h"
#include <stdlib.h>
#include <string.h>

int _add_course(student_t *student, course_t *course)
{
    if (!student || !course)
        return FALSE;

    int i = 0;
    if (course->current_enrollment >= course->max_enrollment) {
        //printf("Class is full\n");
        return FALSE;
    }

    if (student->total_credits + course->credits > MAX_CREDITS) {
        //printf("You've exceeded your semester credit limit\n");
        return FALSE;
    }
#ifdef PATCHED
    if (student->num_courses == MAX_COURSES)
        return FALSE;
#endif

    for (i = 0; i < student->num_courses; i++) {
        if (check_time_conflict(student->courses[i], course) != 0 || student->courses[i] == course) {
            //printf("Timing conflict\n");
            return FALSE;
        }
        if (student->courses[i]->course_id == course->course_id) {
            //printf("Cannot enroll in the same class multiple times\n");
            return FALSE;
        }
    }

    if (student->major != course->dept && course->credits < 3) {
        //printf("Only minor classes are allowed in major\n");
        return FALSE;
    }

    if (student->major == course->dept) {
        if (student->num_major_courses >= MAJOR_COURSE_MAX) {
            //printf("Cannot exceed more than 4 in major courses.\n");
            return FALSE;
        } else {
            student->num_major_courses++;
        }
    }

    student->total_credits += course->credits;
    student->courses[student->num_courses++] = course;
    return TRUE;
}

int _set_major(student_t *student, char *dept_name)
{
    if (!student || !dept_name)
        return FALSE;

    department_t *dept = get_department(dept_name);
    if (!dept)
        return FALSE;

    student->major = dept;
    return TRUE;
}

int _remove_course(student_t *student, size_t idx)
{
    if (!student || idx >= student->num_courses)
        return FALSE;

    student->total_credits -= student->courses[idx]->credits;
    if (student->major == student->courses[idx]->dept)
        student->num_major_courses--;

    if (idx < student->num_courses - 1) {
        memcpy(&student->courses[idx], &student->courses[idx+1],
                sizeof(void *) * (student->num_courses - idx - 1));
    }

    student->num_courses--;

    return TRUE;
}

void _list_classes(student_t *student)
{
    if (!student)
        return;

    int i = 0;
    print_course_banner();
    for (i = 0; i < student->num_courses; i++) {
        printf("#%d|", i+1);
        student->courses[i]->print_course(student->courses[i]);
    }
}

void _print_schedule(student_t *student)
{
    if (!student)
        return;

    int i = 0;
    print_course_banner();
    for (i = 0; i < student->num_courses; i++) {
        printf("#%d|", i+1);
        student->courses[i]->print_course(student->courses[i]);
    }
}

student_t *create_student(char *name)
{
    if (!name)
        return NULL;

    student_t *student = malloc(sizeof(student_t));
    student->name = strdup(name);
    student->major = NULL;
    student->num_courses = 0;
    student->total_credits = 0;

    student->add_course = &_add_course;
    student->set_major = &_set_major;
    student->remove_course = &_remove_course;
    student->list_classes = &_list_classes;
    student->print_schedule = &_print_schedule;

    return student;
}
