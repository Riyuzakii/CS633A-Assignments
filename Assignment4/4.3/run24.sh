#!/bin/bash

python jobscript.py hostfile 24
mkdir -p traces-post-opt/24p

mpirun -np 24 -f hostfile parmetis parmetis/Graphs/rotor.graph 1 6 1 1 6 1
cd traces-post-opt
pprof -s > 24p/161161.txt
rm -rf profile.* 
cd ..

mpirun -np 24 -f hostfile parmetis parmetis/Graphs/rotor.graph 1 12 1 1 6 1
cd traces-post-opt
pprof -s > 24p/1121161.txt
rm -rf profile.* 
cd ..


mpirun -np 24 -f hostfile parmetis parmetis/Graphs/rotor.graph 2 12 1 1 6 1
cd traces-post-opt
pprof -s > 24p/2121161.txt
rm -rf profile.* 
cd ..

mpirun -np 24 -f hostfile parmetis parmetis/Graphs/rotor.graph 2 6 1 1 6 1
cd traces-post-opt
pprof -s > 24p/261161.txt
rm -rf profile.* 
cd ..
