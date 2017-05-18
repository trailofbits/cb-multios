#ifndef COMPARE_H_
#define COMPARE_H_

#include "cgc_hash.h"
#include "cgc_sfile.h"

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

lcll_t *cgc_pre_process(SFILE *sfp, cgc_size_t *wordc, cgc_size_t *linec);
lc_t *cgc_new_linecmp(char *line);
void cgc_free_linecmp_list(lcll_t **head);

#endif
