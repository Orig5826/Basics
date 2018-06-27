#include "getBuff.h"

extern stBuff g_str = {{0},-1};

void clearBuff()
{
	g_str.index = -1;
}

bool getBuff()
{
	char ch = 0;
	while(ch = getchar())
	{
		if(isspace(ch))
		{
			//遇到回车，则直接退出循环
			if(ch == '\n')
			{
				break;
			}
			continue;
		}
		g_str.index++;
		g_str.buff[g_str.index] = ch;
	}
}

int getBuffLen()
{
	return g_str.index + 1;
}