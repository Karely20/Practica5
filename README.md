# PRÁCTICA 5 - USO DE SEMÁFOROS

**Nombres:** Karely Bombón, Jhon Tiupul, Fidel Quilumba, Jhoan Sasnalema

**Fecha:** 18-05-2026

## OBJETIVOS
1. Implementar el uso de semáforos y mutex en C.
2. Asimilar los conceptos teóricos revisados en clase.

## MARCO TEÓRICO
### Semáforo
Mecanismo de sincronización que protege una sección crítica.
### Funciones utilizadas en C
    //Inicializa el semáforo
     int sem_init(sem_t *sem, int pshared, unsigned int value);
     
    //Decrementa el valor del semáforo
    int sem_wait (sem_t *sem);
    
    //Incrementa el valor del semáforo, sem_signal
    int sem_post(sem_t *sem);
### Librería a utilizar
    #include <semaphore.h>
