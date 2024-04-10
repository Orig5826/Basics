#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// 信号处理函数
void signal_handler(int signum) {
    if (signum == SIGINT) {
        printf("Caught SIGINT signal, exiting...\n");
        exit(signum); // 退出程序
    }
}

int main() {
    // 注册SIGINT信号的处理函数
    if (signal(SIGINT, signal_handler) == SIG_ERR) {
        perror("signal");
        exit(EXIT_FAILURE);
    }

    printf("During the program's operation, you can press Ctrl+C to send a SIGINT signal.\n");
    while (1) {
        // 无限循环，直到接收到SIGINT信号
        sleep(1);
    }

    return 0;
}
