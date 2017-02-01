#define LIBCGC_IMPL
#include "libcgc.h"
#include "ansi_x931_aes128.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) < (b)) ? (b) : (a))

/* Terminates the process. */
void _terminate(unsigned int status) {
  exit(status);
}

int transmit(int fd, const void *buf, cgc_size_t count, cgc_size_t *tx_bytes) {
    cgc_size_t ret = _write(fd, buf, count);

    if (ret < 0) {
        return errno;
    } else if (tx_bytes != NULL) {
        *tx_bytes = ret;
    }

    return 0;
}

int receive(int fd, void *buf, cgc_size_t count, cgc_size_t *rx_bytes) {
    cgc_size_t ret = _read(fd, buf, count);

    if (ret < 0) {
        return errno;
    } else if (rx_bytes != NULL) {
        *rx_bytes = ret;
    }

    return 0;
}

int cgc_fdwait(int nfds, cgc_fd_set *readfds, cgc_fd_set *writefds,
               const struct cgc_timeval *timeout, int *readyfds) {
    return 0;
}

int allocate(cgc_size_t length, int is_executable, void **addr) {
    DWORD prot = is_executable ? PAGE_EXECUTE_READWRITE : PAGE_READWRITE;

    LPVOID ret_addr = VirtualAlloc(NULL, length, MEM_COMMIT | MEM_RESERVE, prot);
    if (ret_addr == NULL)
        return GetLastError();

    if (addr != NULL)
        *addr = ret_addr;

    return 0;
}

int deallocate(void *addr, cgc_size_t length) {
    if (VirtualFree(addr, length, MEM_RELEASE) == 0)
        return GetLastError();
    return 0;
}

static cgc_prng *cgc_internal_prng = NULL;
/**
 * Initializes the prng for use with cgc_random and the flag page
 */
static void try_init_prng() {
    // Don't reinitialize
    if (cgc_internal_prng != NULL) return;

    uint8_t prng_seed[BLOCK_SIZE * 3] = {
        0x73, 0x65, 0x65, 0x64, 0x73, 0x65, 0x65, 0x64, 0x73, 0x65, 0x65, 0x64,
        0x73, 0x65, 0x65, 0x64, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
        0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    }; // Default seed, definitely not random

    // This will be hex encoded
    const char *prng_seed_hex = getenv("seed");
    if (prng_seed_hex != NULL && strlen(prng_seed_hex) == (BLOCK_SIZE * 3) * 2) {
        // Convert the hex encoded seed to a normal string
        const char *pos = prng_seed_hex;
        for(int i = 0; i < BLOCK_SIZE * 3; ++i) {
            sscanf(pos, "%2hhx", &prng_seed[i]);
            pos += 2;
        }
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

    if (rnd_bytes)
      *rnd_bytes = count;

    return 0;
}

static void cgc_initialize_flag_page(void) {
    // TODO: VirtualAlloc docs say the address may be rounded down
    // May have to MEM_RESERVE to allocate a large block and MEM_COMMIT the section we want
    LPVOID flag_addr = VirtualAlloc(CGC_FLAG_PAGE_ADDRESS, PAGE_SIZE,
                                    MEM_COMMIT | MEM_RESERVE,
                                    PAGE_READWRITE);

    if (flag_addr != CGC_FLAG_PAGE_ADDRESS) {
        fprintf(stderr, "[!] Failed to map the flag page");
        exit(1);
    }

    // Fill the flag page with bytes from the prng
    try_init_prng();
    cgc_aes_get_bytes(cgc_internal_prng, PAGE_SIZE, flag_addr);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        // __attribute__((constructor))
        setvbuf(stdout, NULL, _IONBF, 0);  // We *may* not need this, not sure yet
        cgc_initialize_flag_page();
    }
    return TRUE;
}
