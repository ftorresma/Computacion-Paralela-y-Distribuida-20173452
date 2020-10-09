#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char** argv){
	const int PING_PONG=10;
	int mpi_rank,mpi_size;
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
	if(mpi_size != 2){
		printf("El tamaño debe de ser 2\n");
		MPI_Abort(MPI_COMM_WORLD,1);
	}
	int p_rango = (mpi_rank+1)%2;
	int golpes1=0;
	int golpes2=0;
	int i=0;
	while(i<PING_PONG)
	{
		if(mpi_rank==i%2)
		{
			i++;
			MPI_Send(&i, 1,MPI_INT,p_rango,0,MPI_COMM_WORLD);
			golpes1++;
			printf("jugador %d le pego a la pelota, lleva %d golpes\n",mpi_rank,golpes1);
		}
		else{	
			MPI_Recv(&i, 1,MPI_INT,p_rango,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			golpes2++;
			printf("jugador %d le pego a la pelota, lleva %d golpes\n",mpi_rank,golpes2 );
		}
	}
	MPI_Finalize();
	return 0;
}