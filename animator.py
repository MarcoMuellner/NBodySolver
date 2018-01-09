"""
A simple example of an animated plot
"""
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

fig, ax = plt.subplots()
Verlet1 = np.loadtxt("build/VerletMethod_1.txt").T
x = Verlet1[0]
line, = ax.plot(x, Verlet1[1],"x")


def animate(i):
    line.set_data(x[i],Verlet1[1][i])  # update the data
    return line,


# Init only required for blitting to give a clean slate.
def init():
    line.set_ydata(np.ma.array(x, mask=True))
    return line,

ani = animation.FuncAnimation(fig, animate, np.arange(1, 200), init_func=init,
                              interval=25, blit=True)
plt.show()