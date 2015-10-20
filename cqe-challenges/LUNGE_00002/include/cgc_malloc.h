#ifndef CGC_MALLOC_H
#define CGC_MALLOC_H

void *calloc(size_t nmemb, size_t size);
void  free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
#endif
