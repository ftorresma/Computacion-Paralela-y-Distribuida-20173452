#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "time.h"
//#include <time.h>
#define threads_total 8

/*CLASES*/

struct list_node_s {
	int data;
	struct list_node_s* next;
	pthread_mutex_t mutex;
};

/*VARIABLES*/
struct list_node_s* head_p = NULL;

pthread_mutex_t head_p_mutex;
long long thread_count=threads_total;
int operaciones = 100000;
pthread_t hilos[threads_total];
int ing_tot=0,del_tot=0;
double tmp1,tmp2;
float tiempo_total = 0;


/*FUNCIONES*/

int Member(int value) {
	
	struct list_node_s* temp_p;
	pthread_mutex_lock(&head_p_mutex);
	temp_p = head_p;
	
	while (temp_p != NULL && temp_p->data < value) {
		if(temp_p->next != NULL)
			pthread_mutex_lock(&(temp_p->next->mutex));
		if(temp_p == head_p)
			pthread_mutex_unlock(&head_p_mutex);
		pthread_mutex_unlock(&(temp_p->mutex));
		temp_p = temp_p->next;
	}
	if(temp_p == NULL || temp_p->data > value) {
		if(temp_p == head_p)
			pthread_mutex_unlock(&head_p_mutex);
		if(temp_p != NULL)
			pthread_mutex_unlock(&(temp_p->mutex));
		return 0;
	}
	else{
		if(temp_p == head_p)
			pthread_mutex_unlock(&head_p_mutex);
		pthread_mutex_unlock(&(temp_p->mutex));
		return 1;
	}
} /* Member */


int Insert(int value, struct list_node_s** head_p) {

	struct list_node_s* curr_p = *head_p;
	struct list_node_s* pred_p = NULL;
	struct list_node_s* temp_p;

	while (curr_p != NULL && curr_p->data < value) {
		pred_p = curr_p;
		curr_p = curr_p->next;
	}

	if(curr_p == NULL || curr_p->data > value) {
		temp_p = malloc(sizeof(struct list_node_s));
		temp_p->data = value;
		temp_p->next = curr_p;
		if(pred_p == NULL) /* New first node */
			*head_p = temp_p;
		else
			pred_p->next = temp_p;
		return 1;
	} 
	else{ /* Value already in list */
		return 0;
	}
} /* Insert */

int Delete(int value, struct list_node_s** head_p) {

	struct list_node_s* curr_p = *head_p;
	struct list_node_s* pred_p = NULL;

	while (curr_p != NULL && curr_p->data < value) {
		pred_p = curr_p;
		curr_p = curr_p->next;
	}

	if(curr_p != NULL && curr_p->data == value) {
		if(pred_p == NULL) { /* Deleting first node in list */
			*head_p = curr_p->next;
			free(curr_p);
		}
		else{
			pred_p->next = curr_p->next;
			free(curr_p);
		}
		return 1;
	}
	else{ /* Value isn’t in list */
		return 0;
	}
} /* Delete */

void Print(struct list_node_s* head_p) {
   struct list_node_s* curr_p;

   printf("Lista = ");

   curr_p = head_p;
   while (curr_p != (struct list_node_s*) NULL) {
      printf("%d ", curr_p->data);
      curr_p = curr_p->next;
   }
   printf("\n");
}  /* Print */

void* RndomOperations(void* rank){
	long my_rank = (long) rank;
	int ran;
	int my_operations = operaciones/thread_count;
	
	for(int op=0;op<my_operations;op++){
		ran=rand() % 1000;
		if(ran>=0 && ran<=200){
			//if(ran==0){
			if((rand() % 200)>100){
				//if((rand() % 2)==1){
				pthread_mutex_lock(&head_p_mutex);
				Insert((rand() % 1000)+100000,&head_p);
				pthread_mutex_unlock(&head_p_mutex);
				ing_tot++;	
			}
			else{
				pthread_mutex_lock(&head_p_mutex);
				Delete((rand() % 1000),&head_p);
				pthread_mutex_unlock(&head_p_mutex);
				del_tot++;
			}

		}
		else{
			//pthread_mutex_lock(head_p_mutex);
			Member(ran);
			//pthread_mutex_unlock(head_p_mutex);
		}
	}
	//printf("HILO %ld TERMINO!!\n",my_rank );
	return NULL;
}

int main(void) {

	for(int in=0;in<1000;in++){
		Insert(in,&head_p);
	}
    pthread_mutex_init(&head_p_mutex, NULL);
    GET_TIME(tmp1);
    int x;
	for(long i=0;i<thread_count;i++){
		x = pthread_create(&hilos[i], NULL, RndomOperations,(void*) i);
		if (x != 0){
			printf("Error en la creacion del hili %ld.\n",i);
		}
	}
	
	//JOIN
	for(int j=0;j<thread_count;j++){
		pthread_join(hilos[j], NULL);
	}
	GET_TIME(tmp2);
	printf("Los %lld hilos han terminado, tiempo:%f\n",thread_count,(tmp2-tmp1));
	printf("Se ingresaron %i y se eliminaron %i\n",ing_tot,del_tot);
    return 0;
}