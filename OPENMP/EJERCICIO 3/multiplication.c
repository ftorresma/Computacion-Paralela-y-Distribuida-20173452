#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "time.h"
//#include <time.h>
#define D1 8000000
#define D2 8
double tmp1,tmp2,tmp3,tmp4;
double total=0;
int thread_count = 4;
int A[D1][D2];
int B[D1];
int X[D2];
int main(void)
{
	
	
	for(int in=0;in<D1;in++){
		for (int yn = 0; yn < D2; ++yn)
		{
			A[in][yn]=0;
		}
	}
	for (int im = 0; im < D2; ++im)
	{
		B[im]=0;
	}
	GET_TIME(tmp1);
	int i;
	int j;
	#pragma omp parallel for num_threads(thread_count)\
		default(none) private(i,j) shared(A,B,X,D1,D2)
 	for (i=0; i<D1; i=i+1){
 		GET_TIME(tmp3);
	    X[i]=0.;
	    for (j=0; j<D2; j=j+1){
	        X[i]=(X[i])+((A[i][j])*(B[j]));
	    }
	    GET_TIME(tmp4);
	    total=total+(tmp4-tmp3);
	}
	GET_TIME(tmp2);
	printf("%d x %d | hilos = %d\n",D1,D2,thread_count );
	printf("Se termino en : %f , eficiencia %f\n",tmp2-tmp1, total/((tmp2-tmp1)*thread_count));
	return 0;
}