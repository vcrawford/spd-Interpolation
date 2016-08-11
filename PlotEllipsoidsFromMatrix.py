import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import numpy.linalg as la
import itertools as it
import xml.etree.ElementTree as et

#An ellipsoid representing a covariance matrix 
class Ellipsoid:
	def __init__(self, matrix):
		eigenvalues, eigenvectors_matrix = la.eig(matrix)

		#print matrix
		#print eigenvalues
		#print eigenvectors_matrix

		#Numpy returns eigenvectors as columns of a matrix
		self.eigenvalues = eigenvalues
		self.eigenvectors = []
		self.eigenvectors.append(eigenvectors_matrix[:, 0])
		self.eigenvectors.append(eigenvectors_matrix[:, 1])
		self.eigenvectors.append(eigenvectors_matrix[:, 2])

		#All eigenvectors should be perpendicular to each other
		for i, eig1 in enumerate(self.eigenvectors):
			for j, eig2 in enumerate(self.eigenvectors):
				if i is not j:
					if abs(np.dot(eig1, eig2)) > 0.01:
						raise Exception("Not all input eigenvectors are orthogonal.")


		#We want to figure out what rotations would need to be made to transform the 
		#x, y, and z axes into the same directions as these eigenvectors
		#Using typical thumb rule from physics about rotation direction
		#In order to transform those axes, we would need to first rotate around the y-axis,
		#then around the z-axis, and finally around the x-axis

		#Choose any eigenvector to be the "direction" of the ellipse. This is where the 
		#x-axis will be rotated
		self.direction = self.eigenvectors[0]
		self.x_length = eigenvalues[0]
		#We can use this vector to find theta and phi
		self.y_rotate = getYRotation(self.direction)
		self.z_rotate = getZRotation(self.direction)

		#check that doing these rotation backwards works
		test = rotateAboutZ(self.direction, -self.z_rotate)
		test = rotateAboutY(test, -self.y_rotate)

		if abs(np.dot(test, np.array([1, 0, 0])) - 1) > 0.01:
			raise Exception("There is something wrong with computing the y and/or z rotations.")

		#Now choose the next eigenvector to be rotated to the positive y-axis
		rotate_to_y = self.eigenvectors[1]
		self.y_length = eigenvalues[1]
		#Do the transforms that would move the first eigenvector to the pos x-axis
		#We should now be in the YZ plane
		rotate_to_y = rotateAboutY(rotateAboutZ(rotate_to_y, -self.z_rotate), -self.y_rotate)

		if abs(np.dot(rotate_to_y, np.array([1, 0, 0]))) > 0.01:
			raise Exception("After the Z and Y rotations, the eigenvector to be rotated to " +
			  					 "the y-axis is not in the YZ plane.")

		#Find the rotation about the x-axis to bring the pos y-axis to this
		self.x_rotate = getXRotation(rotate_to_y)

		test = rotateAboutX(rotate_to_y, -self.x_rotate)
		if abs(abs(np.dot(test, np.array([0, 1, 0]))) - 1) > 0.01:
			raise Exception("Vector was not able to properly rotate to Y axis.")

		#The remaining eigenvector will be along the z axis
		self.z_length = eigenvalues[2]

	#END


#Rotate vec about the z axis theta degrees
def rotateAboutZ(vec, theta):
	theta = np.deg2rad(theta)
	rotate_matrix_z = np.array([[np.cos(theta), -np.sin(theta), 0], 
	                          	 [np.sin(theta), np.cos(theta), 0], 
									  	 [0, 0, 1]])
	return np.dot(rotate_matrix_z, vec)
#END


#Rotate each Vector3D value about the y axis theta degrees
def rotateAboutY(vec, theta):
	theta = np.deg2rad(theta)
	rotate_matrix_y = np.array([[np.cos(theta), 0, np.sin(theta)], 
   	                       [0, 1, 0], 
									  [-np.sin(theta), 0, np.cos(theta)]])
	return np.dot(rotate_matrix_y, vec)
#END


#Rotate each Vector3D value about the y axis theta degrees
def rotateAboutX(vec, theta):
	theta = np.deg2rad(theta)
	rotate_matrix_x = np.array([[1, 0, 0], 
   	                         [0, np.cos(theta), -np.sin(theta)], 
									    [0, np.sin(theta), np.cos(theta)]])
	return np.dot(rotate_matrix_x, vec)
#END


#Return this vector projected onto the XY axis
def getProjectXY(vec):
	return np.array([vec[0], vec[1], 0])
#END


#Phi is the angle of this vector with the XY plane
def getPhi(vec):
	xy_proj = getProjectXY(vec)
	return np.rad2deg(np.arccos((vec.dot(xy_proj))/(la.norm(vec)*la.norm(xy_proj))))
#END


#Theta is the angle of the projection of this vector onto the xy plane with the x axis
def getTheta(vec):
	xy_proj = getProjectXY(vec)
	x_axis = np.array([1, 0, 0])
	return np.rad2deg(np.arccos((x_axis.dot(xy_proj))/(la.norm(x_axis)*la.norm(xy_proj))))

#If this vector were to be projected onto the XZ plane, then how many degrees 
#about the Y axis must the pos X axis turn to align with it
def getYRotation(vec):
	y_rotate = getPhi(vec)
	if vec[2] > 0:
		y_rotate = 360 - y_rotate
	return y_rotate
#END

#If a vector were to be projected onto the XY plane, then how many degrees counter-clockwise
#about the Z axis must the x-axis turn to align with it
def getZRotation(vec):
	z_rotate = getTheta(vec)
	if vec[1] < 0:
		z_rotate = 360 - z_rotate
	return z_rotate
#END

#This assumes vec is in the YZ plane
#How many degrees must the pos y-axis be rotated about the x axis to be aligned with it
def getXRotation(vec):
	y_axis = np.array([0, 1, 0])
	x_rotate = np.rad2deg(np.arccos((np.dot(y_axis, vec))/(la.norm(y_axis)*la.norm(vec))))
	if vec[2] < 0:
		x_rotate = 360 - x_rotate
	return x_rotate
#END


# Plots each ellipsoid in ellipsoids (which is just a bunch of x, y, and z coordinates
# as a surface in a plot and then saves it
def plotEllipsoids(ellipsoids, num_rows, num_cols, filename, max_x, max_y, max_z):

	fig = plt.figure()
	subplots = []

	#Add 3D subplots
	for row in range(num_rows):
		for col in range(num_cols):
			subplot_num = row*num_cols + (col + 1)
			subplot = fig.add_subplot(num_rows, num_cols, subplot_num, projection='3d')
			subplot.axis('off')
			subplot.set_aspect('equal')
			subplot.set_xlim(-max_x, max_x)
			subplot.set_ylim(-max_y, max_y)
			subplot.set_zlim(-max_z, max_z)

			if ((subplot_num - 1) < len(ellipsoids)):
				ellipsoid = ellipsoids[subplot_num - 1]
				ellipse_points = getEllipsePoints(ellipsoid.x_length, ellipsoid.y_length, 
															 ellipsoid.z_length)
				ellipse_points = map(lambda point: rotateAboutX(point, ellipsoid.x_rotate), 
											ellipse_points)
				ellipse_points = map(lambda point: rotateAboutY(point, ellipsoid.y_rotate), 
											ellipse_points)
				ellipse_points = map(lambda point: rotateAboutZ(point, ellipsoid.z_rotate), 
											ellipse_points)
				xs = map(lambda point: point[0], ellipse_points)
				ys = map(lambda point: point[1], ellipse_points)
				zs = map(lambda point: point[2], ellipse_points)
				subplot.plot_surface(xs, ys, zs, color='#a6ccff',
			                     	linewidth=0.0, alpha=1.0)
				#for i, eigenvector in enumerate(ellipsoid.eigenvectors):
					#subplot.quiver(0, 0, 0, eigenvector[0], eigenvector[1], eigenvector[2], 
									   #length=(2*ellipsoid.eigenvalues[i]), pivot='tail')
				subplot.set_xlabel('X')
				subplot.set_ylabel('Y')
				subplot.set_zlabel('Z')


			subplots.append(subplot)

	fig.tight_layout()
	plt.subplots_adjust(wspace=0, hspace=0)
	fig.savefig(filename)
#END


#Returns x, y, z values for an ellipse surface plot
#Center is origin, not angled
#return an array of 
def getEllipsePoints(x_c, y_c, z_c):

	u = np.linspace(0, 2 * np.pi, 200)
	v = np.linspace(0, np.pi, 200)

	xs = x_c*np.outer(np.cos(u), np.sin(v))
	ys = y_c*np.outer(np.sin(u), np.sin(v))
	zs = z_c*np.outer(np.ones(np.size(u)), np.cos(v))

	ellipse_points = []
	for i, x in enumerate(xs):
		ellipse_points.append([x, ys[i], zs[i]])

	return ellipse_points
#END

def parseInterpolation(file_name):

	interp_xml = et.parse(file_name)

	interpolations = interp_xml.getroot()

	#array of Ellipse objects
	ellipses = []

	for interpolation in interpolations:
		for matrix in interpolation:
			np_mat = []

			for row in matrix:
				np_mat.append(map(float, row.text.split(",")))

			ellipses.append(Ellipsoid(np_mat))			

	return ellipses
#

ellipsoids = parseInterpolation("interpolation.xml")

plotEllipsoids(ellipsoids, 4, 9, "interpolate3D.png", 1.5, 1.5, 1.5)

