#include "cgc_stdio_private.h"

int cgc_fflush(FILE *stream)
{
    if (stream->idx == INVALID_IDX)
        return 0;

    if (stream->rw == F_READ)
    {
        /* drop the contents of the cgc_read buffer */
        stream->idx = stream->length = 0;
        return 0;
    }
    else
    {
        int ret = 0;
        cgc_size_t tx;

        /* flush to fd */
        if (cgc_transmit(stream->fd, stream->buffer + stream->idx, stream->length - stream->idx, &tx) != 0 || tx == 0)
            ret = -1;

        stream->idx = stream->length = 0;
        return ret;
    }
}
