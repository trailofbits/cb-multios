typedef struct node {
    struct node *left, *right;
    unsigned int level;
    unsigned char *key;
    cgc_size_t key_length;
    unsigned char *data;
    cgc_size_t data_length;
} node_t;

node_t *cgc_tree_lookup(node_t **T, unsigned char *key, cgc_size_t key_length);
node_t *cgc_tree_insert(node_t **T, node_t *n);
node_t *cgc_tree_delete(node_t **T, unsigned char *key, cgc_size_t key_length);
node_t *cgc_tree_smallest(node_t **T);
node_t *cgc_tree_largest(node_t **T);
node_t *cgc_tree_succ(node_t **T);
node_t *cgc_tree_pred(node_t **T);
node_t *cgc_tree_prev(node_t **T, unsigned char *key, cgc_size_t key_length);
node_t *cgc_tree_next(node_t **T, unsigned char *key, cgc_size_t key_length);
