
import os, sys, subprocess
def create(HF_name, procs):
	cnt = 0
	wanted = int(procs)
	if wanted == 0:
		print "We don't cater to 0 nodes!"
		sys.exit(0)
	HF_loc = "../" + str(HF_name) 
	with open(HF_name, 'w') as hostfile:
		for i in range(1, 30):
			ip = '172.27.19.' + str(i)
			if ip[:9] == '172.27.19':
				try:
					subprocess.check_call(["ssh", ip, "date"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
				except subprocess.CalledProcessError:
					print "error"
					continue
				hostfile.write('%s:8\n' % ip)
				cnt += 1 # Count number of nodes with ip starting with 172.27.19.X
			if cnt == wanted/8:
				break
