#pragma once


#if defined(__cplusplus) 
extern "C" {
#endif
typedef unsigned char* va_list;


#define va_size(s) ((sizeof(s) + sizeof(int) - 1) & ~(sizeof(int) -1))

#define va_start(list, arg) ((void)(list = (va_list)(&(arg)) + va_size(arg)))
#define va_arg(list, type) (*(type*)((list += va_size(type)) - va_size(type)))
#define va_end(list) (list = (va_list)0)

#if defined(__cplusplus) 
}
#endif