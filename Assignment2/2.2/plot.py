import sys
import matplotlib.pyplot as plt
import numpy as np 
op_file=sys.argv[1]
D=int(sys.argv[2])
values = np.loadtxt(op_file, dtype=float, skiprows=13, usecols=7)
print values

xticks=['1 MB','4 MBs','16 MBs', '64 MBs', '256 MBs', '512 MBs', '1024 MBs']
x=[1,2,3,4,5, 6, 7]
# for i in range(5):
# 	y[i] = y[0]/y[i]
fig = plt.figure()
# plt.plot(x,values)
plt.boxplot(values)
plt.xticks(x,xticks)
for a,b in zip(x, values):
	plt.text(a, b, str(('%.6f' % b)))

# plt.gca().legend(('PP_reduce','MPI_reduce'))
fig.suptitle('Exec time Plot-' + str(D) + 'Processes!', fontsize=20)
plt.xlabel('No. of MBs', fontsize=14)
plt.ylabel('Execution Time', fontsize=14)
image_name =  './perf-'+ str(D) + '.png'
plt.savefig(image_name, dpi=300,quality=50)
plt.show()
