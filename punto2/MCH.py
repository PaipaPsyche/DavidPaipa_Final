"""
Created on Fri Dec  7 11:26:38 2018

@author: david
"""
import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import odeint

INC=1

DATA=np.genfromtxt("datos_observacionales.dat").T
T=DATA[0]
X=DATA[1]
Y=DATA[2]
Z=DATA[3]


def modelo_x(x,t,sig,rho,beta,y,z):
    dxdt=sig*(y-x)
    return dxdt
def modelo_y(y,t,sig,rho,beta,x,z):
    dydt=x*(rho-z)-y
    return dydt
def modelo_z(z,t,sig,rho,beta,x,y):
    dzdt=x*y-beta*z
    return dzdt




def logprior(sig,rho,beta):
    p=-np.inf
    if((sig<=30)and(rho<=30)and(beta<=30)):
        p=0
    return p


def loglikelihood(t_obs, x_obs,y_obs,z_obs, sigma_obs, sig,rho,beta):
    
    x=odeint(modelo_x,np.random.random(),T,args=(sig,rho,beta,y,z,))
    y=odeint(modelo_y,np.random.random(),T,args=(sig,rho,beta,x,z,))
    z=odeint(modelo_z,np.random.random(),T,args=(sig,rho,beta,x,y,))
    dx = x_obs -  x
    dy = y_obs -  y
    dz = z_obs -  z
    d = (dx+dy+dz)/sigma_y_obs
    d = -0.5 * np.sum(d**2)
    return d
