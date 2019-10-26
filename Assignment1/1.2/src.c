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
	MPI_Request request = MPI_REQUEST_NULL;
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &myrank );
	MPI_Comm_size(MPI_COMM_WORLD, &N);
	MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);//Error_handler
	double tbeg = MPI_Wtime ();
	int newrank, newsize, color = myrank%(N/2);//N/2 groups for every processor-consumer pair
	MPI_Comm newcomm;//New communicator
	MPI_Comm_split (MPI_COMM_WORLD, color, myrank, &newcomm);
	MPI_Comm_rank (newcomm, &newrank);
	MPI_Comm_size (newcomm, &newsize);

	srand(time(NULL));
	double *msend=malloc(D*128*sizeof(double));
	for(int j=0;j<128*D;j++)
	{
		msend[j] = rand()%128;
	}
	int error_code = MPI_Ibcast(msend, 128*D, MPI_DOUBLE, newrank, newcomm, &request);

	if (error_code != MPI_SUCCESS)//Error TRAPING
		{
			char error_string[BUFSIZ];
			int length_of_error_string;

			MPI_Error_string(error_code, error_string, &length_of_error_string);
			printf("%3d: %s\n", myrank, error_string);//Print error string with rank of process that caused the error
		}
	
	double elapsedTime = MPI_Wtime() - tbeg;
	MPI_Comm_free (&newcomm);
	double totalTime;
	MPI_Reduce( &elapsedTime, &totalTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD );//Collect exec time from all processes and find the max
	if ( myrank == 0 ) {
		printf( "Total time spent in seconds is %f\n", totalTime );
	}

	MPI_Finalize();
	return 0;
}
