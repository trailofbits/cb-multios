#ifndef _LIBCGC_H
#define _LIBCGC_H

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#ifdef NULL
# undef NULL
#endif
#define NULL (0)

typedef unsigned long cgc_size_t;
typedef long cgc_ssize_t;

#ifndef PAGE_SIZE
# define PAGE_SIZE 4096
#endif

#ifndef offsetof
# define offsetof(TYPE, MEMBER) __builtin_offsetof (TYPE, MEMBER)
#endif

#ifndef SSIZE_MAX
# define SSIZE_MAX ((cgc_ssize_t)((~((cgc_size_t)0ULL))>>1))
#endif

#ifndef SIZE_MAX
# define SIZE_MAX (~((cgc_size_t)0ULL))
#endif

#define CGC_FD_SETSIZE 1024

typedef long int _fd_mask;

#define CGC__NFDBITS (8 * sizeof(_fd_mask))

typedef struct {
    _fd_mask _fd_bits[CGC_FD_SETSIZE / CGC__NFDBITS];
} cgc_fd_set;

#define CGC_FD_ZERO(set)                                            \
    do {                                                            \
        int __i;                                                    \
        for (__i = 0; __i < (CGC_FD_SETSIZE / CGC__NFDBITS); __i++) \
            (set)->_fd_bits[__i] = 0;                               \
    } while (0)

#define CGC_FD_SET(b, set) \
    ((set)->_fd_bits[b / CGC__NFDBITS] |= (1 << (b & (CGC__NFDBITS - 1))))

#define CGC_FD_CLR(b, set) \
    ((set)->_fd_bits[b / CGC__NFDBITS] &= ~(1 << (b & (CGC__NFDBITS - 1))))

#define CGC_FD_ISSET(b, set) \
    ((set)->_fd_bits[b / CGC__NFDBITS] & (1 << (b & (CGC__NFDBITS - 1))))

struct cgc_timeval {
    int tv_sec;
    int tv_usec;
};

#define CGC_EBADF 1
#define CGC_EFAULT 2
#define CGC_EINVAL 3
#define CGC_ENOMEM 4
#define CGC_ENOSYS 5
#define CGC_EPIPE 6

#ifndef LIBCGC_IMPL
# define FD_SETSIZE CGC_FD_SETSIZE
# define _NFDBITS CGC__NFDBITS
# define FD_ZERO CGC_FD_ZERO
# define FD_SET CGC_FD_SET
# define FD_CLR CGC_FD_CLR
# define FD_ISSET CGC_FD_ISSET

# define EBADF CGC_EBADF
# define EFAULT CGC_EFAULT
# define EINVAL CGC_EINVAL
# define ENOMEM CGC_ENOMEM
# define ENOSYS CGC_ENOSYS
# define EPIPE CGC_EPIPE
#endif

void _terminate(unsigned int status) __attribute__((__noreturn__));
int transmit(int fd, const void *buf, cgc_size_t count, cgc_size_t *tx_bytes);
int receive(int fd, void *buf, cgc_size_t count, cgc_size_t *rx_bytes);
int cgc_fdwait(int nfds, cgc_fd_set *readfds, cgc_fd_set *writefds,
               const struct cgc_timeval *timeout, int *readyfds);
int allocate(cgc_size_t length, int is_X, void **addr);
int deallocate(void *addr, cgc_size_t length);
int cgc_random(void *buf, cgc_size_t count, cgc_size_t *rnd_bytes);

typedef struct { long _b[8]; } jmp_buf[1];
int setjmp(jmp_buf) __attribute__((__returns_twice__));
void longjmp(jmp_buf, int) __attribute__((__noreturn__));

float sinf(float); double sin(double); long double sinl(long double);
float cosf(float); double cos(double); long double cosl(long double);
float tanf(float); double tan(double); long double tanl(long double);
float logf(float); double log(double); long double logl(long double);
float rintf(float); double rint(double); long double rintl(long double);
float sqrtf(float); double sqrt(double); long double sqrtl(long double);
float fabsf(float); double fabs(double); long double fabsl(long double);
float log2f(float); double log2(double); long double log2l(long double);
float exp2f(float); double exp2(double); long double exp2l(long double);
float expf(float); double exp(double); long double expl(long double);
float log10f(float); double log10(double); long double log10l(long double);
float powf(float, float);
double pow(double, double);
long double powl(long double, long double);
float atan2f(float, float);
double atan2(double, double);
long double atan2l(long double, long double);
float remainderf(float, float);
double remainder(double, double);
long double remainderl(long double, long double);
float scalbnf(float, int);
double scalbn(double, int);
long double scalbnl(long double, int);
float scalblnf(float, long int);
double scalbln(double, long int);
long double scalblnl(long double, long int);
float significandf(float);
double significand(double);
long double significandl(long double);

#endif /* _LIBCGC_H */