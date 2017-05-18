#ifndef STRIO_H_
#define STRIO_H_

typedef struct {
    char *buf;
    int pos;
    int length;
} strio_t;

int cgc_strio_init(strio_t *s);
void cgc_strio_free(strio_t *s);
char *cgc_strio_dup(strio_t *s);
int cgc_strio_append_char(strio_t *s, char c);

#endif
