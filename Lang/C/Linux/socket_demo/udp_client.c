#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define IP_ADDR             "127.0.0.1"
#define PORT                8080
#define BACKLOG             5

#define BUFFER_SIZE_MAX     40960

uint8_t recv_buf[BUFFER_SIZE_MAX];
uint8_t send_buf[BUFFER_SIZE_MAX];
int32_t recv_len = 0;
int32_t send_len = 0;

int socket_server_udp_demo(void)
{
    int sockfd = -1;
    struct sockaddr_in server_addr;
    ssize_t length = 0;

    const char * hello = "Keep optimistic and love life! Real men program in C!";

    // 创建套接字
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0)
    {
        printf("socket failed!\r\n");
        goto done;
    }

    // 绑定socket到IP地址
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if(inet_pton(AF_INET, IP_ADDR, &server_addr.sin_addr) <= 0)
    {
        printf("inet_pton failed!\r\n");
        goto done;
    }

    send_len = strlen(hello);
    memcpy(send_buf, hello, send_len);

    printf("sendto :\n");
    send_len = BUFFER_SIZE_MAX;


    time_t time_start, time_end;
    // time_start = clock();
    time(&time_start);

    uint32_t total_bytes = 0;
    uint32_t num_messages = 0;
#define TEST_DURATION       10
    while(1)
    {
        sendto(sockfd, send_buf, send_len, 0, (const struct sockaddr *)&server_addr, sizeof(server_addr));

        recv_len = BUFFER_SIZE_MAX;
        length = recvfrom(sockfd, recv_buf, recv_len, MSG_WAITALL, NULL, 0);
        if(length < 0)
        {
            printf("accept failed\r\n");
            goto done;
        }

        total_bytes += recv_len;
        num_messages++;

        time(&time_end);
        if(difftime(time_end, time_start) >= TEST_DURATION)
        {
            break;
        }
    }

    close(sockfd);
    
    // time_end = clock();
    // printf("receive length = %ld\n", length);
    // double time_s = (double)(time_end - time_start)/CLOCKS_PER_SEC;
    // printf("time = %0.6f s\n",(double)time_s);
    // printf("speed = %0.6f MBps\n", (double)send_len/time_s/1024/1024);

    double test_duration_seconds = difftime(time_end, time_start);  
    double bytes_per_second = (double)total_bytes / test_duration_seconds;  
    double messages_per_second = (double)num_messages / test_duration_seconds;  
  
    printf("Test duration: %.2f seconds\n", test_duration_seconds);  
    printf("Total bytes received: %u\n", total_bytes);  
    printf("Bytes per second: %.2f\n", bytes_per_second);  
    printf("Messages per second: %.2f\n", messages_per_second);

    printf("speed = %0.2f MBps\n", (double)bytes_per_second/1024/1024);

done:
    return 0;
}

int main(int argc, int argv)
{
    socket_server_udp_demo();

    return 0;
}
