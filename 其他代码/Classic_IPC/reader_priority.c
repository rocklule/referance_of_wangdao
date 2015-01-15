#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

int r_count = 0, share = 0;
pthread_mutex_t mu_access;
pthread_mutex_t mu_r_count;

void * reader (void * input)
{
    pthread_detach(pthread_self());
    
    pthread_mutex_lock(&mu_r_count);
    if(r_count==0)
        pthread_mutex_lock(&mu_access);
    ++r_count;
    pthread_mutex_unlock(&mu_r_count);
    
    printf("i'm a reader! now share is:%d\n", share);
    // sleep(2);
    
    pthread_mutex_lock(&mu_r_count);
    --r_count;
    if(r_count==0)
        pthread_mutex_unlock(&mu_access);
    pthread_mutex_unlock(&mu_r_count);
    
    
    return 0;
}

void * writer (void * input)
{
    pthread_mutex_lock(&mu_access);
        ++share;
    pthread_mutex_unlock(&mu_access);
    
    return 0;
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    pthread_mutex_init(&mu_access,NULL);
    pthread_mutex_init(&mu_r_count,NULL);
    
    int temp[20], re = 0, wr = 0;
    
    for (int i = 0; i < 30; ++i)
    {
        temp[i] = rand();
        if(temp[i]%2 == 0)
            re++;
        else
            wr++;
    }
    printf("There are %d readers and %d writers been sent!\n",re, wr );
    
    
    pthread_t temp_thread;
    for(int i = 0; i < 30; ++i)
    {
        if(temp[i]%2 == 0)
            pthread_create(&temp_thread, NULL, reader, NULL);
        else
            pthread_create(&temp_thread, NULL, writer, NULL);
    }
    
    pthread_mutex_destroy(&mu_access,NULL);
    pthread_mutex_destroy(&mu_r_count,NULL);


    while(1);
    
    return 0;
}


