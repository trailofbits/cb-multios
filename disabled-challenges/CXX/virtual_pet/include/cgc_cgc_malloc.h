#ifndef CGC_MALLOC_H
#define CGC_MALLOC_H

void *cgc_calloc(cgc_size_t nmemb, cgc_size_t size);
void  cgc_free(void *ptr);
void *cgc_malloc(cgc_size_t size);
void *realloc(void *ptr, cgc_size_t size);
#endif
