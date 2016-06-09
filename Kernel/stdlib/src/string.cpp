#include <string.h>
#include <stdio.h>

unsigned int _strlen(const char* _string) {
	unsigned int res = 0;

	while (_string[res++] != '\0');
	
	return res;
}

bool _strcmp(const char* _string1, const char* _string2) {
	unsigned int len1 = _strlen(_string1);
	unsigned int len2 = _strlen(_string2);

	if (len1 != len2) return false;

	for (unsigned int i = 0; i < len1; i++) {
		if (_string1[i] != _string2[i]) return false;
	}

	return true;
}

const char chars[]{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

unsigned int _sprintf(char* _buff, const char* _format...) {	
	va_list args;
	va_start(args, _format);

	return _vsprintf(_buff, _format, args);
}

unsigned int _vsprintf(char* _buff, const char* _format, va_list args) {
	unsigned int len = _strlen(_format);
	unsigned int printed = 0;

	char tmp[11];

	for (unsigned int i = 0; i < len; i++) {
		if (_format[i] == '%') {
			i++;
			switch (_format[i]) {
				case 'c':
				case 'C':

					_buff[printed++] = va_arg(args, char);

					break;

				case 'h':
				case 'H':

					memset(tmp, 0, 11);

					_uintToString(va_arg(args, unsigned int), 16, tmp);

					memcpy(_buff + printed, tmp, 8);

					printed += 8;
					break;

				case 'u':
				case 'U':

					memset(tmp, 0, 11);

					unsigned int tmplen = _uintToString(va_arg(args, unsigned int), 10, tmp);

					memcpy(_buff + printed, tmp, tmplen);

					printed += tmplen;
					break;
			}
		} else {
			_buff[printed++] = _format[i];
		}

	end:
		int a = 0;
	}

	return printed;
}


unsigned int _uintToString(unsigned int _v, unsigned int _base, char* _buff) {
	unsigned int num = 0;

	while (_v > 0) {
		if (num >= 10) break;
		_buff[num++] = chars[_v % _base];
		_v /= _base;
	}

	char tmp[11];
	memcpy(tmp, _buff, 11);

	unsigned int start = 0;

	if (_base == 16) {
		memset(_buff, '0', 8);
		start = 8 - num;
	}

	for (unsigned int i = 0; i < num; i++) {
		_buff[start + i] = tmp[num - i - 1];
	}

	return num;
}

