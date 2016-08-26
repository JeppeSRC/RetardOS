#include "string.h"
#include "stdio.h"
#include "math64.h"

uint32 _strlen(const char* _string) {
	uint32 res = 0;

	while (_string[res++] != '\0');
	
	return res;
}

bool _strcmp(const char* _string1, const char* _string2) {
	uint32 len1 = _strlen(_string1);
	uint32 len2 = _strlen(_string2);

	if (len1 != len2) return false;

	for (uint32 i = 0; i < len1; i++) {
		if (_string1[i] != _string2[i]) return false;
	}

	return true;
}

const char chars[]{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

uint32 _sprintf(char* _buff, const char* _format...) {	
	va_list args;
	va_start(args, _format);

	return _vsprintf(_buff, _format, args);
}

uint32 _vsprintf(char* _buff, const char* _format, va_list args) {
	uint32 len = _strlen(_format);
	uint32 printed = 0;

	char tmp[21];

	uint32 tmplen = 0;
	uint64 value = 0;

	for (uint32 i = 0; i < len; i++) {
		if (_format[i] == '%') {
			i++;
			switch (_format[i]) {
				case 'c':
				case 'C':

					_buff[printed++] = va_arg(args, char);

					break;

				case 'h':

					memset(tmp, 0, 11);

					_uint32ToString(va_arg(args, uint32), 16, tmp);

					memcpy(_buff + printed, tmp, 8);

					printed += 8;
					break;

				case 'H':

					memset(tmp, 0, 17);

					_uint64ToString(va_arg(args, uint64), 16, tmp);

					memcpy(_buff + printed, tmp, 16);

					printed += 16;
				
					break;

				case 'u':

					memset(tmp, 0, 11);

					tmplen = 1;
					value = va_arg(args, uint32);

					if (value != 0) {
						tmplen = _uint32ToString((uint32)(value & 0xFFFFFFFF), 10, tmp);
					} else {
						tmp[0] = '0';
					}

					memcpy(_buff + printed, tmp, tmplen);

					printed += tmplen;
					break;

				case 'U':

					memset(tmp, 0, 21);

					tmplen = 1;
					value = va_arg(args, uint64);

					if (value != 0) {
						tmplen = _uint64ToString(value, 10, tmp);
					} else {
						tmp[0] = '0';
					}

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


uint32 _uint32ToString(uint32 _v, uint32 _base, char* _buff) {
	uint32 num = 0;

	while (_v > 0) {
		if (num >= 10) break;
		_buff[num++] = chars[_v % _base];
		_v /= _base;
	}

	char tmp[11];
	memcpy(tmp, _buff, 11);

	uint32 start = 0;

	if (_base == 16) {
		memset(_buff, '0', 8);
		start = 8 - num;
	}

	for (uint32 i = 0; i < num; i++) {
		_buff[start + i] = tmp[num - i - 1];
	}

	return num;
}

uint32 _uint64ToString(uint64 _v, uint32 _base, char * _buff) {
	uint32 num = 0;
	
	uint32 rem = 0;

	while (_v > 0) {
		if (num >= 20) break;
		_v = uint64div(_v, _base, &rem);
		_buff[num++] = chars[rem];
	}
	
	char tmp[21];
	memcpy(tmp, _buff, 21);

	uint32 start = 0;

	if (_base == 16) {
		memset(_buff, '0', 16);
		start = 16 - num;
	}

	for (uint32 i = 0; i < num; i++) {
		_buff[start + i] = tmp[num - i - 1];
	}

	return num;
}
