/* Copyright 2015 Peter Goodman (peter@trailofbits.com), all rights reserved. */

#define LIBCGC_IMPL
#include "libcgc.h"
#include "ansi_x931_aes128.h"

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/types.h>
#include <unistd.h>
#include <err.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) < (b)) ? (b) : (a))

/* Terminates the process. */
void _terminate(unsigned int status) {
  exit(status);
  __builtin_unreachable();
}

/* Transmits data from one CGC process to another. */
int transmit(int fd, const void *buf, cgc_size_t count, cgc_size_t *tx_bytes) {
  const cgc_ssize_t ret = write(fd, buf, count);

  if (ret < 0) {
    return errno;
  } else {
    *tx_bytes = ret;
    return 0;
  }
}

/* Receives data from another CGC process. */
int receive(int fd, void *buf, cgc_size_t count, cgc_size_t *rx_bytes) {
  const cgc_ssize_t ret = read(fd, buf, count);

  if (ret < 0) {
    return errno;
  } else {
    *rx_bytes = ret;
    return 0;
  }
}

/* Tries to validate a timeout. */
static int check_timeout(const struct cgc_timeval *timeout) {
  if (!timeout) {
    return 0;
  } else if (0 > timeout->tv_sec || 0 > timeout->tv_usec) {
    return CGC_EINVAL;
  } else {
    return 0;
  }
}

enum {
    // Maximum number of binaries running for one challenge
    kPracticalMaxNumCBs = 10,

    // STD(IN/OUT/ERR) + a socketpair for every binary
    // All fds used by the binaries should be less than this
    kExpectedMaxFDs = 3 + (2 * kPracticalMaxNumCBs)
};

/* Marshal a CGC fd set into an OS fd set. */
static int copy_cgc_fd_set(const cgc_fd_set *cgc_fds, fd_set *os_fds, int *num_fds) {
  for (unsigned fd = 0; fd < CGC__NFDBITS; ++fd) {
    if (CGC_FD_ISSET(fd, cgc_fds)) {
      // Shouldn't be using an fd greater than the allowed values
      if (fd >= kExpectedMaxFDs) {
          return CGC_EBADF;
      }

      if (fd > NFDBITS) {
        continue;  /* OS set size is too small. */
      }
      FD_SET(fd, os_fds);
      ++*num_fds;
    }
  }
  return 0;
}

/* Marshal an OS fd set into a CGC fd set. */
static void copy_os_fd_set(const fd_set *os_fds, cgc_fd_set *cgc_fds) {
  for (unsigned fd = 0; fd < MIN(NFDBITS, CGC__NFDBITS); ++fd) {
    if (FD_ISSET(fd, os_fds)) {
      CGC_FD_SET(fd, cgc_fds);
    }
  }
}
int cgc_fdwait(int nfds, cgc_fd_set *readfds, cgc_fd_set *writefds,
               const struct cgc_timeval *timeout, int *readyfds) {

  int ret = check_timeout(timeout);
  int actual_num_fds = 0;
  struct timeval max_wait_time = {0, 0};
  fd_set read_fds;
  fd_set write_fds;

  if (ret) {
    return ret;
  } else if (0 > nfds || CGC__NFDBITS < nfds) {
    return EINVAL;
  }

  FD_ZERO(&read_fds);
  FD_ZERO(&write_fds);

  if (readfds) {
    if (0 != (ret = copy_cgc_fd_set(readfds, &read_fds, &actual_num_fds))) {
      return ret;
    }
  }

  if (writefds) {
    if (0 != (ret = copy_cgc_fd_set(writefds, &write_fds, &actual_num_fds))) {
      return ret;
    }
  }

  if (actual_num_fds != nfds) {
    return EINVAL;  /* Not actually specified, but oh well. */
  }

  if (readfds)  CGC_FD_ZERO(readfds);
  if (writefds) CGC_FD_ZERO(writefds);

  if (timeout) {
    max_wait_time.tv_sec = timeout->tv_sec;
    max_wait_time.tv_usec = timeout->tv_usec;
  }

  errno = 0;
  int num_selected_fds = select(
          nfds,
          (readfds ? &read_fds : NULL),
          (writefds ? &write_fds : NULL),
          NULL,
          (timeout ? &max_wait_time : NULL));
  const int errno_val = errno;
  errno = 0;

  if (errno_val) {
    if (ENOMEM == errno_val) {
      return CGC_ENOMEM;
    } else if (EBADF == errno_val) {
      return CGC_EBADF;
    } else {
      return CGC_EINVAL;
    }
  }

  if (readfds) {
    copy_os_fd_set(&read_fds, readfds);
  }

  if (writefds) {
    copy_os_fd_set(&write_fds, writefds);
  }

  if (readyfds) {
    *readyfds = num_selected_fds;
  }

  return 0;
}

#define PAGE_ALIGN(x) (((x) + (PAGE_SIZE - 1)) & ~(PAGE_SIZE - 1))

/* Going to ignore `is_executable`. It's not really used in the official CGC
 * challenges, and if it were used, then JITed code would likely be 32-bit, and
 * ideally, this code will also work on 64-bit.
 */
int allocate(cgc_size_t length, int is_executable, void **addr) {
  int page_perms = PROT_READ | PROT_WRITE;
  if (is_executable)
    page_perms |= PROT_EXEC;

  void *return_address = mmap(NULL, length, page_perms, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0);

  if (return_address == MAP_FAILED) {
    return errno;
  }

  *addr = return_address;
  memset(return_address, 0, length);

  return 0;
}

/* Deallocate some range of memory and mark the pages as free. */
int deallocate(void *addr, cgc_size_t length) {

  const int ret = munmap(addr, length);

  if (ret < 0) {
    return errno;
  }

  return 0;
}


cgc_prng *cgc_internal_prng = NULL;
/**
 * Initializes the prng for use with cgc_random and the secret page
 */
void try_init_prng() {
    // Don't reinitialize
    if (cgc_internal_prng != NULL) return;

    // This will be hex encoded
    const char *prng_seed_hex = getenv("seed");
    if (prng_seed_hex == NULL || strlen(prng_seed_hex) != (BLOCK_SIZE * 3) * 2) {
        // TODO: Actually make this random
        prng_seed_hex = "736565647365656473656564736565643031323334353637383961626364656600000000000000000000000000000000";
    }

    // Convert the hex encoded seed to a normal string
    const char *pos = prng_seed_hex;
    uint8_t prng_seed[BLOCK_SIZE * 3];
    for(int i = 0; i < BLOCK_SIZE * 3; ++i) {
        sscanf(pos, "%2hhx", &prng_seed[i]);
        pos += 2;
    }

    // Create the prng
    cgc_internal_prng = (cgc_prng *) malloc(sizeof(cgc_prng));
    cgc_aes_state *seed = (cgc_aes_state *) prng_seed;
    cgc_init_prng(cgc_internal_prng, seed);
}

int cgc_random(void *buf, cgc_size_t count, cgc_size_t *rnd_bytes) {
    // Get random bytes from the prng
    try_init_prng();
    cgc_aes_get_bytes(cgc_internal_prng, count, buf);
    *rnd_bytes = count;
    return 0;
}

void *cgc_initialize_secret_page(void) {
  const void * MAGIC_PAGE_ADDRESS = (void *)0x4347C000;
  const size_t MAGIC_PAGE_SIZE = 4096;

  void *mmap_addr = mmap(MAGIC_PAGE_ADDRESS, MAGIC_PAGE_SIZE,
                         PROT_READ | PROT_WRITE,
                         MAP_FIXED | MAP_PRIVATE | MAP_ANONYMOUS,
                         -1, 0);

  if (mmap_addr != MAGIC_PAGE_ADDRESS) {
    err(1, "[!] Failed to map the secret page");
  }

  // Fill the magic page with bytes from the prng
  try_init_prng();
  cgc_aes_get_bytes(cgc_internal_prng, MAGIC_PAGE_SIZE, mmap_addr);

  return mmap_addr;
}
