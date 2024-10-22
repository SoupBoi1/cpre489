import matplotlib.pyplot as plt
import numpy as np
t0 =[]
t2 =[]
t1 =[]
p0 =[]
p1=[]
p2=[]
h0=[]
h1=[]
h2=[]

with open("tcpprobe.dat", "r") as file:
    for line in file:

        if(line.split()[1]=="10.10.1.2:51110"):
            t0.append(float(line.split()[0]));
            p0.append(float(line.split()[6]));
            h0.append(float(line.split()[7]));
            print(line.split()[0],line.split()[1],line.split()[6])

        if(line.split()[1]=="10.10.1.2:51112"):
            t1.append(float(line.split()[0]));
            p1.append(float(line.split()[6]));
            h1.append(float(line.split()[7]));

            print(line.split()[0],line.split()[1],line.split()[6])
        if(line.split()[1]=="10.10.1.2:51114"):
            t2.append(float(line.split()[0]));
            p2.append(float(line.split()[6]));
            h2.append(float(line.split()[7]));

            print(line.split()[0],line.split()[1],line.split()[6])






# evenly sampled time at 200ms intervals

# red dashes, blue squares and green triangles
plt.figure()
plt.subplot(311)
plt.plot(t0,p0)
plt.plot(t0,h0)

plt.subplot(312)
plt.plot(t1,p1)
plt.plot(t1,h1)


plt.subplot(313)
plt.plot(t2,p2)
plt.plot(t2,h2)



plt.show()
f.close