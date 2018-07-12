#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

static void display(unsigned char * data,unsigned int len)
{
	unsigned int i = 0;
	for(i = 0; i < len ; i++)
	{
		if(i != 0 && i % 16 == 0)
		{
			printf("\n");
		}

		printf("%02X ",*(data + i));
	}
	printf("\n");
}


static int s_fd_mouse;
int main(int argc,char * argv[])
{
	static unsigned char rBuf[8] = {0};
	static unsigned int rLen = 0;
	char * mdev = "/dev/input/mice";
	int ret = 0;
	s_fd_mouse = open(mdev,O_RDONLY);
	if(s_fd_mouse < 0)
	{
		printf("mouse opend failed!\n");
		return -1;
	}

	while(1)
	{
		rLen = 4;
		ret = read(s_fd_mouse,rBuf,rLen);
		if(ret < 0)
		{
			printf("read error!\n");
			continue;
		}
		display(rBuf,rLen);
	}
	return 0;
}