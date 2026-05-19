# EJERCICIO 3.4
## Código con semáforo - Variable color de texto

Tomar como base el código de la Figura 3 propuesto y añadir un semáforo que permita compartir la variable que define el color del texto.
    
    #include <stdio.h>
    #include <stdlib.h>
    #include <pthread.h>
    void * rojo(void *id)
    {
    #define A "\x1b[31m"
    printf (A "Este texto es ROJO! \n");
    }
    void * verde(void *id)
    {
    #define B "\x1b[32m"
    printf(B "Este texto es VERDE! \n");
    }
    int main()
    {
    pthread_t hilo_rojo, hilo_verde;
    pthread_create(&hilo_rojo, NULL,*rojo, NULL);
    pthread_create(&hilo_verde, NULL,*verde, NULL);
    pthread_join(hilo_rojo, NULL);
    pthread_join(hilo_verde, NULL);
    #define C "\x1b[34m"
    printf (C "Este texto es AZUL \n");
    return 0;
    }
Este programa demuestra cómo dos hilos pueden acceder a un recurso compartido: el estado de color de la terminal. 
Para evitar que los mensajes se impriman mezclados o con colores incorrectos, se utiliza un semáforo (~sem_t~) que sincroniza el acceso.
