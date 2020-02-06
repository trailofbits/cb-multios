#ifndef LIBXDR_H_
#define LIBXDR_H_

#include "cgc_stdlib.h"
#include "cgc_stdint.h"

/* Standard definitions */
typedef unsigned char opaque;
typedef char string;

#define CHECK_RESULT() do { \
    if (_result < 0) return _result; \
} while (0)

#define ASSERT_RESULT() do { \
    if (_result < 0) cgc_exit(1); \
} while (0)

static int _checked_calloc(void **ptr, unsigned int count, cgc_size_t size)
{
    // make sure that we won't overflow
    if (size > INT32_MAX)
        return -1;
    if ((unsigned long long)count * size > INT32_MAX)
        return -1;

    *ptr = cgc_calloc(count, size);
    if (*ptr == NULL)
#ifdef PATCHED
    {
        if (count == 0 || size == 0)
        {
            *ptr = cgc_malloc(8);
        }
        if (*ptr == NULL)
            cgc_exit(0);
    }
#else
        return -1;
#endif
    return 0;
}

static int marshal_int(long *data, unsigned char **out, cgc_size_t *size)
{
    unsigned char *_out = *out;
    long _data = *data;
    if (*size < 4)
        return -1;

    _out[0] = (_data >> 24) & 0xff;
    _out[1] = (_data >> 16) & 0xff;
    _out[2] = (_data >> 8) & 0xff;
    _out[3] = (_data >> 0) & 0xff;

    (*size) -= 4;
    (*out) += 4;
    return 0;
}

static int marshal_unsigned_int(unsigned long *data, unsigned char **out, cgc_size_t *size)
{
    unsigned char *_out = *out;
    unsigned long _data = *data;
    if (*size < 4)
        return -1;

    _out[0] = (_data >> 24) & 0xff;
    _out[1] = (_data >> 16) & 0xff;
    _out[2] = (_data >> 8) & 0xff;
    _out[3] = (_data >> 0) & 0xff;

    (*size) -= 4;
    (*out) += 4;
    return 0;
}

static int marshal_opaque(unsigned char *data, unsigned char **out, cgc_size_t *size)
{
    if (*size < 1)
        return -1;

    *(*out) = *data;

    (*size) -= 1;
    (*out) += 1;
    return 0;
}

static int marshal_double(double *data, unsigned char **out, cgc_size_t *size)
{
    double *_out = (double *)*out;
    if (*size < 8)
        return -1;
    *_out = *data;
    (*size) -= 8;
    (*out) += 8;
    return 0;
}

static int unmarshal_double(double *data, unsigned char **in, cgc_size_t *size)
{
    double *_in = (double *)*in;
    if (*size < 8)
        return -1;
    *data = *_in;
    (*size) -= 8;
    (*in) += 8;
    return 0;
}

static int unmarshal_int(long *data, unsigned char **in, cgc_size_t *size)
{
    unsigned char *_in = *in;
    long _data = 0;
    if (*size < 4)
        return -1;

    _data |= _in[0] << 24;
    _data |= _in[1] << 16;
    _data |= _in[2] << 8;
    _data |= _in[3] << 0;
    *data = _data;

    (*size) -= 4;
    (*in) += 4;
    return 0;
}

static int unmarshal_unsigned_int(unsigned long *data, unsigned char **in, cgc_size_t *size)
{
    unsigned char *_in = *in;
    unsigned long _data = 0;
    if (*size < 4)
        return -1;

    _data |= _in[0] << 24;
    _data |= _in[1] << 16;
    _data |= _in[2] << 8;
    _data |= _in[3] << 0;
    *data = _data;

    (*size) -= 4;
    (*in) += 4;
    return 0;
}

static int unmarshal_opaque(unsigned char *data, unsigned char **in, cgc_size_t *size)
{
    if (*size < 1)
        return -1;

    *data = *(*in);

    (*size) -= 1;
    (*in) += 1;
    return 0;
}

#endif
