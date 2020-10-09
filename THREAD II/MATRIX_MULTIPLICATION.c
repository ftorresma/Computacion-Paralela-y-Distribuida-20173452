#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "time.h"
//#include <time.h>
#define threads_total 4
#define D1 8
#define D2 8000000
	
/*CLASES*/
	
struct list_node_s {
	int data;
	struct list_node_s* next;
};	
	
/*VARIABLES*/
struct list_node_s* head_p = NULL;
	
long long thread_count=threads_total;
int operaciones = 100000;
pthread_t hilos[threads_total];
int ing_tot=0,del_tot=0;
double tmp1,tmp2,tmp3,tmp4;
double tiempo_total = 0;
int A[D1][D2];
int y[D1];
int x[D2];
	
/*FUNCIONES*/
void *Pth_mat_vect(void* rank) {
	long my_rank = (long) rank;
	int i, j;
	int local_m = D1/thread_count;
	int my_first_row = my_rank*local_m;
	int my_last_row = (my_rank+1)*local_m - 1;
	GET_TIME(tmp3);
	//printf("Iniciando con el hilo %li\n",my_rank);
	for (i = my_first_row; i <= my_last_row; i++) {
		
		y[i] = 0.0;
		for (j = 0; j < D2; j++)
			y[i] += A[i][j]*x[j];
	}
	GET_TIME(tmp4);
	tiempo_total+=(tmp4-tmp3);
	//printf("Terminando el Hilo %li\n",my_rank);
	return NULL;
} /* Pth mat vect */

int main(void) {
	int xt;
	for(int in=0;in<D1;in++){
		for (int yn = 0; yn < D2; ++yn)
		{
			A[in][yn]=0;
		}
	}
	for (int im = 0; im < D2; ++im)
	{
		x[im]=0;
	}
	GET_TIME(tmp1);
    for(long i=0;i<thread_count;i++){
		xt = pthread_create(&hilos[i], NULL, Pth_mat_vect,(void*) i);
		if (xt != 0){
			printf("Error en la creacion del hili %ld.\n",i);
		}
	}
	//JOIN
	for(int j=0;j<thread_count;j++){
		pthread_join(hilos[j], NULL);
	
	}
	GET_TIME(tmp2);
	//printf("Todos los hilos han terminado, tiempo:%f\n",(tmp2-tmp1)/CLOCKS_PER_SEC);
	printf("Los %lli nodos terminaron en P:%f --- S:%f\n",thread_count,tmp2-tmp1,tiempo_total);
	printf("LA EFICIENCIA ES: %f\n",tiempo_total/((tmp2-tmp1)*thread_count));
    return 0;
}	