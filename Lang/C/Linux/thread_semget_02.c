#include <stdio.h>  
#include <stdlib.h>  
#include <pthread.h>  
#include <unistd.h>
#include <stdint.h>

#include <ctype.h>

// semget
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>


// #define COUNT_MAX   10
// #define COUNT_MAX   100000       // semop 报溢出
#define COUNT_MAX   10000
uint32_t count = 0;

// 是否使用信号量？
#define USE_SEM

#ifdef USE_SEM
int g_semid;

int sem_new(int sem_num)
{
    key_t key;
    int semid = 0;

    // 生成一个唯一的key值，通常使用ftok函数  
    // if ((key = ftok(".", 'R')) == -1) {  
    //     perror("ftok");  
    //     exit(1);  
    // }
    key = IPC_PRIVATE;

    // 创建信号量集  
    if ((semid = semget(key, sem_num, IPC_CREAT | 0666)) == -1) {  
        perror("semget");  
        exit(1);  
    }

    // ----- 初始化信号量的值 -----
    // 按照当前程序的设计
    // 初值可以影响两线程谁先执行count++;
    union semun {  
        int val;  
        struct semid_ds *buf;  
        unsigned short *array;  
    }arg;
    arg.val = 0;        // 初值
    if (semctl(semid, 0, SETVAL, arg) == -1) {  
        perror("semctl");  
        exit(1);  
    }

    return semid;
}

void sem_del(int semid)
{
    // 删除信号量集  
    if (semctl(semid, 0, IPC_RMID) == -1) {  
        perror("semctl");  
        exit(1);  
    }
}

void sem_p(int semid, int index)
{
    struct sembuf sem_op[2];
    sem_op[0].sem_num = 0;  
    sem_op[0].sem_op = 0; 
    sem_op[0].sem_flg = 0;
    
    sem_op[1].sem_num = 0;
    sem_op[1].sem_op = 1; 
    sem_op[1].sem_flg = SEM_UNDO;
    if (semop(semid, &sem_op[0], 2) == -1) {  
        perror("semop");  
        exit(1);  
    }
}

void sem_v(int semid, int index)
{
    struct sembuf sem_op;
    sem_op.sem_num = index;
    sem_op.sem_op = -1;
    sem_op.sem_flg = 0; 
    if (semop(semid, &sem_op, 1) == -1) {  
        perror("semov");  
        exit(1);
    }
}
#endif

void *thread_function(void *arg) {
    char *message = (char *)arg;

    for(uint32_t i = 0; i < COUNT_MAX; i++)
    {
        // printf("^");

        #ifdef USE_SEM
        sem_p(g_semid, 0);
        #endif

        // printf("$\n");

        // printf("%d",atoi(message));

        count++;
        count--;

        #ifdef USE_SEM
        sem_v(g_semid, 0);
        #endif
    }
    return NULL;  
}

int main(int argc, char *argv[])
{
    pthread_t thread1, thread2;  
    const char *message1 = "1";  
    const char *message2 = "2";  
    int  iret1, iret2;

    #ifdef USE_SEM
    g_semid = sem_new(2);
    #endif

    // 创建线程 1  
    iret1 = pthread_create( &thread1, NULL, thread_function, (void*) message1);  
    if(iret1) {  
        printf("Error - pthread_create() return code: %d\n",iret1);  
        exit(EXIT_FAILURE);  
    }

    // 创建线程 2  
    iret2 = pthread_create( &thread2, NULL, thread_function, (void*) message2);  
    if(iret2) {
        printf("Error - pthread_create() return code: %d\n",iret2);  
        exit(EXIT_FAILURE);
    }

    // 等待线程完成  
    pthread_join(thread1, NULL);  
    pthread_join(thread2, NULL);

    #ifdef USE_SEM
    sem_del(g_semid);
    #endif

    printf("count = %d\n", count); 

    pthread_exit(NULL);
}
