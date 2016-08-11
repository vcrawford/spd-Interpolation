#This is to produce a graph that has the fractional anisotropy
#plotted for a series of interpolations. The plot is the position along the 
#interpolation (how much the final matrix is weighted) vs. the fractional 
#anisotropy. Each interpolation has it's own curve.
#call like "python PlotFractionalAnisotropy.py input.xml output.png"
import xml.etree.ElementTree as et
import Interpolations as interp
import sys
import matplotlib.pyplot as plt

print "Graphing fractional anisotropy..."

#xml file that holds the interpolation data
filename = sys.argv[1]
#where we should save the output image
imagename = sys.argv[2]
interpolation_xml = et.parse(filename)
interpolations = interpolation_xml.getroot()

#each interpolation gets its own line on the graph
for interpolation in interpolations:
	#get an array of matrices from reading in elements in interpolation
	matrices = interp.parseMatrices(interpolation)

	#bottom axis
	weights = interp.interpolationWeights(interpolation)
	aniso = interp.computeFractionalAnisotropyList(matrices)

	#add this interpolation to plot
	plt.plot(weights, aniso, label=interpolation.get("type"))

print "Saving output image to " + imagename
plt.legend()
plt.savefig(imagename)

print "Fractional anisotropy graph complete."

