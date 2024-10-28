import matplotlib.pyplot as plt
import numpy as np
t0 =[]
t2 =[]
t1 =[]
p0 =[]
p1=[] #cwnd
p2=[]
h0=[]
h1=[]
h2=[] #ssthresh

sever = "10.10.1.2:37454"
router = "10.10.1.2:37456"
client = "10.10.1.2:37452"

with open("tcpprobe.dat", "r") as file:
    for line in file:

        if(line.split()[1]==sever):
            t0.append(float(line.split()[0]))
            p0.append(float(line.split()[6]))
            h0.append(float(line.split()[7]))
            #print(line.split()[0],line.split()[1],line.split()[6])

        if(line.split()[1]==router):
            t1.append(float(line.split()[0]))
            p1.append(float(line.split()[6]))
            h1.append(float(line.split()[7]))

         #   print(line.split()[0],line.split()[1],line.split()[6])
        if(line.split()[1]==client):
            t2.append(float(line.split()[0]))
            p2.append(float(line.split()[6]))
            h2.append(float(line.split()[7])) #ssthresh

        print(line.split())






# evenly sampled time at 200ms intervals

# red dashes, blue squares and green triangles
plt.figure()
plt.xlabel("time (s)")
plt.ylabel("CWND (in MSS)")

plt.subplot(311)
plt.plot(t0,p0,"r")
plt.plot(t0,h0,"b--")

plt.title(sever , "sever")


plt.subplot(312)
plt.plot(t1,p1,"r")
plt.plot(t1,h1,"b--")
plt.title(router, "router")



plt.subplot(313)
plt.plot(t2,p2,"r")
plt.plot(t2,h2,"b--")
plt.title(client , "client")

plt.legend(['cwnd','ssthresh'],bbox_to_anchor = (1,-.15),ncol=2) 



plt.show()
f.close