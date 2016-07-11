#ifndef MALLOC_INTERNAL_H_
#define MALLOC_INTERNAL_H_

#define NUM_BUCKETS 13

#define OVERHEAD_BYTES 8
#define MIN_ALLOC 32
#define MAX_ALLOC 65536 /* 64 KB */
#define SPAN_SIZE 131072 /* 128 KB */

typedef struct block {
    unsigned int size;
    unsigned int free : 1;
    unsigned int mmap : 1;
} block_t;

typedef struct free_block {
    block_t hdr;
    struct free_block *next, *prev;
} free_block_t;

typedef struct {
    free_block_t *free_list[NUM_BUCKETS];    
} malloc_t;

extern malloc_t g_malloc;

#endif /* !MALLOC_INTERNAL_H_ */
