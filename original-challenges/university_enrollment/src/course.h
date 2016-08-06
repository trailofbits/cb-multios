#ifndef COURSE_H_
#define COURSE_H_
typedef struct course course_t;

#include <stdlib.h>

#include "time.h"
#include "ptrlist.h"
#include "professor.h"
#include "department.h"

struct course
{
    unsigned int course_id;
    professor_t *prof;
    department_t *dept;
    short course_num;

    short credits;
    short current_enrollment;
    short max_enrollment;
    days_t days;
    time_t start;
    time_t end;
    char *title;

    void (*print_course)(course_t *);
};


course_t *create_course(unsigned int course_id, char *prof_name, char *dept_name, short course_num,
                        short credits, short current_enrollment, short max_enrollment,
                        days_t days, time_t start, time_t end, char *title);
ptrlist_t *get_course(int course_id);

void list_courses_by_num(char *name, short course_num);
void list_courses_by_id(int course_id);

course_t *select_course_num(char *name, int course_num, size_t idx);
course_t *select_course_id(int course_id, size_t idx);

void print_course_list(ptrlist_t *courses);
int check_time_conflict(course_t *course1, course_t *course2);
void print_course_banner();

#endif
