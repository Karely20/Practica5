# EJERCICIO 3.5
## Código con mutex

Tomar como base los códigos de las Figuras 3 y 4 y verificar que un mutex permita compartir la variable que define el color del texto.

    #include <pthread.h>
    #include <stdio.h>

    #define MAX 10000000

    int a = 0;

    void *funcion_hilo1(void *arg) 
    {
        pthread_mutex_t *mutex = (pthread_mutex_t *)arg; 
        pthread_mutex_lock(mutex);
        for(int i = 0; i < MAX; i++) {
          a += 1;
        }
        pthread_mutex_unlock(mutex);
    }

    void *funcion_hilo2(void *arg) 
    {
        pthread_mutex_t *mutex = (pthread_mutex_t *)arg;
        pthread_mutex_lock(mutex);
        for(int i = 0; i < MAX; i++) {
          a -= 1;
        }
        pthread_mutex_unlock(mutex); 
    }

    int main() {
        pthread_t hilo1, hilo2; 
        pthread_mutex_t mutex;  
     
        pthread_mutex_init(&mutex, NULL);
    
        pthread_create(&hilo1, NULL, funcion_hilo1, &mutex);
        pthread_create(&hilo2, NULL, funcion_hilo2, &mutex);
    
        pthread_join(hilo1, NULL);
        pthread_join(hilo2, NULL);
 
        pthread_mutex_destroy(&mutex);
    
        printf("El valor de a es %d \n", a);

        return 0;
    }

- Este ejercicio implementa el uso de `pthread_mutex` para sincronizar el acceso a un recurso compartido cuando dos hilos intentan usarlo al mismo tiempo.

*Ejecución de la Figura 4:*

<img width="317" height="49" alt="Captura de pantalla 2026-05-18 203617" src="https://github.com/user-attachments/assets/598b0890-2927-4c89-bb55-740e4f39b20a" />

En la Figura 4 se observa que el valor impreso al final de la ejecución es 0. Esto ocurre porque la variable global `a` funciona como recurso compartido entre dos hilos que ejecutan operaciones contrarias:
- **Hilo 1:** incrementa la variable `a` en 10 millones.
- **Hilo 2:** decrementa la variable `a` en 10 millones.

Si ambos hilos accedieran a `a` sin coordinación, las constantes interrupciones provocarían una condición de carrera, generando resultados inconsistentes o completamente erróneos.
Es por ello que se implementa `mutex`. Al utilizarlo:
- Solo un hilo a la vez puede modificar a.
- Los dos hilos modifican a de manera ordenada.
- El resultado final es 0, garantizado y determinístico.




El estado de color de la terminal, que normalmente puede corromperse si múltiples hilos intentan imprimir con diferentes códigos ANSI al mismo tiempo.

Para este ejercicio se ha modificado el código base de la Figura 4 en función al ejercicio planeteado anteriormente.
