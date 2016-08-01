import RotateVectors as rv
import sys
import numpy as np
import numpy.linalg as la

theta = float(sys.argv[1])
phi = float(sys.argv[2])
alpha = float(sys.argv[3])

eigenvalues = []
eigenvalues.append(float(sys.argv[4]))
eigenvalues.append(float(sys.argv[5]))
eigenvalues.append(float(sys.argv[6]))

filename = sys.argv[7]

eigenvectors = rv.rotateAxis(theta, phi, alpha)
eigen_vec_arr = np.column_stack(eigenvectors)
eigen_vec_arr_inv = la.inv(eigen_vec_arr)

eigen_val_arr = np.zeros((3, 3))
for i, val in enumerate(eigenvalues):
	eigen_val_arr[i][i] = val

spd = np.dot(eigen_vec_arr, np.dot(eigen_val_arr, eigen_vec_arr_inv))

spd_eigvals = la.eig(spd)[0]
if len(filter(lambda x: x <= 0, spd_eigvals)) is not 0:
	raise Exception("A valid SPD matrix was not generated")

f = open(filename, 'w')
for row in spd:
	for entry in row:
		if abs(entry - 0.0) < 0.00001:
			f.write(str(0.0) + ",")
		else:
			f.write(str(entry) + ",")



