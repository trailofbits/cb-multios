#ifndef PROFESSOR_H_
#define PROFESSOR_H_
typedef struct professor professor_t;

#include "cgc_stdlib.h"
#include "cgc_ptrlist.h"
#include "cgc_course.h"

struct professor
{
    char *name;
    ptrlist_t *courses_taught;
};

professor_t *cgc_create_professor(char *name);
void cgc_add_course_to_professor(professor_t *prof, course_t *course);

professor_t *cgc_get_professor(char *name);
course_t *cgc_get_professor_class(professor_t *prof, cgc_size_t idx);

void cgc_list_professors();
void cgc_list_classes_taught(professor_t *prof);

#endif
