/**
由于信号量只能进行两种操作等待和发送信号，即P(sv)和V(sv),他们的行为是这样的：
- P(sv)：如果sv的值大于零，就给它减1；如果它的值为零，就挂起该进程的执行
- V(sv)：如果有其他进程因等待sv而被挂起，就让它恢复运行，如果没有进程因等待sv而挂起，就给它加1.
举个例子，就是两个进程共享信号量sv，一旦其中一个进程执行了P(sv)操作，它将得到信号量，并可以进入临界区，使sv减1。而第二个进程将被阻止进入临界区，因为当它试图执行P(sv)时，sv为0，它会被挂起以等待第一个进程离开临界区域并执行V(sv)释放信号量，这时第二个进程就可以恢复执行。
*/
#include <stdio.h>  
#include <stdlib.h>  
#include <pthread.h>  
#include <unistd.h>
#include <stdint.h>

// semget
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>


#define COUNT_MAX   100000
uint32_t count = 0;

// 是否使用信号量？
#define USE_SEM

#ifdef USE_SEM
#define NUM_SEMS 2       // 信号量的数量  
// #define SEM_VALUE 1     // 信号量的初始值  

key_t key;
int semid;

void sem_p(int semid, int index)
{
    struct sembuf sem_op;
    // P操作（等待），将信号量减1  
    sem_op.sem_num = index;      // 指定操作第几个信号量，这里操作第一个信号量  
    sem_op.sem_op = -1;         // P操作：等待信号量变为非零，然后将其减1  
    sem_op.sem_flg = 0;         // 通常设为0  
    if (semop(semid, &sem_op, 1) == -1) {  
        perror("semop");  
        exit(1);  
    }
}

void sem_v(int semid, int index)
{
    struct sembuf sem_op;
    sem_op.sem_num = index;
    sem_op.sem_op = 1;         // V操作：将信号量加1
    sem_op.sem_flg = 0; 
    if (semop(semid, &sem_op, 1) == -1) {  
        perror("semov");  
        exit(1);
    }
}


#endif

void *thread_function(void *arg) {
    char *message = (char *) arg;

    for(uint32_t i = 0; i < COUNT_MAX; i++)
    {
        #ifdef USE_SEM
        sem_p(semid, 0);
        #endif

        // printf(".");

        count++;
        count--;

        #ifdef USE_SEM
        sem_v(semid, 1);
        #endif
    }
    return NULL;  
}


void *thread_function2(void *arg) {
    char *message = (char *) arg;

    for(uint32_t i = 0; i < COUNT_MAX; i++)
    {
        #ifdef USE_SEM
        sem_p(semid, 1);
        #endif

        // printf("-");

        count++;
        count--;

        #ifdef USE_SEM
        sem_v(semid, 0);
        #endif
    }
    return NULL;  
}


int main(int argc, char *argv[])
{
    pthread_t thread1, thread2;  
    const char *message1 = "Thread 1";  
    const char *message2 = "Thread 2";  
    int  iret1, iret2;

    #ifdef USE_SEM
    // 生成一个唯一的key值，通常使用ftok函数  
    // if ((key = ftok(".", 'R')) == -1) {  
    //     perror("ftok");  
    //     exit(1);  
    // }
    key = IPC_PRIVATE;

    // 创建信号量集  
    if ((semid = semget(key, NUM_SEMS, IPC_CREAT | 0666)) == -1) {  
        perror("semget");  
        exit(1);  
    }

    // 初始化信号量的值  
    union semun {  
        int val;  
        struct semid_ds *buf;  
        unsigned short *array;  
    }arg;
    arg.val = 1;
    if (semctl(semid, 0, SETVAL, arg) == -1) {  
        perror("semctl");  
        exit(1);  
    }

    union semun arg2;
    arg2.val = 0;
    if (semctl(semid, 1, SETVAL, arg2) == -1) {  
        perror("semctl");  
        exit(1);  
    }
    #endif

    // 创建线程 1  
    iret1 = pthread_create( &thread1, NULL, thread_function, (void*) message1);  
    if(iret1) {  
        printf("Error - pthread_create() return code: %d\n",iret1);  
        exit(EXIT_FAILURE);  
    }

    // 创建线程 2  
    iret2 = pthread_create( &thread2, NULL, thread_function2, (void*) message2);  
    if(iret2) {
        printf("Error - pthread_create() return code: %d\n",iret2);  
        exit(EXIT_FAILURE);
    }

    // 等待线程完成  
    pthread_join(thread1, NULL);  
    pthread_join(thread2, NULL);

    #ifdef USE_SEM
    // 删除信号量集  
    if (semctl(semid, 0, IPC_RMID) == -1) {  
        perror("semctl");  
        exit(1);  
    }
    #endif

    printf("count = %d\n", count); 

    pthread_exit(NULL);
}
