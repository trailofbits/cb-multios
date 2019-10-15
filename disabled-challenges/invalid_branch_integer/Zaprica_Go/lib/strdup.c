#include "cgc_stdlib.h"
#include "cgc_string.h"

char *cgc_strdup(const char *str)
{
    cgc_size_t n = cgc_strlen(str) + 1;
    char *dup = cgc_malloc(n);
    if (dup == NULL)
        return NULL;
    cgc_memcpy(dup, str, n);
    return dup;
}
