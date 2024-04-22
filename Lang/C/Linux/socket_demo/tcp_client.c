#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <time.h>

// socket,bind
#include <sys/types.h>
#include <sys/socket.h>

// struct sockaddr_in
#include <arpa/inet.h>

// close
#include <unistd.h>



#define IP_ADDR             "127.0.0.1"
#define PORT                8080

#define BUFFER_SIZE_MAX     1024


uint8_t recv_buf[BUFFER_SIZE_MAX];
uint8_t send_buf[BUFFER_SIZE_MAX];
int32_t recv_len = 0;
int32_t send_len = 0;

int socket_client_tcp_demo(void)
{
    int sockfd = -1;
    struct sockaddr_in server_addr;

    const char * hello = "Keep optimistic and love life! Real men program in C!";

    // 创建套接字
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        printf("socket failed!\r\n");
        goto done;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if(inet_pton(AF_INET, IP_ADDR, &server_addr.sin_addr) <= 0)
    {
        printf("inet_pton failed!\r\n");
        goto done;
    }

    // 连接
    if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("connect failed!\r\n");
        goto done;
    }

    send_len = strlen(hello);
    memcpy(send_buf, hello, send_len);

    send_len = 1024;

    time_t time_start, time_end;
    time_start = clock();   //us
    send(sockfd, send_buf, send_len, 0);
    time_end = clock();
    double time_s = (double)(time_end - time_start)/CLOCKS_PER_SEC;
    printf("time = %0.6f s\n",(double)time_s);
    printf("speed = %0.6f MBps\n", (double)send_len/time_s/1024/1024);

    recv_len = send_len;
    recv(sockfd, recv_buf, recv_len, 0);
    printf("recv:\n%s\n", recv_buf);  

    return 0;
done:
    close(sockfd);
    return -1;
}

int main(int argc, int argv)
{
    socket_client_tcp_demo();
    
    return 0;
}
