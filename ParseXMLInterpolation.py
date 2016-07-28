import xml.etree.ElementTree as et
import CovarianceEllipse2D as ell
import numpy as np
import numpy.linalg as la

#string of the form 2.4, 3, ... mapped to list of floats
'''
def parseEigenvector(vec_string):
	return map(float, vec_string.split(","))
#end
'''

#Return interpolation ellipses (for matplotlib) from xml file
'''
def parseInterpolation(file_name):

	interp_xml = et.parse(file_name)

	interpolations = interp_xml.getroot()

	#array of ellipses (artists) for matplotlib
	ellipses = []

	for interpolation in interpolations:
		for matrix in interpolation:
			eigenvalues = matrix[0]
			eigenvectors = matrix[1]
			together = []

			for i, eigenvalue in enumerate(eigenvalues):
				eigenvector = parseEigenvector(eigenvectors[i].text)
				eigenvector_object = ell.Eigenvector(eigenvector, 
														    float(eigenvalue.text))
				together.append(eigenvector_object)

			ellipses.append(ell.getEllipse2D(together))

	return ellipses
#end
'''

def parseInterpolation(file_name):

	interp_xml = et.parse(file_name)

	interpolations = interp_xml.getroot()

	#array of ellipses (artists) for matplotlib
	ellipses = []

	for interpolation in interpolations:
		for matrix in interpolation:
			np_mat = []

			for row in matrix:
				np_mat.append(map(float, row.text.split(",")))

			eigens = la.eig(np_mat)
			#print np_mat
			#print "Eigenvectors:"
			#print eigens[1]
			#print "Eigenvalues:"
			#print eigens[0]
			#print
			eigens_obj = []
			for i in range(len(eigens[0])):
				vec = ell.Eigenvector(eigens[1][:,i], eigens[0][i])
				eigens_obj.append(vec)

			ellipses.append(ell.getEllipse2D(eigens_obj))

	return ellipses
#

