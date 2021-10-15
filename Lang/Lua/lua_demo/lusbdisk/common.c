#define DLL_EXPORTS

#define DLL_EXPORTS
#include "usbdisk.h"

#include <Windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

#include "common.h"


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

// ---------------------------------------------------------
void dbgview_display_hex(uint8_t* buffer, uint32_t size)
{
	uint32_t i, j;
	char debug_info[256];	// 经过计算，最大长度为69字节。
	char* p;
	const uint32_t colomn = 32;

	// DWORD line;
	// 要将uchar转换为hex形式显示
	if (size == 0)
	{
		return;
	}

	p = debug_info;
	for (i = 0; i < size; i += colomn)
	{
		for (j = 0; j < colomn; j++)
		{
			if (i + j < size)
			{
				sprintf(p, "%02x", buffer[i + j]);
				p += 2;
			}
			else
			{
				sprintf(p, "  ");
				p += 2;
			}

			sprintf(p, " ");
			p += 1;
		}

		sprintf(p, "    ");
		p += 3;
		for (j = 0; j < colomn; j++)
		{
			if (i + j < size)
			{
				if ((buffer[i + j] < 32) || (buffer[i + j] > 126))
				{
					sprintf(p, ".");
					p += 1;
				}
				else
				{
					sprintf(p, "%c", buffer[i + j]);
					p += 1;
				}
			}
		}

		if (i + colomn < size)
		{
			//DBG_LOG("\n");
			sprintf(p, "\n");
			p += 1;
		}

		*p = '\0';
		DBG(debug_info);
		p = debug_info;
	}
}
