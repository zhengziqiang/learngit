#coding=utf-8
import numpy as np 
# x=np.array([[1,2,3],
# 	[2,3,4]])
# print x.shape #shape函数没有括号
# m,n=x.shape
# def meanX(X):
# 	return np.mean(X,axis=0)#二维的是0，list是1
# 	#axis=1是直接求行的平均值
# 	#协方差(i,j)=（第i列的所有元素-第i列的均值）*（第j列的所有元素-第j列的均值）
# xu=meanX(x)
# print xu
# all_xu=np.tile(xu,(m,1))#1的作用是保持第二维不变
# print all_xu
# print x.T
# print np.diag(x.T * x)

# x=np.linspace(0,4,5) #等量划分
# print x.shape
# y=np.transpose(x)
# print y.shape
# print y
# a=np.array([[1,2],[3,4]])
# b=np.array([[5,6],[7,8]])
# print np.dot(a,b)
# #dot 函数对应的是矩阵的矢量乘积
# print a*b
# # *整个函数就是对应位置相乘的结果。
# print np.multiply(a,b)
# #也是求数量积

# x=[[1,2,3,4],[5,6,7,8]]
# y=[1,2,3,4]
# data=np.mat(x)
# label=np.mat(y).transpose()
# print label
#转换为矩阵之后所有的*都变成了单纯的矩阵乘积

# print data*label

print np.random.rand(5,1)#rand函数是返回0,1之间的随机值。且返回的是5行1列的数据

index_all=[1,1,2,3,1]
data=np.nonzero(index_all==1)
print data[0]