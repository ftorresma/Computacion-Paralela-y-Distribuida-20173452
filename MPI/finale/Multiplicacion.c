#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>

#define TAM 20

void Mat_vect_mult(double local_A[],
	double local_x[],
	double local_y[],
	int local_m,
	int n,
	int local_n,
	MPI_Comm comm ) {
	double* x;
	int local_i;
	int local_ok = 1;

	x = malloc(n*sizeof(double));
	MPI_Allgather(local_x, local_n, MPI_DOUBLE,x, local_n, MPI_DOUBLE, comm);

	for (local_i = 0; local_i < local_m; local_i++) {
		local_y[local_i] = 0.0;
		for (int j = 0; j < n; j++){
			local_y[local_i] += local_A[local_i*n+j]*local_x[j];
		}
	}
	free(x);
}

int main(int argc, char** argv){
	double localA[TAM*TAM],localX[TAM*TAM],localY[TAM*TAM];
	int mpi_rank,mpi_size;
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);

	for (int i=0; i<TAM*TAM; i++){
	    localA[i]= 1;
		localX[i]= 1;
	    }

	double start = MPI_Wtime();
	Mat_vect_mult(localA,localX,localY,
		TAM,TAM*TAM,TAM,MPI_COMM_WORLD);
	double finish = MPI_Wtime();
	printf("Terminado en %f segundos.\n", finish - start);


	return 0;
}
