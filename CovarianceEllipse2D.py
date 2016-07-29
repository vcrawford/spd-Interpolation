import matplotlib.pyplot as plt
from matplotlib.patches import Ellipse
import matplotlib.gridspec as gridspec
import numpy as np
import numpy.random as rnd
import numpy.linalg as la
import math as m

#represent an eigenvector and its corresponding eigenvalue
class Eigenvector:
	def __init__(self, vector, eigenvalue):
		#list that is the eigenvector
		self.vector = vector
		#corresponding eigenvalue
		self.eigenvalue = eigenvalue

		if len(vector) == 2:
			x = vector[0]
			y = vector[1]
			if x > 0 and y > 0:
				self.quad = 1
			elif x < 0 and y > 0:
				self.quad = 2
			elif x < 0:
				self.quad = 3
			else:
				self.quad = 4
#end
	
#take in a list of eigenvectors and return the corresponding ellipse	
def getEllipse2D(eigenvectors):

	#print eigenvectors[0].vector
	#print eigenvectors[0].eigenvalue
	#print eigenvectors[1].vector
	#print eigenvectors[1].eigenvalue
	#print

	first_eigenvector = eigenvectors[0].vector
	first_eigenvector_norm = la.norm(first_eigenvector)
	second_eigenvector = eigenvectors[1].vector
	second_eigenvector_norm = la.norm(second_eigenvector)
	#dot product of eigenvectors[0] and [1, 0, 0, ...] is first element

	angle = np.rad2deg(np.arccos(first_eigenvector[0]/first_eigenvector_norm))

	if eigenvectors[0].quad > 2:
		angle = 360 - angle

	#print angle
	#print eigenvectors[0].quad
	#print

	return Ellipse(xy=[0, 0], width=eigenvectors[0].eigenvalue*2, 
	               height=eigenvectors[1].eigenvalue*2, angle=angle, alpha=0.4)
#end

#Take in a list of ellipses and plot them all
def plotEllipses(ellipses, filename, rows, cols, max_x, max_y):

	fig, ax = plt.subplots(rows, cols)

	k = 0
	for i, a in enumerate(ax):
		for j, b in enumerate(a):
			b.axis([-max_x, max_x, -max_y, max_y])
			b.axis('off')
			b.set_aspect('equal')
			if len(ellipses) > k:
				b.add_artist(ellipses[k])
			k = k + 1

	fig.tight_layout()		
	plt.subplots_adjust(wspace=0, hspace=0)
	plt.savefig(filename)

