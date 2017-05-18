#ifndef __IO_H
#define __IO_H

#define CLIENT_TO_SERVER_IN 3
#define CLIENT_TO_SERVER_OUT 4
#define SERVER_TO_CLIENT_IN 5
#define SERVER_TO_CLIENT_OUT 6

int cgc_send_n_bytes(int fd, cgc_size_t n, char* buf);
int cgc_read_n_bytes(int fd, cgc_size_t n, char* buf);
int cgc_read_until(int fd, cgc_size_t n, char terminator, char* buf);
int cgc_transmit_string(int fd, char* buf);

#ifdef DEBUG
  #define dbg(s, ...) fdprintf(STDERR, "DEBUG %s:%d:\t" s "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
  #define dbg(s, ...)
#endif

#define err(s, ...) \
({ \
  fdprintf(STDERR, "ERROR %s:%d:\t" s "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
  cgc_exit(1); \
})

#endif
