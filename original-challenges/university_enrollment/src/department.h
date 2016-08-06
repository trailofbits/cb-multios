#ifndef DEPARTMENT_H_
#define DEPARTMENT_H_
typedef struct department department_t;

#include "ptrlist.h"
#include "course.h"

struct department
{
    char *name;
    ptrlist_t *courses_available;
};

department_t *create_department(char *name);
void add_course_to_department(department_t *dept, course_t *course);

department_t *get_department(char *name);

void list_departments();
void list_dept_courses(department_t *dept);

#endif
