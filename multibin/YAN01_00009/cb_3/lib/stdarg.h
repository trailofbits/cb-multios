#ifndef STDARG_H
#define STDARG_H

typedef __builtin_va_list va_list;
#define va_start(_va_list, _param) __builtin_va_start(_va_list, _param)
#define va_end(_va_list) __builtin_va_end(_va_list)
#define va_arg(_va_list, _type) __builtin_va_arg(_va_list, _type)

#endif//STDARG_H
