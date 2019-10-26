import sys
import matplotlib.pyplot as plt
def plotter( assignment, D, y = []):
	xticks=['1 Node','2 Nodes','4 Nodes','8 Nodes' ,'16 Nodes']
	x=[1,2,3,4,5]
	# for i in range(5):
	# 	y[i] = y[0]/y[i]
	fig = plt.figure()
	plt.plot(x,y)
	plt.xticks(x,xticks)
	for a,b in zip(x, y):
		plt.text(a, b, str(('%.6f' % b)))
	fig.suptitle('Exec time Plot-' + str(D) + 'Bytes!', fontsize=20)
	plt.xlabel('No. of Nodes', fontsize=14)
	plt.ylabel('Executioin Time', fontsize=14)
	image_name = './' + str(assignment)+ '/perf-'+ str(D) + '.png'
	plt.savefig(image_name, dpi=300,quality=50)
	plt.show()
