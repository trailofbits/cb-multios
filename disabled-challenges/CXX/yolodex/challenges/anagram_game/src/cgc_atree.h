#ifndef ATREE_H_
#define ATREE_H_

#include "cgc_alphabet.h"

typedef struct atree_link_t {
    unsigned int freq;
    struct atree_node_t *child;
} atree_link_t;

typedef struct atree_node_t {
    unsigned int level;
    unsigned short degree;
    unsigned short max_degree;

    struct atree_node_t *next_leaf;
    struct atree_node_t *prev_leaf;

    const char *words[0];
    atree_link_t children[0];
} atree_node_t;
#define NODE_MIN_DEGREE 2
#define NODE_MIN_SIZE (sizeof(atree_node_t) + sizeof(atree_link_t) * NODE_MIN_DEGREE)

typedef struct {
    unsigned int count;

    atree_node_t *root;
    atree_node_t *leaf;

    /* map from level to character */
    char levelmap[ALPHABET_SIZE];
} atree_t;

atree_t *cgc_atree_init(freqtab_t *ftab);
int cgc_atree_add(atree_t *tree, const char *word);
int cgc_atree_remove(atree_t *tree, const char *word);
char **cgc_atree_query(atree_t *tree, const char *word);
char **cgc_atree_query_subset(atree_t *tree, const char *word);
const char *cgc_atree_cgc_random(atree_t *tree);
static inline unsigned int atree_count(atree_t *tree)
{
    return tree->count;
}

#endif /* !ATREE_H_ */
