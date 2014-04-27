import pylab
import numpy
import sys, string, os
from StringIO import StringIO

data = numpy.loadtxt("datos_eqonda.txt")
x = data[:,0]
uinicial = data[:,1]

pylab.plot(x,uinicial)
pylab.title("Grafica inicial")
pylab.xlabel("$x$")
pylab.ylabel("$Uinicial$")
pylab.savefig("grafica")




