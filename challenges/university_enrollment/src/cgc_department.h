#ifndef DEPARTMENT_H_
#define DEPARTMENT_H_
typedef struct department department_t;

#include "cgc_ptrlist.h"
#include "cgc_course.h"

struct department
{
    char *name;
    ptrlist_t *courses_available;
};

department_t *cgc_create_department(char *name);
void cgc_add_course_to_department(department_t *dept, course_t *course);

department_t *cgc_get_department(char *name);

void cgc_list_departments();
void cgc_list_dept_courses(department_t *dept);

#endif
