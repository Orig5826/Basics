
#include <Windows.h>

#include <stdio.h>
#include <stdint.h>
#include <string.h>

char* cmd_param[1024];

void print_hex(uint8_t* data, uint32_t len)
{
	uint32_t i = 0; 
	for (i = 0; i < len; i++)
	{
		printf("%c", data[i]);
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	const char *cmd = ".\\python3\\python.exe hamster ";
	int cmd_len = strlen(cmd);
	char* pdata = &cmd_param[0];
	memmove(pdata, cmd, cmd_len);
	pdata += cmd_len;

	for (int i = 1; i < argc; i++)
	{
		cmd_len = strlen(argv[i]);
		memmove(pdata, argv[i], cmd_len);
		pdata += cmd_len;

		*pdata = ' ';
		pdata += 1;
	}
	system(cmd_param);
	system("pause");
}
