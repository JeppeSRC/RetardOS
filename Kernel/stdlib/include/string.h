#pragma once
#include <stdarg.h>
#include "memory.h"



extern unsigned int		_strlen(const char* _string);
extern bool				_strcmp(const char* _string1, const char* _string2);
extern unsigned int		_sprintf(char* _buff, const char* _format...);
extern unsigned int		_vsprintf(char* _buff, const char* _format, va_list args);

extern unsigned int		_uintToString(unsigned int _v, unsigned int _base, char* _buff);