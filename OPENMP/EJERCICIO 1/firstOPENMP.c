#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<string.h>
#define MAX_VALUE 1000
#include <omp.h>
#include "time.h"


double tmp1,tmp2;

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        printf("Se necesitan 2 argumentos, tamano de lista y numero de hilos\n");
        exit(-1);       
    }
  
    int size = atoi(argv[1]);
    int thread_count = atoi(argv[2]);
    int *a = (int*)calloc(size, sizeof(int));
    int *initial = (int*)calloc(size, sizeof(int));


    srand(time(NULL));
    
    for(int i = 0; i < size; i++){
        //a[i] = size-i;
        a[i] = 2;
    }
    /*
    

    printf("a=[");
    for(int k=0; k<size;k++){
        printf("%d,",a[k]);
    }
    printf("]");*/
    //memcpy(initial, a, size * sizeof(int));

    int phase, i, temp;

    printf("tam = %d , hilos = %d \n",size,thread_count);

    GET_TIME(tmp1);

    for(phase = 0; phase < size; phase++){
        if(phase % 2==0){   
            #pragma omp parallel for num_threads(thread_count) \
                default(none) shared(a,size) private(i,temp)
            for(i = 1; i < size; i += 2)
            {
                if(a[i-1] > a[i])
                {
                    temp = a[i-1];
                    a[i-1] = a[i];
                    a[i] = temp;
                }
            }
        }
        else 
        {
            #pragma omp parallel for num_threads(thread_count) \
                default(none) shared(a,size) private(i,temp)
            for(i = 1; i < size-1; i += 2)
            {
                if(a[i] > a[i+1])
                {
                    temp = a[i+1];
                    a[i+1] = a[i];
                    a[i] = temp;                        
                }
            }
        }            
    }

    GET_TIME(tmp2);

    printf("Los %d hilos han terminado, tiempo:%f\n",thread_count,(tmp2-tmp1));

}