import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

Verlet1 = np.loadtxt("build/VerletMethod_1.txt").T
Verlet2 = np.loadtxt("build/VerletMethod_2.txt").T
Verlet3 = np.loadtxt("build/VerletMethod_3.txt").T

pl.plot(Verlet1[0],Verlet2[1],label="Objekt1")
pl.plot(Verlet2[0],Verlet2[1],label="Objekt2")
pl.plot(Verlet3[0],Verlet3[1],label="Objekt3")
pl.legend()
pl.title("Euler")
pl.show()

Verlet1 = np.loadtxt("build/VerletMethod_1.txt").T
Verlet2 = np.loadtxt("build/VerletMethod_2.txt").T
Verlet3 = np.loadtxt("build/VerletMethod_3.txt").T

pl.plot(Verlet1[0],Verlet2[1],label="Objekt1")
pl.plot(Verlet2[0],Verlet2[1],label="Objekt2")
pl.plot(Verlet3[0],Verlet3[1],label="Objekt3")
pl.legend()
pl.title("Verlet")
pl.show()

fig,ax = plt.subplots()

