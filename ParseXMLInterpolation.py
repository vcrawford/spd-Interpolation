import xml.etree.ElementTree as et
import CovarianceEllipse2D as ell
import numpy as np
import numpy.linalg as la


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

