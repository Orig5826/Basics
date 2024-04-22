#include <stdint.h>
#include <stdio.h>

// socket,bind
#include <sys/types.h>
#include <sys/socket.h>

// struct sockaddr_in
#include <arpa/inet.h>

// close
#include <unistd.h>



#define IP_ADDR             "127.0.0.1"
#define PORT                8080
#define BACKLOG             5

#define BUFFER_SIZE_MAX     1024

uint8_t recv_buf[BUFFER_SIZE_MAX];
uint32_t recv_len = 0;

int socket_server_tcp_demo(void)
{
    int sockfd = -1;
    struct sockaddr_in server_addr;
    int connect_fd = -1;
    socklen_t addrlen = 0;

    struct sockaddr_in client_addr;
    ssize_t length = 0;

    // 创建套接字
    printf("create socket\r\n");
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        printf("socket failed!\r\n");
        goto done;
    }

    // int opt = 1;
    // if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
    //     perror("setsockopt");
    //     goto done; 
    // }

    // 绑定socket到IP地址
    printf("bind socket and ip\r\n");
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    if(bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("bind failed!\r\n");
        goto done;
    }

    // 开始监听
    printf("start listen ...\r\n");
    if(listen(sockfd, BACKLOG) < 0)
    {
        printf("listen failed!\r\n");
        goto done;
    }

    while(1)
    {
        // 等待连接[阻塞]
        printf("wait connect... \r\n");
        connect_fd = accept(sockfd, (struct sockaddr *)&client_addr, &addrlen);
        if(connect_fd < 0)
        {
            printf("accept failed\r\n");
            goto done;
        }
        printf("new client connected from (%s, %d)\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        recv_len = BUFFER_SIZE_MAX;
        while(1)
        {
            // 等待接收[阻塞]
            length = 0;
            printf("wait recv... \r\n");
            length = recv(connect_fd, recv_buf, recv_len, 0);
            if(length == 0)
            {
                printf("client disconnected!\r\n");

                close(connect_fd);
                connect_fd = -1;
                break;
            }
            else if(length < 0)
            {
                printf("recv failed!\r\n");
                goto done;
            }

            printf("recv:\n%s\n", recv_buf);  
            send(connect_fd, recv_buf, length, 0);
        }
    }

    return 0;
done:
    close(sockfd);
    return -1;
}

int main(int argc, int argv)
{
    socket_server_tcp_demo();

    return 0;
}