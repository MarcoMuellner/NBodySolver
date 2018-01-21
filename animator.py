import matplotlib
matplotlib.use('TkAgg')
from matplotlib import pyplot as plt
from matplotlib import animation
import numpy as np
import pylab as pl

strList = ["Verlet"]#,"RK4","Leapfrog"]

for i in strList:
    ended = False;
    counter = 1;
    while not ended:
        try:
            obj = np.loadtxt("cmake-build-debug/"+i+"Method_"+str(counter)+".txt").T
            pl.plot(obj[0],obj[1],label="Object"+str(counter))
            pl.arrow(obj[0][-1],obj[1][-1],obj[0][-1]+0.01,obj[1][-1]-0.1,shape="full",lw=0,length_includes_head=True,head_width=.05)
            counter +=1
        except:
            ended = True
    pl.legend()
    pl.title(i)
    pl.xlabel("x")
    pl.ylabel("y")
    pl.show()

for i in strList:
    obj = []
    ended = False
    counter = 1
    while not ended:
        try:
            obj.append(np.loadtxt("cmake-build-debug/"+i+"Method_"+str(counter)+".txt").T)
            counter +=1
        except:
            ended = True

    fig = plt.figure()
    ax = plt.axes(xlim=(0,int(len(obj)*1.3)),ylim=(-0,int(len(obj)*1.3)))
    lines = []
    for x in obj:
        lobj = ax.plot([], [], 'bo', ms=10)
        lines.extend(lobj)

    ax.set_title(i)

    def init():
        for line in lines:
            line.set_data([],[])
        return lines


    def animate(i):
        for line,objects in zip(lines,obj):
            line.set_data(objects[0][i],objects[1][i])

        return lines

    # call the animator.  blit=True means only re-draw the parts that have changed.
    anim = animation.FuncAnimation(fig, animate, init_func=init,
                                   frames=int(len(obj[0][0])), interval=1, blit=False)

    plt.show()



