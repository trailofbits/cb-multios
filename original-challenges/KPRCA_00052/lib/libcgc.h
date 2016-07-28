#ifndef _LIBCGC_H
#define _LIBCGC_H

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#undef NULL
#define	NULL 0

typedef long unsigned int size_t;
typedef long signed int ssize_t;

#define SSIZE_MAX	2147483647
#define SIZE_MAX	4294967295
#define	FD_SETSIZE	1024

typedef long int _fd_mask;

#define	_NFDBITS (8 * sizeof(_fd_mask))

typedef struct {
	_fd_mask _fd_bits[FD_SETSIZE / _NFDBITS];
} fd_set;

#define	FD_ZERO(set)							\
	do {								\
		int __i;						\
		for (__i = 0; __i < (FD_SETSIZE / _NFDBITS); __i++)	\
			(set)->_fd_bits[__i] = 0;				\
	} while (0)
#define	FD_SET(b, set) \
	((set)->_fd_bits[b / _NFDBITS] |= (1 << (b & (_NFDBITS - 1))))
#define	FD_CLR(b, set) \
	((set)->_fd_bits[b / _NFDBITS] &= ~(1 << (b & (_NFDBITS - 1))))
#define	FD_ISSET(b, set) \
	((set)->_fd_bits[b / _NFDBITS] & (1 << (b & (_NFDBITS - 1))))

struct timeval {
	int tv_sec;
	int tv_usec;
};

#define	EBADF		1
#define	EFAULT		2
#define	EINVAL		3
#define	ENOMEM		4
#define	ENOSYS		5
#define	EPIPE		6

void _terminate(unsigned int status) __attribute__((__noreturn__));
int transmit(int fd, const void *buf, size_t count, size_t *tx_bytes);
int receive(int fd, void *buf, size_t count, size_t *rx_bytes);
int fdwait(int nfds, fd_set *readfds, fd_set *writefds,
	   const struct timeval *timeout, int *readyfds);
int allocate(size_t length, int is_X, void **addr);
int deallocate(void *addr, size_t length);
int random(void *buf, size_t count, size_t *rnd_bytes);

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
