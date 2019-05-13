
#include "common.h"
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <Windows.h>

void __cdecl odprintf(const char *format, ...)
{
	char buf[1024] = "[usbdisk] ";
	char *p = &buf[10];	// 和上面对应

	va_list args;
	va_start(args, format);
	p += _vsnprintf(p, sizeof(buf) - 1, format, args);
	va_end(args);

	OutputDebugString(buf);
}
