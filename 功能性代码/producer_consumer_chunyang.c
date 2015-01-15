#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include "queue.h"

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0);

#define BUFFERSIZE 5

sem_t full;   /* 同步信号量，表示缓冲区中有产品 */
sem_t empty;  /* 同步信号量，表示缓冲区中有空闲 */
pthread_mutex_t mutex; /* 互斥锁，用于实现对缓冲区的互斥操作  */

Queue Q;

void *producer(void *arg){

    while(1){
        sem_wait(&empty); //生产者等待有空闲
        pthread_mutex_lock(&mutex);
        
        int num = rand()%100;
        queue_push(&Q, num);
        printf("push a num %d\n", num);

        pthread_mutex_unlock(&mutex);
        sem_post(&full); //通知消费者去消费产品
        sleep(1);
    }
}

void *consumer(void *arg){
    while(1){
        sem_wait(&full); //消费者等待有产品
        pthread_mutex_lock(&mutex); 

        int num = queue_top(&Q);
        printf("pop a num %d\n", num);
        queue_pop(&Q);

        pthread_mutex_unlock(&mutex);
        sem_post(&empty); //通知生产者可以放入产品
        sleep(3);
    }
}

int main(int argc, const char *argv[])
{
    srand(10086);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFERSIZE);
    pthread_mutex_init(&mutex, NULL);
    queue_init(&Q);

    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, producer, NULL);
    pthread_create(&tid2, NULL, consumer, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    queue_destroy(&Q);
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}
