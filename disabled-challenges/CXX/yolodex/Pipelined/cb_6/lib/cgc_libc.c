#include "cgc_cgc_libc.h"
#include "cgc_cgc_malloc.h"

void *cgc_memset(void *b, int c, cgc_size_t len) {
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
void *calloc(cgc_size_t count, cgc_size_t size) {
    if (size == 0)
        return NULL;

    if (count == 0)
        return NULL;

    unsigned long long total = count * size;
    cgc_size_t block_size = (cgc_size_t)total;
    void *res = NULL;

    if (total == block_size)
        res = malloc(block_size);

    if (res != NULL)
        cgc_memset(res, 0, block_size);

    return res;
}
#endif

int cgc_strcmp(const char *s1, const char *s2) {
    if (!s1)
        return 0;

    if (!s2)
        return 0;

    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }

    return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

int cgc_strncmp(const char *s1, const char *s2, cgc_size_t dstsize) {
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

cgc_size_t cgc_strlcpy(char *dst, const char *src, const cgc_size_t dstsize) {
    cgc_size_t i = 0;

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

cgc_size_t cgc_strlcat(char *dst, const char *src, const cgc_size_t dstsize) {
    cgc_size_t current_dst_len;

    if (!src)
        return 0;

    if (!dst)
        return 0;

    if (!dstsize)
        return 0;

    current_dst_len = cgc_strlen(dst);
    return current_dst_len + cgc_strlcpy(dst + current_dst_len, src, dstsize - current_dst_len);
}

cgc_size_t cgc_strlen(const char *s) {
    const char *p;

    /* less than good. */
    if (!s)
        return 0;

    p = s;

    while (*s)
        ++s;

    return (cgc_size_t)(s - p);
}

char *cgc_strchr(const char *s, int c) {
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

cgc_size_t cgc_strspn(const char *s1, const char *s2) {
    cgc_size_t ret = 0;

    if (!s1)
        return 0;

    if (!s2)
        return 0;

    while (*s1 && cgc_strchr(s2, *s1++))
        ret++;

    return ret;
}

cgc_size_t cgc_strcspn(const char *s1, const char *s2) {
    cgc_size_t ret = 0;

    if (!s1)
        return 0;

    if (!s2)
        return 0;

    while (*s1) {
        if (cgc_strchr(s2, *s1))
            return ret;
        else {
            s1++;
            ret++;
        }
    }

    return ret;
}

char *cgc_strtok(char *str, const char *sep) {
    static char *p = NULL;

    if (str)
        p = str;

    if (!p)
        return 0;

    if (!sep)
        return 0;

    str = p + cgc_strspn(p, sep);
    p = str + cgc_strcspn(str, sep);

    if (p == str)
        return p = 0;

    if (*p) {
        *p = 0;
        p = p + 1;
    } else
        p = 0;

    return str;
}

char *cgc_strdup(const char *src) {
    cgc_size_t len = 0;
    char *dst = NULL;

    if (!src)
        return 0;

    len = cgc_strlen(src) + 1;
    dst = cgc_malloc(len);

    if (dst)
        cgc_memcpy(dst, src, len);

    return dst;
}

int cgc_transmit_all(int fd, const char *s, cgc_size_t size) {
    int ret;
    cgc_size_t total_sent = 0;
    cgc_size_t sent = 0;

    while (total_sent < size) {
        ret = cgc_transmit(fd, s + total_sent, size - total_sent, &sent);
        if (ret > 0) {
            cgc_printf(3, "tried writing to %d\n", fd);
            cgc_err(3, "transmit failed\n");
        }
        total_sent += sent;
    }

    return 1;
}

int cgc_transmit_str(int fd, char *s) {
    return cgc_transmit_all(fd, s, cgc_strlen(s));
}

cgc_size_t cgc_receive_all(int fd, char *buf, const cgc_size_t size) {
    int ret;
    cgc_size_t received;
    cgc_size_t offset = 0;

    while (offset< size) {
        ret = cgc_receive(fd, buf + offset, 1, &received);
        if (ret != 0) {
            cgc_printf(STDERR, "got error reading from %u: %u\n", fd, ret);
            cgc_err(4, "receive failed (got err)\n");
        }

        if (received == 0) {
            cgc_printf(STDERR, "received nothing from %u: %u\n", fd, ret);
            return 0;
        }
       
        offset++;
    }
    return offset;
}

int cgc_read_until(int fd, char *buf, unsigned int size, char endchar) {
    char ch;
    unsigned int total = 0;
    cgc_size_t nbytes;
    while (1) {
        if (cgc_receive(fd, &ch, 1, &nbytes) != 0 || nbytes == 0) {
            return -1;
        }
        if (ch == endchar) break;
        if (total >= size) return -1;
        buf[total++] = ch;
    }
    return (int)total;
}

void cgc_err(unsigned int id, char *str) {
    cgc_transmit_str(STDERR, str);
    cgc__terminate(id);
}

void *cgc_memcpy(void *dst, const void *src, cgc_size_t size) {
    char *dst_char = (char *)dst;
    char *src_char = (char *)src;

    while (size--)
        *dst_char++ = *src_char++;

    return dst;
}

int cgc_memcmp(const void *buf1, const void *buf2, cgc_size_t size) {
    char *buf1_char = (char *)buf1;
    char *buf2_char = (char *)buf2;

    while (size--)
        if (*buf1_char != *buf2_char) {
            return *buf1_char - *buf2_char;
        } else {
            buf1_char++;
            buf2_char++;
        }

    return 0;
}

void cgc_sleep(int seconds) {
    struct cgc_timeval tv;
    tv.tv_sec = seconds;
    tv.tv_usec = 0;
    cgc_fdwait(0, NULL, NULL, &tv, NULL);
}
