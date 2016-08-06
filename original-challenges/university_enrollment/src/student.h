#ifndef STUDENT_H_
#define STUDENT_H_

#define MAX_COURSES 7
#define MAX_CREDITS 17
#define MAJOR_COURSE_MAX 4
typedef struct student student_t;

#include "course.h"
#include "department.h"

enum {FALSE=0, TRUE=1};

struct student
{
    char *name;
    department_t *major;

    int num_courses;
    int num_major_courses;
    int total_credits;
    course_t *courses[MAX_COURSES];
    int (*add_course)(student_t *, course_t *);
    int (*set_major)(student_t *, char *);
    int (*remove_course)(student_t *, size_t);
    void (*list_classes)(student_t *);
    void (*print_schedule)(student_t *);
};

student_t *create_student();
void list_added_courses(student_t *student);

#endif
