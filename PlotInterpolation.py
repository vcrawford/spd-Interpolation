import CovarianceEllipse2D as ell
import ParseXMLInterpolation as par

ellipses = par.parseInterpolation("MatrixOutput.xml")
ell.plotEllipses(ellipses, "output.png", 4, 6, 1.75, 1.75)


