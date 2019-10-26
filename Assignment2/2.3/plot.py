import sys
import matplotlib.pyplot as plt
import numpy as np 
op_file=sys.argv[1]
D=int(sys.argv[2])
values = np.loadtxt(op_file, dtype=(str,float), skiprows=13, usecols=(5,9))
print values
pp_list = []
coll_list = []
for i in range(10):
	if values[i][0] == 'PP':
		pp_list.append(float(values[i][1]))
	else:
		coll_list.append(float(values[i][1]))
print pp_list
print coll_list

xticks=['1 Node','2 Nodes','4 Nodes','8 Nodes' ,'16 Nodes']
x=[1,2,3,4,5]
# for i in range(5):
# 	y[i] = y[0]/y[i]
fig = plt.figure()
plt.plot(x,pp_list)
plt.plot(x,coll_list)
plt.xticks(x,xticks)
for a,b in zip(x, pp_list):
	plt.text(a, b, str(('%.6f' % b)))
for a,b in zip(x, coll_list):
	plt.text(a, b, str(('%.6f' % b)))

plt.gca().legend(('PP_reduce','MPI_reduce'))
fig.suptitle('Exec time Plot-' + str(D) + 'MB!', fontsize=20)
plt.xlabel('No. of Nodes', fontsize=14)
plt.ylabel('Execution Time', fontsize=14)
image_name =  './perf-'+ str(D) + '.png'
plt.savefig(image_name, dpi=300,quality=50)
plt.show()
