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
Para evitar que los mensajes se impriman mezclados o con colores incorrectos, se utiliza un semáforo (`sem_t`) que sincroniza el acceso a la variable que define el color del texto.

Al ejercutar el código de la Figura 3 obtuvimos lo siguiente:

<img width="407" height="75" alt="Captura de pantalla 2026-05-18 183601" src="https://github.com/user-attachments/assets/20bdc88b-ed20-4c71-bcae-ab671e0bfd56" />

De esta forma se puede comprobar que sin una sincronización los hilos pueden ejecutar al mismo tiempo y, por lo tanto, ambos pueden cambiar el color de la terminal simultáneamente. Aunque los mensajes impresos por los hilos mantienen su color esperado, se puede observar el problema cuando finaliza la ejecución: después de imprimir el texto AZUL, la línea del sistema también aparece en azul. Esto se debe a que el programa no restablece adecuadamente el color de la consola antes de terminar.

Por esta razón se incorpora un semáforo: este mecanismo garantiza que únicamente un hilo a la vez pueda modificar el color de la terminal, evitando así que los mensajes se impriman con un color incorrecto o se mezclen entre sí.

### Rol de Semáforo
Se declara un semáforo global y se inicializa el semáforo como binario

       sem_t sem_color;
       sem_init(&sem_color, 0, 1);

   
