#!/usr/bin/env python

"""List all hosts with their IP adress of the current network."""

import os, sys, subprocess
if sys.argv[2] == "":
	print "Please provide the number of nodes as an argument!"
	sys.exit(0)
cnt = 0
wanted = int(sys.argv[2])
if wanted == 0:
	print "We don't cater to 0 nodes!"
	sys.exit(0)
if sys.argv[1] == "":
	print "Provide the hostfile name in the argument!"
	sys.exit(0)

with open(sys.argv[1], 'w') as hostfile:
	for i in range(1, 30):
		ip = '172.27.19.' + str(i)
		if ip[:9] == '172.27.19':
			try:
				subprocess.check_call(["ssh", ip, "date"])
			except subprocess.CalledProcessError:
				print "error"
				continue
			hostfile.write('%s:8\n' % ip)
			cnt += 1 # Count number of nodes with ip starting with 172.27.19.X
		if cnt == wanted:
			break
