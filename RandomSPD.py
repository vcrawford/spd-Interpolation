#run as "python RandomSPD.py 3 matrix1-3D.txt"
import numpy as np
import numpy.linalg as la
import numpy.random as rand
import sys

dims = int(sys.argv[1])
filename = sys.argv[2]

#Generate random SPD
rand_mx = rand.rand(dims, dims)
rand_mx = np.dot(rand_mx, rand_mx.transpose())

#Sanity check
eigvals = la.eigvals(rand_mx)
if len(filter(lambda x: x <= 0, eigvals)) is not 0:
	raise Exception("An SPD matrix was not successfully generated.")

print "Generated matrix:"
print rand_mx
print "Wrote matrix to " + filename

f = open(filename, 'w')
for row in rand_mx:
	for entry in row:
		f.write(str(entry) + ",")

f.close()
