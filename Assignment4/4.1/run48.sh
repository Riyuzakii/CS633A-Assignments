#!/bin/bash

python jobscript.py hostfile 48
mkdir -p traces-pre-opt/48p

mpirun -np 48 -f hostfile parmetis parmetis/Graphs/rotor.graph 1 6 1 1 6 1
cd traces-pre-opt
pprof -s > 48p/161161.txt
rm -rf profile.* 
cd ..

mpirun -np 48 -f hostfile parmetis parmetis/Graphs/rotor.graph 1 12 1 1 6 1
cd traces-pre-opt
pprof -s > 48p/1121161.txt
rm -rf profile.* 
cd ..


mpirun -np 48 -f hostfile parmetis parmetis/Graphs/rotor.graph 2 12 1 1 6 1
cd traces-pre-opt
pprof -s > 48p/2121161.txt
rm -rf profile.* 
cd ..

mpirun -np 48 -f hostfile parmetis parmetis/Graphs/rotor.graph 2 6 1 1 6 1
cd traces-pre-opt
pprof -s > 48p/261161.txt
rm -rf profile.* 
cd ..
