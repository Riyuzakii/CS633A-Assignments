#! /bin/bash
#PBS -N fileWr
#PBS -q courses
#PBS -j oe
#PBS -l walltime=00:30:00
#number of nodes here is 64 .pn is 8 as each node allows 8 cores
#PBS -l nodes=8:ppn=8
#merge output and error into a single job_name.number_of_job_in_queue.
#PBS -j oe
#export fabric infiniband related variables
export I_MPI_FABRICS=shm:tmi
export I_MPI_DEVICE=rdma:OpenIB-cma
#change directory to where the job has been submitted from
cd $PBS_O_WORKDIR
#source paths
source /opt/software/intel/initpaths intel64
sort $PBS_NODEFILE > hostfile
echo `date`
#mpirun -l -f hostfile -np 64 ./S3D-IO/s3d_io.x 400 400 400 4 4 4 1 F output/ 11 
#mpirun -l -f hostfile -np 64 ./S3D-IO/s3d_io.x 400 400 400 4 4 4 1 F output/ 11
#mpirun -l -f hostfile -np 64 ./S3D-IO/s3d_io.x 400 400 400 4 4 4 1 F output/ 11
#mpirun -l -f hostfile -np 64 ./S3D-IO/s3d_io.x 400 400 400 4 4 4 1 F output/ 11
#mpirun -l -f hostfile -np 64 ./S3D-IO/s3d_io.x 400 400 400 4 4 4 1 F output/ 11
#mpirun -l -f hostfile -np 64 ./S3D-IO/s3d_io.x 400 400 400 4 4 4 1 F output/ 52
mpirun -l -f hostfile -np 64 ./S3D-IO/s3d_io.x 400 400 400 4 4 4 1 F output/ 52
mpirun -l -f hostfile -np 64 ./S3D-IO/s3d_io.x 400 400 400 4 4 4 1 F output/ 52
mpirun -l -f hostfile -np 64 ./S3D-IO/s3d_io.x 400 400 400 4 4 4 1 F output/ 52
mpirun -l -f hostfile -np 64 ./S3D-IO/s3d_io.x 400 400 400 4 4 4 1 F output/ 52
mpirun -l -f hostfile -np 64 ./S3D-IO/s3d_io.x 400 400 400 4 4 4 1 F output/ 100
mpirun -l -f hostfile -np 64 ./S3D-IO/s3d_io.x 400 400 400 4 4 4 1 F output/ 100
mpirun -l -f hostfile -np 64 ./S3D-IO/s3d_io.x 400 400 400 4 4 4 1 F output/ 100
mpirun -l -f hostfile -np 64 ./S3D-IO/s3d_io.x 400 400 400 4 4 4 1 F output/ 100
mpirun -l -f hostfile -np 64 ./S3D-IO/s3d_io.x 400 400 400 4 4 4 1 F output/ 100
echo `date`
#mpirun -l -machinefile hostfile -np 44 ./fileWr.x 8388608
#echo `date`
