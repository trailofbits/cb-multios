#ifndef PROFESSOR_H_
#define PROFESSOR_H_
typedef struct professor professor_t;

#include <stdlib.h>
#include "ptrlist.h"
#include "course.h"

struct professor
{
    char *name;
    ptrlist_t *courses_taught;
};

professor_t *create_professor(char *name);
void add_course_to_professor(professor_t *prof, course_t *course);

professor_t *get_professor(char *name);
course_t *get_professor_class(professor_t *prof, size_t idx);

void list_professors();
void list_classes_taught(professor_t *prof);

#endif
