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
	double *msend=malloc(D*128*sizeof(double));
	double *mrec1=malloc(D*128*sizeof(double));
	double *mrec2=malloc(D*128*sizeof(double));
	double *mrec3=malloc(D*128*sizeof(double));
	int j, iter;
	for(j=0;j<128*D;j++)
	{
		msend[j] = (rand()%128);
	}
	for(iter=0; iter<1; iter++)
	{
		if (myrank%4 != 3)    /* code for even processes (SENDERS) */
		{	
			int j;
			for(j=0;j<128*D;j++)
			{
				msend[j] = msend[j]/2;
			}		
			int index = myrank%4;
			int error_code = MPI_Send(msend,128*D, MPI_DOUBLE, myrank+3-index, myrank - index, MPI_COMM_WORLD);
			if (error_code != MPI_SUCCESS) //ERROR TRAPING
			{
				char error_string[BUFSIZ];
				int length_of_error_string;

				MPI_Error_string(error_code, error_string, &length_of_error_string);
				printf("%3d: %s\n", myrank, error_string);//Print error string with rank of process that caused the error
			}
		}
		else if (myrank%4 == 3)  /* code for odd processes (RECEIVERS) */
		{
			int error_code = MPI_Recv(mrec1, 128*D, MPI_DOUBLE, myrank-3, myrank-3, MPI_COMM_WORLD, &status);
			if (error_code != MPI_SUCCESS)//Error TRAPING
			{
				char error_string[BUFSIZ];
				int length_of_error_string;

				MPI_Error_string(error_code, error_string, &length_of_error_string);
				printf("%3d: %s\n", myrank, error_string);//Print error string with rank of process that caused the error
			}
			error_code = MPI_Recv(mrec2, 128*D, MPI_DOUBLE, myrank-2, myrank-3, MPI_COMM_WORLD, &status);
			if (error_code != MPI_SUCCESS)//Error TRAPING
			{
				char error_string[BUFSIZ];
				int length_of_error_string;

				MPI_Error_string(error_code, error_string, &length_of_error_string);
				printf("%3d: %s\n", myrank, error_string);//Print error string with rank of process that caused the error
			}
			error_code = MPI_Recv(mrec3, 128*D, MPI_DOUBLE, myrank-1, myrank-3, MPI_COMM_WORLD, &status);
			if (error_code != MPI_SUCCESS)//Error TRAPING
			{
				char error_string[BUFSIZ];
				int length_of_error_string;

				MPI_Error_string(error_code, error_string, &length_of_error_string);
				printf("%3d: %s\n", myrank, error_string);//Print error string with rank of process that caused the error
			}
		}
	}
	free(msend);
    free(mrec1);
    free(mrec2);
    free(mrec3);
	double elapsedTime = MPI_Wtime() - tbeg;
	double totalTime;
	MPI_Reduce( &elapsedTime, &totalTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD );//Collect exec time from all processes and find the max
	if ( myrank == 0 ) {
		printf( "Maximum time spent in seconds is %f\n", totalTime );
	}
	MPI_Finalize();
	return 0;
}
