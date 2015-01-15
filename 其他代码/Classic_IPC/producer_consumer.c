#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFF 20

pthread_mutex_t mu_prod_num;
pthread_cond_t produce, consume;

int prod_num = 0;


void * producer (void * input)
{
    pthread_mutex_lock(&mu_prod_num);
    while(prod_num==20)
        pthread_cond_wait(&produce, &mu_prod_num);

    
    prod_num++;
    printf("I am a producer,now %d\n", prod_num);
    if(prod_num==1)
        pthread_cond_signal(&consume);
    pthread_mutex_unlock(&mu_prod_num);

    return 0;
}


void * consumer (void * input)
{
    pthread_mutex_lock(&mu_prod_num);
    while(prod_num==0)
        pthread_cond_wait(&consume, &mu_prod_num);
    
    prod_num--;
    printf("I am a consumer,now %d\n", prod_num);
    if(prod_num==19)
        pthread_cond_signal(&produce);
    pthread_mutex_unlock(&mu_prod_num);

    return 0;
}






int main(int argc, char const *argv[])
{
    srand(time(NULL));  
    pthread_mutex_init(&mu_prod_num,NULL);

    pthread_cond_init(&produce,NULL);
    pthread_cond_init(&consume,NULL);
    
    int  prod = 0, consu = 0, temp[20];

    for (int i = 0; i < 10; ++i)
    {
        temp[i] = rand();
        if(temp[i]%2 == 0)
            prod++;
        else
            consu++;
    }
    printf("There are %d consumer and %d producers been sent!\n",prod, consu );
    
    
    pthread_t temp_thread;
    for(int i = 0; i < 10; ++i)
    {
        if(temp[i]%2 == 0)
            pthread_create(&temp_thread, NULL, consumer, NULL);
        else
            pthread_create(&temp_thread, NULL, producer, NULL);
    }
    

    while(1);           //这里两句顺序不能交换，否则主线程立马就把锁销毁了……
    pthread_mutex_destroy(&mu_prod_num);
    
    

    
    return 0;
}