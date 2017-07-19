#coding=utf-8
import os
import math
import copy
import matplotlib.pyplot as plt
import numpy as np

def init_data(sigma,mu1,mu2,k,n):
    global x
    global mu
    global expec
    x=np.zeros(((1,n)))
    mu=np.random.random(k)#产生k个0到1的浮点数
    for i in xrange(0,n):
        if np.random.random(1)>0.5:
            x[0,i]=np.random.normal(mu1,sigma)
        else:
            x[0,i]=np.random.normal(mu2,sigma)

def e_step(sigma,k,n):
    global expec
    global mu
    global x
    for i in range(n):
        denom=0.0
        numer=[0.0]*k
        for j in range(k):
            numer[j]+=math.exp(-1.0/2(float(sigma**2))*(float(x[0,i]-mu[j])**2))
            denom+=numer[j]
        for j in xrange(0,k):
            expec[i][j]=numer[j]/denom

def m_step(k,n):
    global expec
    global x
    for j in range(k):
        numer=0.0
        denom=0.0
        for i in range(n):
            numer+=expec[i,j]*x[0,i]#期望值之和除以期望值和x之值乘积之和等于这一次的均值
            denom+=expec[i,j]
        mu[j]=denom/numer