#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

int a = 0;
long MAX = 1000000;

sem_t s;

void *funcion_hilo1(void *arg);
void *funcion_hilo2(void *arg);

int main(void)
{
    pthread_t hilo1, hilo2;
    
    sem_init(&s, 0, 1);
    
    pthread_create(&hilo1, NULL, funcion_hilo1, NULL);
    pthread_create(&hilo2, NULL, funcion_hilo2, NULL);
    
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
    
    printf("El valor final de a es %d \n", a);
    
    sem_destroy(&s);
    return 0;
}

void *funcion_hilo1(void *arg)
{
    for(long i = 0; i < MAX; i++)
    {
        sem_wait(&s);
        a += 1;
        sem_post(&s);
    }
    return NULL;
}

void *funcion_hilo2(void *arg)
{
    for(long i = 0; i < MAX; i++)
    {
        sem_wait(&s);
        a -= 1;
        sem_post(&s);
    }
    return NULL;
}
