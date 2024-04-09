#include <stdio.h>  
#include <stdlib.h>  
#include <pthread.h>  
#include <unistd.h>
#include <stdint.h>
#include <semaphore.h>

uint32_t count = 0;

// #define USE_SEM
#ifdef USE_SEM
sem_t sem;
#endif

void *thread_function(void *arg) {
    char *message = (char *) arg;

    for(uint32_t i = 0; i < 1000000; i++)
    {
        #ifdef USE_SEM
        sem_wait(&sem);
        #endif

        count++;
        count--;

        #ifdef USE_SEM
        sem_post(&sem);
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
    sem_init(&sem, 0, 1);
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

    printf("count = %d\n", count); 

    pthread_exit(NULL);
}
