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
	int newrank, newsize, color = myrank%(N/4);//N/4 groups for every processor-consumer pair
	MPI_Comm newcomm;//New communicator
	MPI_Comm_split (MPI_COMM_WORLD, color, myrank, &newcomm);
	MPI_Comm_rank (newcomm, &newrank);
	MPI_Comm_size (newcomm, &newsize);
	int size_dt = 128;
	srand(time(NULL));

	double *msend = malloc(D*size_dt*sizeof(double));
	double *mrecv = malloc(3*3*D*size_dt*sizeof(double));
	int iter=0;
	for (iter = 0; iter < 1000; ++iter)
	{	
		int j=0;
		if(iter == 0){
			for(j=0;j<size_dt*D;j++)
				msend[j] = rand()%4096;
		}
		else{
			//j=0;
			for(j=0;j<size_dt*D;j++)
				msend[j] = msend[j]/2;
		}
		// int error_code = MPI_Igather(msend, size_dt*D, MPI_DOUBLE, mrecv, D*size_dt, MPI_DOUBLE, 3, newcomm, &request);
		int error_code = MPI_Gather(msend, size_dt*D, MPI_DOUBLE, mrecv, D*size_dt, MPI_DOUBLE, 3, newcomm);

		if (error_code != MPI_SUCCESS)//Error TRAPING
		{
			char error_string[BUFSIZ];
			int length_of_error_string;

			MPI_Error_string(error_code, error_string, &length_of_error_string);
			printf("%3d: %s\n", myrank, error_string);//Print error string with rank of process that caused the error
		}
	}
	free(mrecv);
	free(msend);

	double elapsedTime = MPI_Wtime() - tbeg;
	MPI_Comm_free (&newcomm);
	double totalTime;
	MPI_Reduce( &elapsedTime, &totalTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD );//Collect exec time from all processes and find the max
	if ( myrank == 0 ) {
		printf( "Maximum time spent in seconds is %f\n", totalTime );
	}

	MPI_Finalize();
	return 0;
}
