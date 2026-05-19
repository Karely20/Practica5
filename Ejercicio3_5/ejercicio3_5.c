#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ROJO "\x1b[31m"
#define VERDE "\x1b[32m"
#define AZUL "\x1b[34m"
#define RESET "\x1b[0m"

void *rojo(void *arg){
	pthread_mutex_t *mutex  = (pthread_mutex_t *)arg;

	pthread_mutex_lock(mutex); //Bloquea el mutex para tomar control de la consola
	printf(ROJO "Este texto es ROJO!\n");
	printf(RESET);
	pthread_mutex_unlock(mutex); //Desbloquea

	return NULL;
}

void *verde(void *arg){
	pthread_mutex_t *mutex = (pthread_mutex_t *)arg;

	pthread_mutex_lock(mutex);
	printf(VERDE "Este texto es VERDE!\n");
	printf(RESET);
	pthread_mutex_unlock(mutex);

	return NULL;
}

int main(){
	pthread_t hilo_rojo, hilo_verde;
	pthread_mutex_t mutex_color;

	//Inicializa el mutex
	pthread_mutex_init(&mutex_color, NULL);

	//Pasa la direccion del mutex como parametro a los hilos
	pthread_create(&hilo_rojo, NULL, rojo, &mutex_color);
	pthread_create(&hilo_verde, NULL, verde, &mutex_color);

	pthread_join(hilo_rojo, NULL);
	pthread_join(hilo_verde, NULL);

	printf(AZUL "Este texto es AZUL\n");
	printf(RESET);

	pthread_mutex_destroy(&mutex_color); //Destruye el mutex al finalizar

	return 0;
}
