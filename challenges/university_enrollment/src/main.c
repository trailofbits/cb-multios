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

#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_read.h"
#include "cgc_student.h"
#include "cgc_course.h"
#include "cgc_department.h"
#include "cgc_professor.h"
#include "cgc_data_gen.h"


static const int LINE_SIZE = 1024;
static char line[LINE_SIZE];

int cgc_yes_no_input()
{
    cgc_printf("1 - Yes\n");
    cgc_printf("2 - No\n");
    cgc_printf("Choice: ");
    return cgc_readnum(line, LINE_SIZE);
}

char *cgc_answer_question(char *question)
{
    int socket_open = 1;
    cgc_printf("%s", question);
    socket_open = cgc_readline(line, LINE_SIZE);
    while(socket_open && socket_open != -1) {
        cgc_printf("Bad Input\n");
        cgc_printf("%s", question);
    }

    return line;
}

student_t *cgc_register_student()
{
    student_t *student = NULL;
    char *answer;

    answer = cgc_answer_question("Enter name: ");
    student = cgc_create_student(answer);

    cgc_printf("Select a major\n");
    cgc_printf("List Departments?\n");
    if (cgc_yes_no_input() == 1)
        cgc_list_departments();

    answer = cgc_answer_question("Enter your Major's Department Name: ");
    if(!student->set_major(student, answer))
        cgc_printf("Bad Department Name\n");

    cgc_printf("Congratulations. You're read to start adding classes\n");
    return student;
}

void cgc_search_classes()
{
    int done = FALSE;
    int choice = 0;
    char *answer, *dept_name;
    short course_num;
    int course_id;

    while(!done) {
        cgc_printf("Class Search\n");
        cgc_printf("0 - Go Back\n");
        cgc_printf("1 - Search by Professor Name (ex: Gerardo Chacon)\n");
        cgc_printf("2 - Search by Department Name (ex: MAT)\n");
        cgc_printf("3 - Search by Class ID (ex: MAT 150)\n");
        cgc_printf("4 - Search by Course ID (ex: 2600)\n");
        cgc_printf("Choice: ");
        choice = cgc_readnum(line, LINE_SIZE);
        if (choice == -1) {
            break;
        }

        switch(choice) {
        case 0:
            done = TRUE; break;
        case 1:
            cgc_printf("List Professors?\n");
            if (cgc_yes_no_input() == 1)
                cgc_list_professors();
            answer = cgc_answer_question("Enter professor's full name: ");
            cgc_list_classes_taught(cgc_get_professor(answer));
            break;
        case 2:
            cgc_printf("List Departments?\n");
            if (cgc_yes_no_input() == 1)
                cgc_list_departments();
            answer = cgc_answer_question("Enter Department name: ");
            cgc_list_dept_courses(cgc_get_department(answer));
            break;
        case 3:
            answer = cgc_answer_question("Enter Class ID: ");
            dept_name = cgc_strsep(&answer, " ");
            if (answer) {
                course_num = cgc_strtol(answer, NULL, 10);
                cgc_list_courses_by_num(dept_name, course_num);
            } else {
                cgc_printf("Bad Input\n");
            }
            break;
        case 4:
            answer = cgc_answer_question("Enter Course ID: ");
            course_id = cgc_strtol(answer, NULL, 10);
            cgc_list_courses_by_id(course_id);
            break;
        default:
            cgc_printf("Bad Input\n");
        }
    }

    cgc_printf("Returning to main menu\n");
}

void cgc_add_class(student_t *student)
{
    int done = FALSE;
    int choice = 0;
    char *answer, dept_name[8], *pdept_name;
    short course_num;
    int course_id;
    course_t *course;

    while(!done) {
        cgc_printf("Add Class to Schedule\n");
        cgc_printf("0 - Go Back\n");
        cgc_printf("1 - Add by Class Num (ex: MAT 150)\n");
        cgc_printf("2 - Add by Course ID (ex: 2600)\n");
        cgc_printf("Choice: ");
        choice = cgc_readnum(line, LINE_SIZE);
        if (choice == -1)
            break;

        switch(choice) {
        case 0:
            done = TRUE; break;
        case 1:
            answer = cgc_answer_question("Enter Class ID: ");
            pdept_name = cgc_strsep(&answer, " ");
            if(!pdept_name || !answer || cgc_strlen(pdept_name) > 7) {
                cgc_printf("Bad Input\n");
                break;
            }
            cgc_strcpy(dept_name, pdept_name);
            course_num = cgc_strtol(answer, NULL, 10);
            cgc_printf("0 - Go Back\n");
            cgc_list_courses_by_num(dept_name, course_num);
            cgc_printf("Choice: ");
            choice = cgc_readnum(line, LINE_SIZE);
            if (choice && choice != -1) {
                course = cgc_select_course_num(dept_name, course_num, --choice);
                if (course) {
                    if (student->add_course(student, course))
                        cgc_printf("Successfully added course!\n");
                    else
                        cgc_printf("Could not add course.\n");
                } else {
                    cgc_printf("Bad selection\n");
                }
            }
            break;
        case 2:
            answer = cgc_answer_question("Enter Course ID: ");
            course_id = cgc_strtol(answer, NULL, 10);
            cgc_printf("0 - Go Back\n");
            cgc_list_courses_by_id(course_id);
            cgc_printf("Choice: ");
            choice = cgc_readnum(line, LINE_SIZE);
            if (choice && choice != -1) {
                course = cgc_select_course_id(course_id, --choice);
                if (course) {
                    if (student->add_course(student, course))
                        cgc_printf("Successfully added course!\n");
                    else
                        cgc_printf("Could not add course.\n");
                } else {
                    cgc_printf("Bad selection\n");
                }
            }
            break;
        default:
            cgc_printf("Bad Input\n");
        }
    }

    cgc_printf("Returning to main menu\n");
}

void cgc_remove_class(student_t *student)
{
    int choice = 0;

    cgc_printf("Remove Class from Schedule\n");
    cgc_printf("0 - Go Back\n");
    student->list_classes(student);
    cgc_printf("Choice: ");
    choice = cgc_readnum(line, LINE_SIZE);
    if (choice && choice != -1) {
        if (student->remove_course(student, --choice))
            cgc_printf("Successfully removed course!\n");
        else
            cgc_printf("Bad selection\n");
    }

    cgc_printf("Returning to main menu\n");
}

int main(int cgc_argc, char *cgc_argv[])
{
    cgc_generate_data();
    cgc_printf("University Course Scheduler\n\n");
    student_t *student = cgc_register_student();
    int exitted = FALSE;
    int choice = 0;

    while (!exitted) {
        cgc_printf("Main Menu\n");
        cgc_printf("1 - Search Classes\n");
        cgc_printf("2 - Add Class\n");
        cgc_printf("3 - Remove Class\n");
        cgc_printf("4 - Print Schedule\n");
        cgc_printf("5 - Exit\n");
        cgc_printf("Choice: ");
        choice = cgc_readnum(line, LINE_SIZE);
        if (choice == -1)
            break;

        switch(choice) {
        case 1:
            cgc_search_classes(); break;
        case 2:
            cgc_add_class(student); break;
        case 3:
            cgc_remove_class(student); break;
        case 4:
            student->print_schedule(student); break;
        case 5:
            exitted = TRUE; break;
        default:
            cgc_printf("Bad Input\n");
        }
    }

    cgc_printf("Exiting.\n");
    return 0;
}
