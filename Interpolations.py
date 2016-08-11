#A collection of functions for doing SPD interpolations
import numpy as np
import numpy.linalg as la

#Given an interpolation xml thing, return a list of lists
#corresponding to the matrices inside.
def parseMatrices(interpolation):
	matrices = []

	for matrix_xml in interpolation:
		matrix = []

		for row in matrix_xml:
			matrix.append(map(float, row.text.split(",")))

		matrices.append(matrix)

	return matrices

#Given an interpolation, compute the array of weights that corresponds 
#to each matrix in the interpolation. Each weight is how much the final
#matrix is weighted in that matrix
def interpolationWeights(interpolation):
	matrix_count = len(interpolation)
	return np.linspace(0.0, 1.0, matrix_count)

#Compute the fractional anisotropy of a matrix
def computeFractionalAnisotropy(matrix):
	eigvals = la.eigvals(matrix)

	#compute average eigenvalue
	eigval_avg = np.mean(eigvals)

	#get the top part of the FA
	variances = map(lambda x: np.square(x - eigval_avg), eigvals)
	top = np.sqrt(np.sum(variances))

	#and the bottom
	bottom = np.sqrt(np.sum(map(lambda x: np.square(x), eigvals)))

	return np.sqrt(3/2)*(top/bottom)

#Return a list of the fractional anisotropies of each matrix in the 
#input list
def computeFractionalAnisotropyList(matrices):
	return map(computeFractionalAnisotropy, matrices)


