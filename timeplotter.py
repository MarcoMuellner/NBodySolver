import matplotlib
matplotlib.use('TkAgg')
import numpy as np
import pylab as pl

data = np.loadtxt("Timeelapsed.txt",skiprows=1).T

x = data[0]
euler = data[1]
RK4 = data[2]
Leapfrog = data[3]

pl.plot(x,euler,'x',label='Euler method')
pl.plot(x,RK4,'x',label='RK4 method')
pl.plot(x,Leapfrog,'x',label='Leapfrog method')
pl.legend()
pl.xlabel("bodies")
pl.ylabel("Time (s)")
pl.show()
