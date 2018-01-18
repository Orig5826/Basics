#include <stdio.h>
#include <conio.h>
#include <string.h>

typedef enum _bool
{
    false = 0,
    true
}bool;


#define STRICT
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

//void system_error(char *name) {
//    char *ptr = NULL;
//    FormatMessage(
//        FORMAT_MESSAGE_ALLOCATE_BUFFER |
//        FORMAT_MESSAGE_FROM_SYSTEM,
//        0,
//        GetLastError(),
//        0,
//        (char *)&ptr,
//        1024,
//        NULL);
//
//    fprintf(stderr, "\nError %s: %s\n", name, ptr);
//    LocalFree(ptr);
//}
static char buffer[1024] = {0};
int main(int argc, char **argv) {
    DWORD write;
    DWORD read;
    COMSTAT ComStat;
    DWORD dwErrorFlags;
    HANDLE hCom;
    DCB dcb = { 0 };
    char * serial_name = "COM3";
    bool flag;
    char msg[1024] = "led blk1\r\n";
    int msgLen = 0;
    char ch;
    printf("%d\n",sizeof(msg));
    hCom = CreateFile(
        serial_name, //CM1串口
        GENERIC_WRITE | GENERIC_READ, //允许读和写
        0,//独占方式
        NULL,
        OPEN_EXISTING, //打开而不是创建
        0,//同步操作
        //FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, //重叠方式
        NULL);
    if (hCom == INVALID_HANDLE_VALUE)
    {
        printf("串口写入失败:can not open %s\n", serial_name);
        return 0;
    }
    if ((flag = GetCommState(hCom, &dcb)) == false)
    {
        printf("串口写入失败:Get Comm State Error!\n");
        return 0;
    }
    dcb.BaudRate = 115200;
    dcb.ByteSize = 8;
    dcb.StopBits = ONESTOPBIT;
    dcb.Parity = NOPARITY;

    //dcb.fParity = 0;
    if ((flag = SetCommState(hCom, &dcb)) == false)
    {
        printf("串口写入失败:Set Comm State Error!\n");
        return 0;
    }
    SetupComm(hCom, 1024, 1024);

    COMMTIMEOUTS TimeOuts;
    TimeOuts.ReadIntervalTimeout = 1;
    TimeOuts.ReadTotalTimeoutMultiplier = 1;
    TimeOuts.ReadTotalTimeoutConstant = 10;  ///设定写超时
    TimeOuts.WriteTotalTimeoutMultiplier = 1;
    TimeOuts.WriteTotalTimeoutConstant = 1;
    if (!SetCommTimeouts(hCom, &TimeOuts))
        printf("set comm time out error");

    PurgeComm(hCom, PURGE_RXCLEAR);///清空缓冲区
    ClearCommError(hCom, &dwErrorFlags, &ComStat);
    SetupComm(hCom, 1024, 1024);

    flag = 0;
    while(1)
    {
        if(flag == 0)
        {
            flag = 1;
            read = 0;
            if(ReadFile(hCom,buffer,sizeof(buffer),&read,NULL))
            {
                if(buffer[read-1] == '\r')
                {
                    buffer[read++] = '\n';
                }
                buffer[read] = '\0';
                printf("%s",buffer);

            }
        }
        else
        {
            flag = 0;
            ch = getch();
            msg[0] = ch;
            WriteFile(hCom,msg,1,&write,NULL);
        }
    }
    return 0;
}
