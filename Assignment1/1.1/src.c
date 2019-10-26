#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <mpi.h>
int main( int argc, char *argv[])
{
	int D = atoi(argv[1]); //Take the number of bytes to be produced/consumed as argument
	int myrank;
	MPI_Status status;
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &myrank );
	MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);
	srand(time(NULL));
	double tbeg = MPI_Wtime ();
	if (myrank%2 == 0)    /* code for even processes (SENDERS) */
	{
		double *msend=malloc(D*128*sizeof(double));
		for(int j=0;j<128*D;j++)
		{
			msend[j] = rand()%128;
		}
		int error_code = MPI_Send(msend,128*D, MPI_DOUBLE, myrank+1, myrank, MPI_COMM_WORLD);
		if (error_code != MPI_SUCCESS) //ERROR TRAPING
		{
			char error_string[BUFSIZ];
			int length_of_error_string;

			MPI_Error_string(error_code, error_string, &length_of_error_string);
			printf("%3d: %s\n", myrank, error_string);//Print error string with rank of process that caused the error
		}
	}
	else if (myrank%2 == 1)  /* code for odd processes (RECEIVERS) */
	{
		double *mrec=malloc(D*128*sizeof(double));
		int error_code = MPI_Recv(mrec, 128*D, MPI_DOUBLE, myrank-1, myrank-1, MPI_COMM_WORLD, &status);
		if (error_code != MPI_SUCCESS)//Error TRAPING
		{
			char error_string[BUFSIZ];
			int length_of_error_string;

			MPI_Error_string(error_code, error_string, &length_of_error_string);
			printf("%3d: %s\n", myrank, error_string);//Print error string with rank of process that caused the error
		}
	}

	double elapsedTime = MPI_Wtime() - tbeg;
	double totalTime;
	MPI_Reduce( &elapsedTime, &totalTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD );//Collect exec time from all processes and find the max
	if ( myrank == 0 ) {
		printf( "Total time spent in seconds is %f\n", totalTime );
	}
	MPI_Finalize();
	return 0;
}
