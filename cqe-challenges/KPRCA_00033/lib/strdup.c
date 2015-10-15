#include <stdlib.h>
#include <string.h>

char *strdup(const char *str)
{
    size_t n = cgc_strlen(str) + 1;
    char *dup = malloc(n);
    if (dup == NULL)
        return NULL;
    cgc_memcpy(dup, str, n);
    return dup;
}
