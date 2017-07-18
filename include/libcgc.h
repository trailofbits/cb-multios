#ifndef _LIBCGC_H
#define _LIBCGC_H

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#ifdef NULL
# undef NULL
#endif
#define NULL (0)

#ifdef WIN
# define __attribute__(x)
# define __builtin_isnan _isnan
# define __builtin_isinf(x) (! _finite(x))
#endif

typedef unsigned long cgc_size_t;
typedef long cgc_ssize_t;

// This is for challenges that define C++ operators and need to know std::size_t
#if defined(APPLE) || defined(__LP64__) || defined(_LP64)
# define STD_SIZE_T unsigned long
#else
# define STD_SIZE_T unsigned int
#endif

#ifndef PAGE_SIZE
# define PAGE_SIZE 4096
#endif

#ifndef CGC_FLAG_PAGE_ADDRESS
# define CGC_FLAG_PAGE_ADDRESS 0x4347C000
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

#ifdef LIBCGC_IMPL
// Maximum number of binaries running for one challenge
# define MAX_NUM_CBS 10

// STD(IN/OUT/ERR) + a socketpair for every binary
// All fds used by the binaries should be less than this
# define EXPECTED_MAX_FDS 3 + (2 * MAX_NUM_CBS)

int cgc_check_timeout(const struct cgc_timeval *timeout) {
    if (!timeout) {
        return 0;
    } else if (0 > timeout->tv_sec || 0 > timeout->tv_usec) {
        return CGC_EINVAL;
    } else {
        return 0;
    }
}
#endif

void cgc__terminate(unsigned int status) __attribute__((__noreturn__));
int cgc_transmit(int fd, const void *buf, cgc_size_t count, cgc_size_t *tx_bytes);
int cgc_receive(int fd, void *buf, cgc_size_t count, cgc_size_t *rx_bytes);
int cgc_fdwait(int nfds, cgc_fd_set *readfds, cgc_fd_set *writefds,
               const struct cgc_timeval *timeout, int *readyfds);
int cgc_allocate(cgc_size_t length, int is_X, void **addr);
int cgc_deallocate(void *addr, cgc_size_t length);
int cgc_random(void *buf, cgc_size_t count, cgc_size_t *rnd_bytes);

// All of the following functions are defined in asm (maths.S/maths_win.asm)

typedef struct { long _b[8]; } jmp_buf[1];
extern int cgc_setjmp(jmp_buf) __attribute__((__returns_twice__));
extern void cgc_longjmp(jmp_buf, int) __attribute__((__noreturn__));

extern float cgc_sinf(float);   extern double cgc_sin(double);   extern long double cgc_sinl(long double);
extern float cgc_cosf(float);   extern double cgc_cos(double);   extern long double cgc_cosl(long double);
extern float cgc_tanf(float);   extern double cgc_tan(double);   extern long double cgc_tanl(long double);
extern float cgc_logf(float);   extern double cgc_log(double);   extern long double cgc_logl(long double);
extern float cgc_rintf(float);  extern double cgc_rint(double);  extern long double cgc_rintl(long double);
extern float cgc_sqrtf(float);  extern double cgc_sqrt(double);  extern long double cgc_sqrtl(long double);
extern float cgc_fabsf(float);  extern double cgc_fabs(double);  extern long double cgc_fabsl(long double);
extern float cgc_log2f(float);  extern double cgc_log2(double);  extern long double cgc_log2l(long double);
extern float cgc_exp2f(float);  extern double cgc_exp2(double);  extern long double cgc_exp2l(long double);
extern float cgc_expf(float);   extern double cgc_exp(double);   extern long double cgc_expl(long double);
extern float cgc_log10f(float); extern double cgc_log10(double); extern long double cgc_log10l(long double);

extern float cgc_powf(float, float);
extern double cgc_pow(double, double);
extern long double cgc_powl(long double, long double);
extern float cgc_atan2f(float, float);
extern double cgc_atan2(double, double);
extern long double cgc_atan2l(long double, long double);
extern float cgc_remainderf(float, float);
extern double cgc_remainder(double, double);
extern long double cgc_remainderl(long double, long double);
extern float cgc_scalbnf(float, int);
extern double cgc_scalbn(double, int);
extern long double cgc_scalbnl(long double, int);
extern float cgc_scalblnf(float, long int);
extern double cgc_scalbln(double, long int);
extern long double cgc_scalblnl(long double, long int);
extern float cgc_significandf(float);
extern double cgc_significand(double);
extern long double cgc_significandl(long double);

#endif /* _LIBCGC_H */
