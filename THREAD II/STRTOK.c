#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "time.h"
#include <string.h>
#include <semaphore.h>
//#include <time.h>
#define threads_total 2
	
/*VARIABLES*/
struct list_node_s* head_p = NULL;
	
long long thread_count=threads_total;
pthread_t hilos[threads_total];
int ing_tot=0,del_tot=0;
double tmp1,tmp2,tmp3,tmp4;
double tiempo_total = 0;
const int MAX = 1000;
sem_t* sems;

	
/*FUNCIONES*/
void *Tokenize(void* rank) {
    long my_rank = (long) rank;
    int count;
    int next = (my_rank + 1) % thread_count;
    char *fg_rv;
    char my_line[MAX];
    char *my_string;
	
    sem_wait(&sems[my_rank]);
    fg_rv = fgets(my_line, MAX, stdin);
    sem_post(&sems[next]);

    while (fg_rv != NULL) {
        printf("Thread %ld > my line = %s", my_rank, my_line);

        count = 0;
      	my_string = strtok(my_line, " \t\n");
      	while ( my_string != NULL ) {
      		sleep(1);
         	count++;
         	printf("Thread %ld > string %d = %s\n", my_rank, count, my_string);
         	my_string = strtok(NULL, " \t\n");
      	}
      	sem_wait(&sems[my_rank]);
      	fg_rv = fgets(my_line, MAX, stdin);
      	sem_post(&sems[next]);
   	}
	return NULL;
}  /* Tokenize */

int main(void) {
	int k,xt;
	sems = malloc(thread_count*sizeof(sem_t));
	sem_init(&sems[0], 0, 1);

	for (k = 1; k < thread_count; ++k)
	{
		sem_init(&sems[k], 0, 0);
	}

	GET_TIME(tmp1);
    for(long i=0;i<thread_count;i++){
		xt = pthread_create(&hilos[i], NULL, Tokenize,(void*) i);
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