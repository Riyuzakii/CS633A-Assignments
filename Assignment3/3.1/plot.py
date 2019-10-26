import os, sys
import numpy as np
import matplotlib.pyplot as plt
n_nodes = [2, 4, 8]
data = np.loadtxt("output.txt", dtype='str')
spec100 = [1,2,3,4,5,6,7,8,9,0]
spec11 = [1,2,3,4,5,6,7,8,9,0]
spec52 = [1,2,3,4,5,6,7,8,9,0]

for i in range(3):	
	fig = plt.figure()
	ax = fig.add_subplot(111)
	for j in range(1,11):
		spec11[j-1] =  float(data[j+i*33][0])
		spec52[j-1] =  float(data[j+11+i*33][0])
		spec100[j-1] = float(data[j+22+i*33][0])
	# print type(spec11)
	# print type(spec52)
	# print type(spec100)
	# sys.exit(0)
	ax.boxplot([spec11, spec52,spec100], labels=['11', '52', '100'])
	plt.xlabel('Number of Species', fontsize=14)
	plt.ylabel('Bandwidth in MiB/s', fontsize=14)
	fig.suptitle(str(n_nodes[i]*8)+ "Procs", fontsize=20)
	fig1 = plt.gcf()
	image_name = 'plot-'+str(n_nodes[i]*8)+'.pdf'
	fig1.savefig(image_name, dpi=150,quality=50)
	plt.show()