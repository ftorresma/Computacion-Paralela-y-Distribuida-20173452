#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
//#include <time.h>
#define threads_total 64

/*VARIABLES*/

long long thread_count=threads_total;
long long n=pow(10,8);
pthread_t hilos[threads_total];
pthread_mutex_t mutex;
volatile double sum;
double tmp1,tmp2;
float tiempo_total = 0;
//pthread_rwlock_t∗ rwlock;

/*CLASES*/

struct list_node_s {
	int data;
	struct list_node_s* next;
};

/*FUNCIONES*/

int Member(int value, struct list_node_s* head_p) {

	struct list_node_s* curr_p = head_p;

	while (curr_p != NULL && curr_p->data < value)
		curr_p = curr_p->next;

	if(curr_p == NULL || curr_p->data > value) {
		printf("No esta en la lista\n");
		return 0;
	} 
	else{
		printf("Si se encontro\n");
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

char Get_operacion(void) {
   	char c;
	printf("Ingrese una operacion: ");
   	
   	scanf(" %c", &c);
   	return c;
}  /* Get_operacion */

int  Get_Valor(void) {
   	int val;
   	printf("PIngrese un valor:  ");

   	scanf("%d", &val);
   	return val;
}  /* Get_Valor */

/*FUNCION PRINCIPAL*/

int main(void) {
    char operacion;
    int  value,num;
    struct list_node_s* head_p = NULL; 

    printf("SALIR:			S-s\n");
    printf("INSERTAR:		I-i\n");
    printf("ELIMINAR:		E-e\n");
    printf("BUSCAR:			B-b\n");
    printf("VER LISTA:		V-v\n");
    
    while (operacion != 'S' && operacion != 's') {
    	operacion=Get_operacion();
    	switch (operacion) {
        	case 'I': 
            case 'i': 
            	num=Get_Valor();
            	Insert(num, &head_p);
            	break;
         	case 'E':
         	case 'e':
            	num=Get_Valor();
            	Delete(num, &head_p);
            	break;
         	case 'B': 
         	case 'b':
            	num=Get_Valor();
            	Member(num, head_p); 
            	break;
         	case 'V':
         	case 'v':
	            Print(head_p);
            	break;
            case 'S':
         	case 's':
            	break;
         	default:
            	printf("La opcion %c NO ES VALIDA\n", operacion);
      	}
   	}
   	return 0;
}
