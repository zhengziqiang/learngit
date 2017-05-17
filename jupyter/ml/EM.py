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

