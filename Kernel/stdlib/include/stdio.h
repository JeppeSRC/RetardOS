#pragma once
#include <stdarg.h>

#define VMEMORY 0xB8000

#define _TEXT_ATTRIB_COLOR_FWHITE 0b00001111
#define _TEXT_ATTRIB_COLOR_FRED 0b00001100
#define _TEXT_ATTRIB_COLOR_FGREEN 0b00001010
#define _TEXT_ATTRIB_COLOR_FBLUE 0b00001001

#define _TEXT_ATTRIB_COLOR_BWHITE 0b01110000
#define _TEXT_ATTRIB_COLOR_BRED 0b01000000
#define _TEXT_ATTRIB_COLOR_BGREEN 0b00100000
#define _TEXT_ATTRIB_COLOR_BBLUE 0b00010000

extern void _setTextColor(unsigned char color);
extern void _fillBackGround(unsigned char color);
extern void _print(const char* _string);
extern void _print(const char* _string, unsigned int _len);
extern void _clr();

extern void _printf(const char* _format...);
extern void _vprintf(const char* _format, va_list args);

extern void _setCursor(unsigned int x, unsigned int y);
