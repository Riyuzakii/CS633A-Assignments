import sys
import matplotlib.pyplot as plt
import numpy as np 
op_file_pp=sys.argv[1]
op_file_coll=sys.argv[2]
D=int(sys.argv[3])

values = np.loadtxt(op_file_pp, dtype=float, skiprows=13, usecols=(7))
print values
values_coll = np.loadtxt(op_file_coll, dtype=float, skiprows=13, usecols=(7))
print values_coll
# sys.exit(0)

xticks=['1 Node','2 Nodes','4 Nodes','8 Nodes' ,'16 Nodes']
x=[1,2,3,4,5]
# for i in range(5):
# 	y[i] = y[0]/y[i]
fig = plt.figure()
plt.plot(x,values)
plt.plot(x,values_coll)

plt.xticks(x,xticks)
for a,b in zip(x, values):
	plt.text(a, b, str(('%.6f' % b)))
for a,b in zip(x, values_coll):
	plt.text(a, b, str(('%.6f' % b)))

plt.gca().legend(('PP','Collective'))
fig.suptitle('Exec time Plot-' + str(D) + 'KB!', fontsize=20)
plt.xlabel('No. of Nodes', fontsize=14)
plt.ylabel('Execution Time', fontsize=14)
image_name =  './perf-'+ str(D) + '.png'
plt.savefig(image_name, dpi=300,quality=50)
plt.show()
