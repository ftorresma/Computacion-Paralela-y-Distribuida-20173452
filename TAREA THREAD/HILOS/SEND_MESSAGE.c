#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
//#include <time.h>
#define threads_total 32
const int MSG_MAX = 100;
long long thread_count=threads_total;
pthread_t hilos[threads_total];


//char** messages;
char *messages[threads_total];


void* Send_msg(void* rank) {
	long my_rank = (long) rank;
	long long dest = (my_rank + 1) % thread_count;
	long long source = (my_rank + thread_count - 1) % thread_count;
	char* my_msg = malloc(MSG_MAX*sizeof(char));

	sprintf(my_msg, "Hello to %lld from %ld", dest, my_rank);
	messages[dest] = my_msg;

	if (messages[my_rank] != NULL)
		printf("Thread %ld > %s\n", my_rank, messages[my_rank]);
	else
		printf("Thread %ld > No message from %lld\n", my_rank,source);

	return NULL;
} /* Send msg */

int main(int argc, char* argv[]){
	long i;
	for (i = 0; i < thread_count; i++)
		messages[i] = NULL;
	int x;

	for (i = 0; i < thread_count; i++){
		x = pthread_create(&hilos[i], (pthread_attr_t*) NULL,Send_msg, (void*) i);
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