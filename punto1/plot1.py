"""
Created on Fri Dec  7 10:11:52 2018

@author: david
"""
import numpy as np
import matplotlib.pyplot as plt

DATA=[]
for i in range(4):
    DATA+=list(np.genfromtxt("samp_"+str(i)+".txt"))

plt.figure(figsize=[12,12])
plt.hist(DATA,bins=50)
plt.savefig("dist.png")