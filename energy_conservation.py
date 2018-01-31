import matplotlib
matplotlib.use('TkAgg')
import numpy as np
import pylab as pl

strList = ["Euler","RK4","Leapfrog"]

for i in strList:
    ended = False;
    counter = 1;
    totalPot = 0
    totalKin = 0
    totalPos = 0
    while not ended:
        try:
            obj = np.loadtxt("cmake-build-debug/"+i+"Method_"+str(counter)+".txt").T
            kin = np.loadtxt("cmake-build-debug/"+i+"Method_E_KIN_"+str(counter)+".txt").T
            pot = np.loadtxt("cmake-build-debug/"+i+"Method_E_POT_"+str(counter)+".txt").T

            kin = kin[1:]
            pot = pot[1:]

            if totalPot == 0:
                totalPot = pot
            else:
                totalPot += pot

            if totalKin == 0:
                totalKin = kin
            else:
                totalKin += kin

            if totalPos ==0:
                totalPos = obj
            else:
                totalPos -=obj

            counter +=1
        except:
            ended = True

    positionPlot = np.zeros(1)

    for vals in totalPos.T:
        positionPlot = np.append(positionPlot,np.abs(vals.T))

    sum = totalPot+ totalKin
    pl.plot(totalPot,label="Potential Energy")
    pl.plot(totalKin,label="Kinetic Energy")
    pl.plot(sum, label="Sum")
    pl.legend()
    pl.title(i)
    pl.xlabel("timestep")
    pl.ylabel("E")
    pl.show()
