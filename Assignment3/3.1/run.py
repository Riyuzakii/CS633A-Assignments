import os, sys
import subprocess
n_spec = [11, 52, 100]
n_nodes = [2, 4, 8]
args = []
args.append([])
args.append([])
args.append([])
args[0].append(["100", "100","200", "2", "2", "4", "1", "F", "output/"])
args[1].append(["100", "200","200", "2", "4", "4", "1", "F", "output/"])
args[2].append(["200", "200","200", "4", "4", "4", "1", "F", "output/"])

for n in range(3):
	subprocess.call(["python", "../jobscript.py", "hostfile",str(n_nodes[n])])
	for j in n_spec:
		print n_nodes[n]*8,j
		for k in range(10):
			cmd_list = ["mpiexec", "-n",str(n_nodes[n]*8), "-f","hostfile", "./S3D-IO/s3d_io.x"] + args[n][0]
			cmd_list.append(str(j))
			# print cmd_list
			# subprocess.call(cmd_list)	
			output = subprocess.check_output(cmd_list)
			#print len(output)
			#print type(output)
			band = str(output[-50:]).split(" ")
			print band[len(band)-2], band[len(band)-1]
			#sys.exit(0)
