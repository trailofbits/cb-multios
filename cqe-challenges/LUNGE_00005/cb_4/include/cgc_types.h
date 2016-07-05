#ifndef _TYPES_H
#define _TYPES_H

typedef __builtin_va_list va_list;
#define va_start(v,l)   __builtin_va_start(v,l)
#define va_end(v)   __builtin_va_end(v)
#define va_arg(v,l) __builtin_va_arg(v,l)

// typedef __SIZE_TYPE__ size_t;
// typedef signed long ssize_t;
// #define NULL 0

#endif /* _TYPES_H */
