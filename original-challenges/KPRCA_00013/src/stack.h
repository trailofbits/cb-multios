#ifndef STACK_H_
#define STACK_H_

typedef struct stack stack_t;
struct stack {
    char *data;
    stack_t *next;
};

char *peek_top(stack_t *stack);
int push(stack_t **stack, char *data);
int push_copy(stack_t **stack, char *data, size_t size);
char *pop_copy(stack_t **stack);
void clear_stack();

#endif /* STACK_H */
