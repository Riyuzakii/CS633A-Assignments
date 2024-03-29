#! /bin/bash
#PBS -N src
#PBS -q courses
#PBS -j oe
#PBS -l walltime=00:30:00
#number of nodes here is 32 ppn is 8 as each node allows 8 cores
#PBS -l nodes=16:ppn=8
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
mpirun -l -machinefile hostfile -np 8 ./src.x 1 
mpirun -l -machinefile hostfile -np 16 ./src.x 1
mpirun -l -machinefile hostfile -np 32 ./src.x 1
mpirun -l -machinefile hostfile -np 1 ./src.x 1
mpirun -l -machinefile hostfile -np 128 ./src.x 1
# echo `date`
#mpirun -l -machinefile hostfile -np 24 ./fileWr.x 8388608
#echo `date`
