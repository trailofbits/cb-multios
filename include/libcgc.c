//#include <unistd.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <errno.h>
#include <libcgc.h>
#include <stdlib.h>
#if 0
void _terminate(unsigned int status) __attribute__((__noreturn__));
int transmit(int fd, const void *buf, size_t count, size_t *tx_bytes);
int receive(int fd, void *buf, size_t count, size_t *rx_bytes);
int fdwait(int nfds, cgc_fd_set *readfds, cgc_fd_set *writefds,
	   const struct cgc_timeval *timeout, int *readyfds);
int allocate(size_t length, int is_X, void **addr);
int deallocate(void *addr, size_t length);
int random(void *buf, size_t count, size_t *rnd_bytes);
#endif

extern void exit(int status);
extern ssize_t write(int fildes, const void *buf, size_t nbyte);
extern ssize_t read(int fildes, void *buf, size_t nbyte);
extern ssize_t select(int nfds, cgc_fd_set *readfds, cgc_fd_set *writefds, cgc_fd_set *exceptfds, const struct cgc_timeval *timeout);
extern void *mmap(void *addr, size_t len, int prot, int flags, int fildes, ssize_t off); 
extern int munmap(void *addr, size_t length);
extern void *memcpy(void *dest, const void *src, size_t n);
extern long int random(void);
extern int open(const char *filename, const char *mode);
extern int close(int fildes);

#ifdef APPLE
    extern int errno;
#elif LINUX
    #include <errno.h>
#endif 
    
#define NULL 0
typedef struct {
        unsigned char   *_ptr;
        int     _cnt;
        unsigned char   *_base;
        unsigned char   *_bufendp;
        short   _flag;
        short   _file;
        int     __stdioid;
        char    *__newbase;
        long    _unused[1];
} FILE;


void _terminate(unsigned int status)
{
    exit(status);
}

int transmit(int fd, const void *buf, size_t count, size_t *tx_bytes)
{
    ssize_t num_written = 0;

    num_written = write(fd, buf, count);

    if (num_written < 0)
        return errno;

    if (tx_bytes)
        *tx_bytes = num_written;

    return 0;
}

int receive(int fd, void *buf, size_t count, size_t *rx_bytes)
{
    ssize_t num_read = 0;

    num_read = read(fd, buf, count);

    if (num_read < 0)
        return errno;

    if (rx_bytes)
        *rx_bytes = num_read;

    return 0;
}

int cgc_fdwait(int nfds, cgc_fd_set *readfds, cgc_fd_set *writefds, const struct cgc_timeval *timeout, int *readyfds)
{
    ssize_t num_fd = 0;

    num_fd = select(nfds, readfds, writefds, NULL, timeout);

    if (num_fd < 0)
        return errno;

    if (readyfds)
        *readyfds = num_fd;

    return 0;
}

int allocate(size_t length, int is_X, void **addr)
{
    void *mem_return = NULL;
    const int MAP_PRIVATE  =  0x0002;
    const int MAP_ANON     =  0x1000;

    const int PROT_READ    =  0x01;
    const int PROT_WRITE   =  0x02;
    const int PROT_EXEC    =  0x04;

    const void *MAP_FAILED = (void *)-1;

    unsigned int prot = PROT_READ | PROT_WRITE;
    if (is_X)
        prot |= PROT_EXEC;
    mem_return = mmap(NULL, length, prot, MAP_ANON | MAP_PRIVATE, 0, 0);
    if (mem_return == MAP_FAILED)
        return errno;
    *addr = mem_return;
    return 0;
}

int deallocate(void *addr, size_t length)
{

    ssize_t mun_return = 0;
    mun_return =  munmap( addr, length);

    if (mun_return < 0)
        return errno;

    return 0;

}

int cgc_random(void *buf, size_t count, size_t *rnd_bytes)
{
    if (count == 0)
        return 0;
    if (count > SSIZE_MAX)
        return NULL; //??? unspecified

    int numRead;

    int fp;
    fp = open("/dev/urandom", 0); //0 for rdonly
    numRead = read(fp, buf, count);
    close(fp);

    // FILE * fp;                               //didn't work 
    // fp = fopen("/dev/urandom", "r");
    // numRead = fread(buf, 1, count, fp);
    // fclose(fp);
    
    if (numRead < count){
        return errno;
    }
    if (rnd_bytes)
        *rnd_bytes = numRead;
    return 0;
}




