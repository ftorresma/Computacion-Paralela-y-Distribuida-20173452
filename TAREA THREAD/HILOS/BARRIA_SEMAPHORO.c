#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <semaphore.h>
//#include <time.h>
#define threads_total 16
long long thread_count=threads_total;
pthread_t hilos[threads_total];
int counter=0,ret2,ret1;
sem_t count_sem;
sem_t barrier_sem;

void* Thread_work(void* rank){
	int j;
	long my_rank = (long) rank;
	
	sem_wait(&count_sem);
	printf("Se a bloqueado el hilo %li el counter es: %i thread_count: %lli\n",my_rank,counter,thread_count-1);
	if(counter==thread_count-1){
		counter=0;
		sem_post(&count_sem);
		for(j=0;j<thread_count-1;j++)
			sem_post(&barrier_sem);
	}
	else{
		
		counter++;
		sem_post(&count_sem);
		sem_wait(&barrier_sem);
		
	}
	printf("Ha pasado el hilo %li\n",my_rank);

	return NULL;
}

int main(int argc, char* argv[]){
	int x;
	long i;
	ret2 = sem_init(&count_sem,1,thread_count);
	ret1 = sem_init(&barrier_sem,0,thread_count);
	for (i = 0; i < thread_count; i++){
		x = pthread_create(&hilos[i], (pthread_attr_t*) NULL,Thread_work, (void*) i);
		if (x != 0){
			printf("Error en la creacion del hili %li.\n",i);
		}
	}
		
	//JOIN
	for(int j=0;j<thread_count;j++){
		pthread_join(hilos[j], NULL);
	}
	printf("Ejecucion terminada\n");
    return 0;
}