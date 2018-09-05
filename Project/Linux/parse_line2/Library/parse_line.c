/*
 * @breaf 解析单行命令
 *     参考uboot模拟main函数的参数解析
 */
#include <stdio.h>
#include <string.h>

#define CFG_CBSIZE 512
#define CFG_MAXARGS 128
//#define DEBUG_PARSER
int parse_line(char *line, char *argv[])
{
	int nargs = 0;

#ifdef DEBUG_PARSER
	printf("parse_line: \"%s\"\n", line);
#endif
	while (nargs < CFG_MAXARGS)
	{

		/* skip any white space */
		while ((*line == ' ') || (*line == '\t'))
		{
			++line;
		}

		if (*line == '\0')
		{ /* end of line, no more args	*/
			argv[nargs] = NULL;
#ifdef DEBUG_PARSER
			printf("parse_line: nargs=%d\n", nargs);
#endif
			return (nargs);
		}

		argv[nargs++] = line; /* begin of argument string	*/

		/* find end of string */
		while (*line && (*line != ' ') && (*line != '\t'))
		{
			++line;
		}

		if (*line == '\0')
		{ /* end of line, no more args	*/
			argv[nargs] = NULL;
#ifdef DEBUG_PARSER
			printf("parse_line: nargs=%d\n", nargs);
#endif
			return (nargs);
		}

		*line++ = '\0'; /* terminate current arg	 */
	}

	printf("** Too many args (max. %d) **\n", CFG_MAXARGS);

#ifdef DEBUG_PARSER
	printf("parse_line: nargs=%d\n", nargs);
#endif
	return (nargs);
}

/*
 * @breaf parse_line测试程序
 */
void parse_line_test(void)
{
	char finaltoken[CFG_CBSIZE];
	char *argv[CFG_MAXARGS + 1];
	int argc = 0;
	// 模拟一下main函数参数的处理方式
	// 假设cmd是传输进来的命令及其参数
	char *cmd = "ls -l test";
	// 注意，送给parse_line函数的第一个命令参数
	// 是字符串，因此复制的时候需要将最后一个字节
	// 的'\0'也复制过去
	memcpy(finaltoken, cmd, strlen(cmd) + 1);
	argc = parse_line(finaltoken, argv);

	if(argc == 3)
	{
		// 到这里，得到的参数就和main函数的类似了
		printf("argv[0] = %s\n", argv[0]);
		printf("argv[1] = %s\n", argv[1]);
		printf("argv[2] = %s\n", argv[2]);
		if (argv[3] == NULL)
		{
			printf("\n--- END ---\n");
		}
		else
		{
			printf("%s", argv[3]);
		}
	}
}
