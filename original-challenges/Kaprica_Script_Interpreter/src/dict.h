#ifndef DICT_H_
#define DICT_H_

typedef void (*record_free_t) (void *);

typedef struct _record_t {
    struct _record_t *next, *prev;
    struct _record_t *tbl_next, *tbl_prev;
    char *name;
} _record_t;

typedef struct {
    record_free_t free_fn;
    _record_t *head;
    _record_t **tbl;

    unsigned int count;
    unsigned int length;
} dict_t;

int dict_init(dict_t *dict, record_free_t);
void dict_free(dict_t *dict);
void *dict_get(dict_t *dict, const char *name);
int dict_add(dict_t *dict, const char *name, void *value);

#endif
