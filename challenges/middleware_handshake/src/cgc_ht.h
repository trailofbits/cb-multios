#ifndef HT_H_
#define HT_H_

typedef struct ht_node_t {
    struct ht_node_t *next;
    struct ht_node_t *prev;
    char *k;
    void *value;
} ht_node_t;

typedef struct {
    struct ht_node_t *first;
    struct ht_node_t **tbl;

    unsigned int tbl_size;
    unsigned int tbl_count;
} ht_t;

int cgc_ht_init(ht_t *tbl);
int cgc_ht_compare(const char *a, const char *b);
int cgc_ht_insert(ht_t *tbl, const char *k, void *v);
int cgc_ht_lookup(ht_t *tbl, const char *k, ht_node_t **node);
int cgc_ht_delete(ht_t *tbl, const char *k, void **v);
ht_node_t *cgc_ht_first(ht_t *tbl);
ht_node_t *cgc_ht_next(ht_t *tbl, ht_node_t *);
static inline void *ht_node_value(ht_node_t *node)
{
    return node->value;
}

#endif
