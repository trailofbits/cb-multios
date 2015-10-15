#ifndef IO_H_
#define IO_H_

typedef struct {
    int fd;
    char *buf;
    int pos;
    int length;
    int mark;
} io_t;

void io_init_fd(io_t *io, int fd);
void io_init_bytes(io_t *io, const char *str, unsigned int length);
void io_init_string(io_t *io, const char *str);
void io_mark(io_t *io);
int io_rewind(io_t *io);
int io_tell(io_t *io);
int io_seek(io_t *io, int pos);
int io_getc(io_t *io);
int io_ungetc(io_t *io);
int io_peek(io_t *io);
int io_read(io_t *io, char *buf, unsigned int cnt);

#endif
