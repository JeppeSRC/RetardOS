#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <stdarg.h>

#define MAX_FPRINT_SIZE (20 * 80)

static unsigned char textColor = _TEXT_ATTRIB_COLOR_FWHITE;

static unsigned int xCursor = 0;
static unsigned int yCursor = 0;

void _setTextColor(unsigned char color) {
	textColor = color;
}

void _fillBackGround(unsigned char col) {
	volatile char* video = (char*)0xB8000;

	for (unsigned int i = 0; i < (80 * 25) * 2; i+=2) {
		video[i + 1] = (col & 0b11110000) | (textColor & 0b00001111);
	}
}

void _print(const char* _string) {
	_print(_string, _strlen(_string));
}
// "ABC"
void _print(const char* _string, unsigned int _len) {
	volatile char* video = (char*)0xB8000;
	for (unsigned int i = 0; i < _len; i++) {
		if (xCursor >= 80) {
			xCursor = 0;
			yCursor++;
		}

		if (_string[i] == '\n') {
			xCursor = 0;
			yCursor++;
			continue;
		}

		if (yCursor >= 25) {
			xCursor = 0;
			yCursor = 0;
			_clr();
		}

		unsigned int index = (xCursor + yCursor * 80) * 2;
		video[index + 0] = _string[i];
		video[index + 1] = textColor;

		xCursor++;
	}

	xCursor--;
}

void _clr() {
	char* video = (char*)0xB8000;
	memset(video, 0, 25 * 80 * 2);
}

void _printf(const char* _format...) {
	va_list args;
	va_start(args, _format);

	_vprintf(_format, args);
}

void _vprintf(const char* _format, va_list args) {
	char tmp[MAX_FPRINT_SIZE];

	unsigned int printed = _vsprintf(tmp, _format, args);
	_print(tmp, printed);
}

void _setCursor(unsigned int x, unsigned int y) {
	xCursor = x;
	yCursor = y;
}
