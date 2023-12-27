#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

#define DEV_NAME		"/dev/ttyUSB0"

int main(int argc, char *argv[])
{
	struct termios options; // 串口属性结构体
	
	uint8_t sdata[32];
	uint8_t rdata[32];
	uint32_t i = 0;

	// int fd = open(DEV_NAME, O_RDWR | O_NOCTTY);
	int fd = open(DEV_NAME, O_RDWR);
	if(fd < 0)
	{
		printf(DEV_NAME " open failed!\n");
		return -1;
	}
	printf(DEV_NAME " open succeed!\n");

	// 获取当前串口属性并保存到options结构体中
    tcgetattr(fd, &options);
    // 配置串口属性
    cfsetispeed(&options, B115200); // 波特率为9600bps
    cfsetospeed(&options, B115200);
    options.c_cflag &= ~PARENB; // 不使用奇偶校验位
    options.c_cflag &= ~CSTOPB; // 单个停止位
    options.c_cflag &= ~CSIZE; // 8位数据位
    options.c_cflag |= CS8;
    options.c_cflag &= ~CRTSCTS; // 禁用流控制
    options.c_cc[VMIN] = 1; // 非规范模式下等待1个字节
    options.c_cc[VTIME] = 5; // 超时时间为5*0.1s=0.5s
    // 应用新的串口属性
    tcsetattr(fd, TCSANOW, &options);

	if(argc != 1)
	{
		sdata[0] = 0x7f;
		printf("-> %02x\n", sdata[0]);
		write(fd, sdata, 1);
		read(fd, rdata, 9);
		printf("<- %s\n",rdata);
	}

	printf("-> ", sdata[0]);
	memcpy(sdata,"1234567890\r\n",12);
	for(i = 0; i < 12; i++)
	{
		printf("%02x ",sdata[i]);
	}
	printf("\n");
	write(fd, sdata, 12);
	read(fd, rdata, 12);
	printf("<- %s\n",rdata);

	close(fd);
	printf(DEV_NAME " close!\n");
	return 0;
}
