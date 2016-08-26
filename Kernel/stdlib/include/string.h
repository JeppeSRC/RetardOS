#pragma once
#include "stddef.h"
#include "stdarg.h"
#include "memory.h"

uint32		_strlen(const char* _string);
bool		_strcmp(const char* _string1, const char* _string2);
uint32		_sprintf(char* _buff, const char* _format...);
uint32		_vsprintf(char* _buff, const char* _format, va_list args);

uint32		_uint32ToString(uint32 _v, uint32 _base, char* _buff);
uint32		_uint64ToString(uint64 _v, uint32 _base, char* _buff);