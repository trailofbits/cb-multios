#ifndef STRING_H
#define STRING_H

#include "libcgc.h"
#include "cgc_inttypes.h"

cgc_size_t cgc_strncpy(char* dst, cgc_size_t len, const char* src);

cgc_size_t cgc_strcpy(char* dst, const char* src);

int cgc_strcmp(const char* l, const char* r);

char* cgc_strstr(char* haystack, const char* needle);

char* cgc_strchr(char* haystack, char needle);

char* cgc_strrstr(char* haystack, const char* needle);

char* cgc_strrchr(char* haystack, char needle);

cgc_size_t cgc_strlen(const char* str);

uint32_t cgc_strToUint32(const char* str);
#endif//STRING_H
