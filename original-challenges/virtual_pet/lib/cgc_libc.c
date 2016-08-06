#include "cgc_libc.h"
#include "cgc_malloc.h"

void *memset(void *b, int c, size_t len) {
    if (!b)
        return NULL;

    /* less than good */
    if (!len)
        return b;

    unsigned char *p = b;

    while (len--)
        *p++ = (unsigned char) c;

    return b;
}

#if 0
void *calloc(size_t count, size_t size) {
    if (size == 0)
        return NULL;

    if (count == 0)
        return NULL;

    unsigned long long total = count * size;
    size_t block_size = (size_t)total;
    void *res = NULL;

    if (total == block_size)
        res = malloc(block_size);

    if (res != NULL)
        memset(res, 0, block_size);

    return res;
}
#endif

int strcmp(const char *s1, const char *s2) {
	for (; *s1 && *s2 && (*s1 == *s2); s1++, s2++)
		/* EMPTY */;
	return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

int strncmp(const char *s1, const char *s2, size_t dstsize) {
    if (!s1)
        return 0;

    if (!s2)
        return 0;

    if (!dstsize)
        return 0;

    while (dstsize--) {
        if (*s1++ != *s2++)
            return *(unsigned char *)(s1 - 1) - *(unsigned char *)(s2 - 1);
    }

    return 0;
}

size_t strlcpy(char *dst, const char *src, const size_t dstsize) {
    size_t i = 0;

    if (!src)
        return 0;

    if (!dst)
        return 0;

    if (!dstsize)
        return 0;

    while (i < dstsize - 1) {
        if (src[i] == 0)
            break;

        dst[i] = src[i];
        i++;
    }

    dst[i] = 0;
    return i;
}

size_t strlcat(char *dst, const char *src, const size_t dstsize) {
    size_t current_dst_len;

    if (!src)
        return 0;

    if (!dst)
        return 0;

    if (!dstsize)
        return 0;

    current_dst_len = strlen(dst);
    return current_dst_len + strlcpy(dst + current_dst_len, src, dstsize - current_dst_len);
}

size_t strlen(const char *s) {
    const char *p;

    /* less than good. */
    if (!s)
        return 0;

    p = s;

    while (*s)
        ++s;

    return (size_t)(s - p);
}

char *strchr(const char *s, int c) {
    if (!s)
        return 0;

    if (c < 0)
        return 0;

    if (c > 255)
        return 0;

    while (*s != (char)c) {
        if (!*s++)
            return 0;
    }

    return (char *)s;
}

size_t strspn(const char *s1, const char *s2) {
    size_t ret = 0;

    if (!s1)
        return 0;

    if (!s2)
        return 0;

    while (*s1 && strchr(s2, *s1++))
        ret++;

    return ret;
}

size_t strcspn(const char *s1, const char *s2) {
    size_t ret = 0;

    if (!s1)
        return 0;

    if (!s2)
        return 0;

    while (*s1) {
        if (strchr(s2, *s1))
            return ret;
        else {
            s1++;
            ret++;
        }
    }

    return ret;
}

char *strtok(char *str, const char *sep) {
    static char *p = NULL;

    if (str)
        p = str;

    if (!p)
        return 0;

    if (!sep)
        return 0;

    str = p + strspn(p, sep);
    p = str + strcspn(str, sep);

    if (p == str)
        return p = 0;

    if (*p) {
        *p = 0;
        p = p + 1;
    } else
        p = 0;

    return str;
}

char *strdup(const char *src) {
    size_t len = 0;
    char *dst = NULL;

    if (!src)
        return 0;

    len = strlen(src) + 1;
    dst = malloc(len);

    if (dst)
        memcpy(dst, src, len);

    return dst;
}

int transmit_all(int fd, const char *s, size_t size) {
    int ret;
    size_t total_sent = 0;
    size_t sent = 0;

    while (total_sent < size) {
        ret = transmit(fd, s + total_sent, size - total_sent, &sent);
        if (ret > 0) {
            err(3, "transmit failed\n");
        }
        total_sent += sent;
    }

    return 1;
}

int transmit_str(int fd, const char *s) {
    return transmit_all(fd, s, strlen(s));
}

void err(unsigned int id, char *str) {
    transmit_str(STDERR, str);
    _terminate(id);
}

void *memcpy(void *dst, const void *src, size_t size) {
    char *dst_char = (char *)dst;
    char *src_char = (char *)src;

    while (size--)
        *dst_char++ = *src_char++;

    return dst;
}
