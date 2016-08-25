#pragma once
#include "stddef.h"

#define memset(dst, v, s) _memset(dst, v, s)
#define memcpy(dst, src, s) _memcpy(dst, src, s)

extern void _memset(void* _dst, uint8 _value, uint32 _size);
extern void _memcpy(void* _dst, const void* const _src, uint32 _size);
