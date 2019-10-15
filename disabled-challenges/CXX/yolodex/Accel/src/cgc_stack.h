#ifndef STACK_H_
#define STACK_H_

typedef struct stack stack_t;
struct stack {
    char *data;
    stack_t *next;
};

char *cgc_peek_top(stack_t *stack);
int cgc_push(stack_t **stack, char *data);
int cgc_push_copy(stack_t **stack, char *data, cgc_size_t size);
char *cgc_pop_copy(stack_t **stack);
void cgc_clear_stack();

#endif /* STACK_H */
