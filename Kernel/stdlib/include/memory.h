#pragma once

#define memset(dst, v, s) _memset(dst, v, s)
#define memcpy(dst, src, s) _memcpy(dst, src, s)

extern void _memset(void* _dst, unsigned char _value, unsigned int _size);
extern void _memcpy(void* _dst, const void* const _src, unsigned int _size);
