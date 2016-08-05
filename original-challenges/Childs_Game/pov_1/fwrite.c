#include <libpov.h>
#include "stdio_private.h"

ssize_t fwrite(const void *ptr, size_t size, FILE *stream)
{
    const char *buf = ptr;
    size_t idx = 0, tx;

    if (stream->idx == INVALID_IDX)
    {
unbuffered:
        if (transmit(stream->fd, ptr, size, &tx) != 0 || tx == 0)
            return -1;
        return tx;
    }
    else
    {
        if (size >= sizeof(stream->buffer))
        {
            fflush(stream);
            goto unbuffered;
        }

        if (stream->length + size >= sizeof(stream->buffer))
        {
            tx = sizeof(stream->buffer) - stream->length;
            memcpy(stream->buffer + stream->length, buf, tx);
            stream->length += tx;
            idx += tx;

            fflush(stream);
        }

        if (idx < size)
        {
            tx = size - idx;
            memcpy(stream->buffer + stream->length, buf + idx, tx);
            stream->length += tx;
            idx += tx;
        }

        return idx;
    }
}
