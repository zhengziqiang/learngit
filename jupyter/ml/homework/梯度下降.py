import numpy as np
import os
from numpy import genfromtxt
my_data = genfromtxt('/home/zzq/Downloads/ex1data1.csv', delimiter=',')
x=my_data[:,0]
y=my_data[:,1]
alpha=0.02

def h_theta(x,theta1,theta2):
    return x*theta1+theta2
def cost(x,y):
    return (np.sum((x-y)**2))/(2*x.shape[0])
def update_param(x_,theta1,theta2):
    y_=h_theta(x_,theta1,theta2)
    delta=np.sum((y_-x_)*x_)/(x_.shape[0])
    theta1-=(alpha*delta)
    theta2-=(alpha*delta*0.6)
    return theta1,theta2
if __name__=='__main__':
    theta2 = y.mean()
    theta1 = (y[2] - y[1]) / (x[2] - x[1])
    print theta1,theta2
    for i in range(10000):
        x_ = h_theta(x, theta1, theta2)
        if cost(x_,y) <0.01:
            print i+1
            break
        else:
            m1,m2=update_param(x,theta1,theta2)
            theta1=m1
            theta2=m2
    print theta1,theta2

#在学习率为0.01~0.05这个区间里面收敛速度是比较理想的，如果学习率大于0.1，会是梯度爆掉，如果小于了0.0001就会收敛得比较慢