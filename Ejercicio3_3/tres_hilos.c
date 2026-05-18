#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

int a = 0;
long MAX = 100000; 

sem_t s; 

void *funcion_hilo1(void *arg);
void *funcion_hilo2(void *arg);
void *funcion_hilo3(void *arg); // añado la funcion para el nuevo hilo 3

int main(void)
{
    pthread_t hilo1, hilo2, hilo3; // aumento la variable para el hilo 3
    int valor_semaforo;
    
    sem_init(&s, 0, 1);
    
    pthread_create(&hilo1, NULL, funcion_hilo1, NULL);
    pthread_create(&hilo2, NULL, funcion_hilo2, NULL);
    pthread_create(&hilo3, NULL, funcion_hilo3, NULL); // aqui creo el hilo 3 para que empiece a correr
    
    // con estas dos lineas leo el semaforo a mitad de ejecucion y lo muestro en pantalla
    sem_getvalue(&s, &valor_semaforo);
    printf("El valor del semaforo durante la ejecucion: %d\n", valor_semaforo);
    
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
    pthread_join(hilo3, NULL); // tambien espero que termine el hilo 3 antes de cerrar todo
    
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

// esta es la logica del hilo nuevo que hace la suma de 2 en 2 usando el semaforo
void *funcion_hilo3(void *arg)
{
    for(long i = 0; i < MAX; i++)
    {
        sem_wait(&s);   
        a += 2;         
        sem_post(&s);   
    }
    return NULL;
}
