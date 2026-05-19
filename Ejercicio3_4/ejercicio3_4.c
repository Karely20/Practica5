#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

//Definir los colores
#define ROJO "\x1b[31m"
#define VERDE "\x1b[32m"
#define AZUL "\x1b[34m"
#define RESET "\x1b[0m"  //Para restaurar el color por defecto

sem_t sem_color; //Protege el color de la terminal

void *rojo(void *id){
	sem_wait(&sem_color); //Protege la terminal antes de cambiar el color
	printf(ROJO "Este texto es ROJO!\n");
	printf(RESET); //Restaura el color antes de salir
	sem_post(&sem_color);
	return NULL;
}

void *verde(void *id){
	sem_wait(&sem_color);
	printf(VERDE "Este texto es verde!\n");
	printf(RESET);
	sem_post(&sem_color);
	return NULL;
}

int main(){
	pthread_t hilo_rojo, hilo_verde;

	sem_init(&sem_color, 0, 1); //Inicializamos el semaforo

	pthread_create(&hilo_rojo, NULL, rojo, NULL);
	pthread_create(&hilo_verde, NULL, verde, NULL);

	pthread_join(hilo_rojo, NULL);
	pthread_join(hilo_verde, NULL);

	printf(AZUL "Este texto es AZUL \n");
	printf(RESET);

	sem_destroy(&sem_color); //Destruye el semaforo

	return 0;
}
