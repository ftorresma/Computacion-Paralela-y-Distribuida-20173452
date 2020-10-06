#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
//#include <time.h>
#define threads_total 64
long long thread_count=threads_total;
long long n=pow(10,8);
pthread_t hilos[threads_total];
pthread_mutex_t mutex;
volatile double sum;
double tmp1,tmp2;
float tiempo_total = 0;


void* Thread_sum(void* rank) {
	long my_rank = (long) rank;
	double factor,my_sum = 0.0;
	long long i;
	long long my_n = n/thread_count;
	long long my_first_i = my_n*my_rank;
	long long my_last_i = my_first_i + my_n;

	
	if (my_first_i % 2 == 0)
		factor = 1.0;
	else
		factor = -1.0;
	tmp1=clock();
	for (i = my_first_i; i < my_last_i; i++, factor = -factor){
		//my_sum += factor/(2*i+1);
		my_sum++;
	}
	pthread_mutex_lock(&mutex);
	sum += my_sum;
	pthread_mutex_unlock(&mutex);
	tmp2=clock();
	tiempo_total+=(tmp2-tmp1)/CLOCKS_PER_SEC;
	return NULL;
} /* Thread sum */

int main(int argc, char* argv[]){

	int x;
	for(int i=0;i<thread_count;i++){
		x = pthread_create(&hilos[i], NULL, Thread_sum, NULL);	
		if (x != 0){
			printf("Error en la creacion del hili %i.\n",i);
		}
	}
	//JOIN
	for(int j=0;j<thread_count;j++){
		pthread_join(hilos[j], NULL);
	}
	printf("Todos los hilos han terminado , fueron un total de %i con un tiempo de %f.\n",threads_total,tiempo_total);
	printf("La suma total fue de %f\n",sum);
    return 0;
}