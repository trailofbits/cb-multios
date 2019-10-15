#include "libpov.h"
#include "cgc_stdio_private.h"

cgc_ssize_t cgc_fwrite(const void *ptr, cgc_size_t size, FILE *stream)
{
    const char *buf = ptr;
    cgc_size_t idx = 0, tx;

    if (stream->idx == INVALID_IDX)
    {
unbuffered:
        if (cgc_transmit(stream->fd, ptr, size, &tx) != 0 || tx == 0)
            return -1;
        return tx;
    }
    else
    {
        if (size >= sizeof(stream->buffer))
        {
            cgc_fflush(stream);
            goto unbuffered;
        }

        if (stream->length + size >= sizeof(stream->buffer))
        {
            tx = sizeof(stream->buffer) - stream->length;
            cgc_memcpy(stream->buffer + stream->length, buf, tx);
            stream->length += tx;
            idx += tx;

            cgc_fflush(stream);
        }

        if (idx < size)
        {
            tx = size - idx;
            cgc_memcpy(stream->buffer + stream->length, buf + idx, tx);
            stream->length += tx;
            idx += tx;
        }

        return idx;
    }
}
