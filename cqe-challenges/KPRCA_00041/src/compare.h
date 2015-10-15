#ifndef COMPARE_H_
#define COMPARE_H_

#include "hash.h"
#include "sfile.h"

typedef struct linecmp lc_t;
struct linecmp {
    char *pline;
    char *no_ws_line;

    lhash_t lhash;
    lhash_t no_ws_lhash;

}; // line comparator

typedef struct linecmp_list lcll_t;
struct linecmp_list {
    lc_t *lc;
    lcll_t *next;
};

lcll_t *pre_process(SFILE *sfp, size_t *wordc, size_t *linec);
lc_t *new_linecmp(char *line);
void free_linecmp_list(lcll_t **head);

#endif
