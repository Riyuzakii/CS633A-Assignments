import sys, os, subprocess
from modules import plot
from modules import createHost

assignment = sys.argv[1]	
print "Assignment Sup-part:", assignment
os.chdir(r"./"+str(assignment)+"/")
subprocess.call(['make'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
os.chdir(r"../")
procs = [8, 16, 32, 64, 128]
D = [1, 512, 1024]
HF_name = './' + str(assignment) + '/hostfile'
src_File = './' + str(assignment) + '/src.x'

times1 = [];times512 = [];times1024 = [];
for x in range(5):
	createHost.create(HF_name, procs[x])
	for y in range(3):	
		op = subprocess.check_output(['mpiexec','-n',str(procs[x]),'-f',HF_name, src_File, str(D[y])],shell=False,stderr=subprocess.STDOUT)
		if y == 0:
			times1.append(float(str(op[31:-1])))
		elif y == 1:
			times512.append(float(str(op[31:-1])))
		elif y == 2:
			times1024.append(float(str(op[31:-1])))
   
plot.plotter(assignment, D[0], times1)
plot.plotter(assignment, D[1], times512)
plot.plotter(assignment, D[2], times1024)
# print times1024
# print times512
# print times1
