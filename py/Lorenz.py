import numpy as np
import matplotlib.pyplot as plt

tdat = np.loadtxt("../builddir/tsteps.txt")
xdat = np.loadtxt("../builddir/xvalues.txt")
ydat = np.loadtxt("../builddir/yvalues.txt")
zdat = np.loadtxt("../builddir/zvalues.txt")

fig = plt.figure()
ax = plt.axes(projection='3d')

ax.plot(xdat, ydat, zdat)
plt.show()
