#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <mpi.h>
int main( int argc, char *argv[])
{
	int D = atoi(argv[1]); //Take the number of bytes to be produced/consumed as argument
	int myrank, N;
	MPI_Status status;
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &myrank );
	MPI_Comm_size(MPI_COMM_WORLD, &N);
	MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);
	srand(time(NULL));
	int iter;
	for(iter=0; iter< 10; iter++){	
		double tbeg = MPI_Wtime ();

		double *msend=malloc(D*128*1024*sizeof(double));
		double *mrec=malloc(D*128*1024*sizeof(double));
		for(int j=0;j<128*D*1024;j++)
		{
			msend[j] = rand()%128;
		}
		int z, x;
		for(z =0;z<N; z++){
			if(myrank == z){	// Every process sends to every other process
				for(x=0;x<N; x++){
					if(z == x)
						continue;
					MPI_Send(msend,128*D*1024, MPI_DOUBLE, x, z, MPI_COMM_WORLD);
				}
			}
			else{	// Every process recieves from the process that sent from above conditional
					MPI_Recv(mrec, 128*D*1024, MPI_DOUBLE, z, z, MPI_COMM_WORLD, &status);
			}	
		}
		free(msend);
		free(mrec);
		double elapsedTime = MPI_Wtime() - tbeg;
		double totalTime;
		MPI_Reduce( &elapsedTime, &totalTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD );//Collect exec time from all processes and find the max
		if ( myrank == 0 ) {
			printf("Avg bandwidth is %d\n",N*D*1024*1024/(totalTime*2) );
			printf( "Total time spent in seconds is %f\n", totalTime );
		}
		free(msend);
		free(mrec);
	}
	MPI_Finalize();
	return 0;
}
