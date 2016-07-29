import CovarianceEllipse2D as ell
import ParseXMLInterpolation as par
import sys

#call like python PlotInterpolation.py interpolation.xml plots.png 9
filename = sys.argv[1]
image_filename = sys.argv[2]
count = int(sys.argv[3])
ellipses = par.parseInterpolation(filename)
ell.plotEllipses(ellipses, image_filename, 4, count, 1.5, 1.5)


