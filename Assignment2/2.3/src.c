#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
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
	double tbeg = MPI_Wtime ();

	int size_dt = 128*1024;
	// Point-to-Point reduce
	double *msend = malloc(D*size_dt*sizeof(double));
	int j;
	for( j=0;j<size_dt*D;j++){
		msend[j] = rand()%10;
	}
	
	if(myrank != 0){
		int error_code = MPI_Send(msend,size_dt*D, MPI_DOUBLE, 0,99, MPI_COMM_WORLD);
	
		if (error_code != MPI_SUCCESS) //ERROR TRAPING
		{
			char error_string[BUFSIZ];
			int length_of_error_string;
	
			MPI_Error_string(error_code, error_string, &length_of_error_string);
			printf("%3d: %s\n", myrank, error_string);//Print error string with rank of process that caused the error
		}
	}
	else{
		double *mrecv = malloc(D*size_dt*sizeof(double));
		int z;
		for( z=1; z<N; z++){
			int error_code = MPI_Recv(mrecv, size_dt*D, MPI_DOUBLE, z, 99, MPI_COMM_WORLD, &status);
			if (error_code != MPI_SUCCESS) //ERROR TRAPING
			{
				char error_string[BUFSIZ];
				int length_of_error_string;
		
				MPI_Error_string(error_code, error_string, &length_of_error_string);
				printf("%3d: %s\n", myrank, error_string);//Print error string with rank of process that caused the error
			}
			int i;
			for (i = 0; i < D*size_dt; ++i)
			{
				msend[i] = msend[i]*mrecv[i];
			}
		}
		free(mrecv);
	}
	
	free(msend);
	double elapsedTime = MPI_Wtime() - tbeg;
	double totalTime;
	MPI_Reduce( &elapsedTime, &totalTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD );//Collect exec time from all processes and find the max
	
	//Collective reduce
	double tbeg_coll = MPI_Wtime ();
	double *msend_coll = malloc(D*size_dt*sizeof(double));
	double *mrecv_coll = malloc(D*size_dt*sizeof(double));
	for( j=0;j<size_dt*D;j++){
		msend_coll[j] = rand()%10;
	}
	MPI_Reduce(msend_coll, mrecv_coll, size_dt*D, MPI_DOUBLE, MPI_PROD, 0, MPI_COMM_WORLD);
	free(mrecv_coll);
	free(msend_coll);	
	double elapsedTime_coll = MPI_Wtime() - tbeg_coll;
	double totalTime_coll;
	MPI_Reduce( &elapsedTime_coll, &totalTime_coll, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD );//Collect exec time from all processes and find the max

	if ( myrank == 0 ) {
		printf( "Total time spent for PP in seconds is %f\n", totalTime );
		printf( "Total time spent for Coll in seconds is %f\n", totalTime_coll );
	}
	MPI_Finalize();
	return 0;
}
