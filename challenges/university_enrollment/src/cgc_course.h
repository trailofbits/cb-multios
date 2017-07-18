#ifndef COURSE_H_
#define COURSE_H_
typedef struct course course_t;

#include "cgc_stdlib.h"

#include "cgc_time.h"
#include "cgc_ptrlist.h"
#include "cgc_professor.h"
#include "cgc_department.h"

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


course_t *cgc_create_course(unsigned int course_id, char *prof_name, char *dept_name, short course_num,
                        short credits, short current_enrollment, short max_enrollment,
                        days_t days, time_t start, time_t end, char *title);
ptrlist_t *get_course(int course_id);

void cgc_list_courses_by_num(char *name, short course_num);
void cgc_list_courses_by_id(int course_id);

course_t *cgc_select_course_num(char *name, int course_num, cgc_size_t idx);
course_t *cgc_select_course_id(int course_id, cgc_size_t idx);

void cgc_print_course_list(ptrlist_t *courses);
int cgc_check_time_conflict(course_t *course1, course_t *course2);
void cgc_print_course_banner();

#endif
