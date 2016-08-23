typedef struct node {
    struct node *left, *right;
    unsigned int level;
    unsigned char *key;
    size_t key_length;
    unsigned char *data;
    size_t data_length;
} node_t;

node_t *tree_lookup(node_t **T, unsigned char *key, size_t key_length);
node_t *tree_insert(node_t **T, node_t *n);
node_t *tree_delete(node_t **T, unsigned char *key, size_t key_length);
node_t *tree_smallest(node_t **T);
node_t *tree_largest(node_t **T);
node_t *tree_succ(node_t **T);
node_t *tree_pred(node_t **T);
node_t *tree_prev(node_t **T, unsigned char *key, size_t key_length);
node_t *tree_next(node_t **T, unsigned char *key, size_t key_length);
