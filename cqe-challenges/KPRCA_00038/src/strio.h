#ifndef STRIO_H_
#define STRIO_H_

typedef struct {
    char *buf;
    int pos;
    int length;
} strio_t;

int strio_init(strio_t *s);
void strio_free(strio_t *s);
char *strio_dup(strio_t *s);
int strio_append_char(strio_t *s, char c);

#endif
