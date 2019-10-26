#!/bin/bash

python jobscript.py hostfile 72
mkdir -p traces-post-opt/72p

mpirun -np 72 -f hostfile parmetis parmetis/Graphs/rotor.graph 1 6 1 1 6 1
cd traces-post-opt
pprof -s > 72p/161161.txt
rm -rf profile.* 
cd ..

mpirun -np 72 -f hostfile parmetis parmetis/Graphs/rotor.graph 1 12 1 1 6 1
cd traces-post-opt
pprof -s > 72p/1121161.txt
rm -rf profile.* 
cd ..


mpirun -np 72 -f hostfile parmetis parmetis/Graphs/rotor.graph 2 12 1 1 6 1
cd traces-post-opt
pprof -s > 72p/2121161.txt
rm -rf profile.* 
cd ..

mpirun -np 72 -f hostfile parmetis parmetis/Graphs/rotor.graph 2 6 1 1 6 1
cd traces-post-opt
pprof -s > 72p/261161.txt
rm -rf profile.* 
cd ..
