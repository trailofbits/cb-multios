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

// This is for challenges that define C++ operators and need to know std::size_t
#if defined(APPLE) || defined(__LP64__) || defined(_LP64)
# define STD_SIZE_T unsigned long
#else
# define STD_SIZE_T unsigned int
#endif

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

void *cgc_initialize_secret_page(void);

// All of the following functions are defined in asm (maths.S)
// The asm symbols are being forced to match maths.S keep compatibility across OS's
// (no leading underscores on Windows/OS X)

typedef struct { long _b[8]; } jmp_buf[1];
extern int setjmp(jmp_buf) __asm__("setjmp") __attribute__((__returns_twice__));
extern void longjmp(jmp_buf, int) __asm__("longjmp") __attribute__((__noreturn__));

extern float sinf(float) __asm__("sinf");     extern double sin(double) __asm__("sin");     extern long double sinl(long double) __asm__("sinl");
extern float cosf(float) __asm__("cosf");     extern double cos(double) __asm__("cos");     extern long double cosl(long double) __asm__("cosl");
extern float tanf(float) __asm__("tanf");     extern double tan(double) __asm__("tan");     extern long double tanl(long double) __asm__("tanl");
extern float logf(float) __asm__("logf");     extern double log(double) __asm__("log");     extern long double logl(long double) __asm__("logl");
extern float rintf(float) __asm__("rintf");   extern double rint(double) __asm__("rint");   extern long double rintl(long double) __asm__("rintl");
extern float sqrtf(float) __asm__("sqrtf");   extern double sqrt(double) __asm__("sqrt");   extern long double sqrtl(long double) __asm__("sqrtl");
extern float fabsf(float) __asm__("fabsf");   extern double fabs(double) __asm__("fabs");   extern long double fabsl(long double) __asm__("fabsl");
extern float log2f(float) __asm__("log2f");   extern double log2(double) __asm__("log2");   extern long double log2l(long double) __asm__("log2l");
extern float exp2f(float) __asm__("exp2f");   extern double exp2(double) __asm__("exp2");   extern long double exp2l(long double) __asm__("exp2l");
extern float expf(float) __asm__("expf");     extern double exp(double) __asm__("exp");     extern long double expl(long double) __asm__("expl");

extern float log10f(float) __asm__("log10f"); extern double log10(double) __asm__("log10"); extern long double log10l(long double) __asm__("log10l");
extern float powf(float, float) __asm__("powf");
extern double pow(double, double) __asm__("pow");
extern long double powl(long double, long double) __asm__("powl");
extern float atan2f(float, float) __asm__("atan2f");
extern double atan2(double, double) __asm__("atan2");
extern long double atan2l(long double, long double) __asm__("atan2l");
extern float remainderf(float, float) __asm__("remainderf");
extern double remainder(double, double) __asm__("remainder");
extern long double remainderl(long double, long double) __asm__("remainderl");
extern float scalbnf(float, int) __asm__("scalbnf");
extern double scalbn(double, int) __asm__("scalbn");
extern long double scalbnl(long double, int) __asm__("scalbnl");
extern float scalblnf(float, long int) __asm__("scalblnf");
extern double scalbln(double, long int) __asm__("scalbln");
extern long double scalblnl(long double, long int) __asm__("scalblnl");
extern float significandf(float) __asm__("significandf");
extern double significand(double) __asm__("significand");
extern long double significandl(long double) __asm__("significandl");

#endif /* _LIBCGC_H */
