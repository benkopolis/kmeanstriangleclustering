#!/bin/python

import sys
import random

if len(sys.argv) < 4:
	print 'Provide number of non zero dimensions, number of dimensions and ouput file path, in this order.'
else:
	num_dim = int(sys.argv[2])
	# 16% of dimensions will be non zero
	non_zero = int(sys.argv[1])
	delta = 0.0
	while True:
		delta = random.random() / 2.0
		if delta > 0.0:
			break
	num_vec = int(float(num_dim - non_zero) / delta)  
	print "Num vec: %d , delta: %f "%(num_vec, delta)

	out = open(sys.argv[3], 'w')
	out.write("{0} {1}\n".format(num_vec, num_dim))

	for vec_index in range(0, num_vec):
		first_non_zero = (float(vec_index) * delta)
		int_first_nz = int(first_non_zero)
		nz_len = int_first_nz + int(non_zero)
		#print "first index: %d len: %d"%(int_first_nz, nz_len)
		for dim_index in range(0, num_dim):
			if dim_index >= int_first_nz and dim_index < nz_len:
				out.write("{0}:1 ".format(dim_index))
		out.write("\n")
	out.close()
