#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define IP_ADDR             "127.0.0.1"
#define PORT                8080
#define BACKLOG             5

#define BUFFER_SIZE_MAX     4096*1000

uint8_t recv_buf[BUFFER_SIZE_MAX];
uint32_t recv_len = 0;

int socket_server_udp_demo(void)
{
    int sockfd = -1;
    struct sockaddr_in server_addr, client_addr;
    socklen_t socklen = 0;
    ssize_t length = 0;

    // 创建套接字
    printf("create socket\r\n");
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0)
    {
        printf("socket failed!\r\n");
        goto done;
    }

    // 绑定socket到IP地址
    printf("bind socket and ip\r\n");

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    if(bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("bind failed!\r\n");
        goto done;
    }

    recv_len = BUFFER_SIZE_MAX;
    socklen = sizeof(client_addr);      // sendto接口，这个必须合理。

    int count = 0;
    while(1)
    {
        printf("wait recv... [%d]\r\n", count);
        count++;

        length = recvfrom(sockfd, recv_buf, recv_len, MSG_WAITALL, (struct sockaddr *)&client_addr, &socklen);
        if(length < 0)
        {
            printf("accept failed\r\n");
            goto done;
        }
        printf("receive length = %ld\n", length);

        sendto(sockfd, recv_buf, length, 0, (struct sockaddr *)&client_addr, socklen);
    }

done:
    return 0;
}

int main(int argc, int argv)
{
    socket_server_udp_demo();

    return 0;
}
