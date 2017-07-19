#coding=utf-8
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

def meanX(data):
    return np.mean(data,axis=0)#axis=0表示按照列来求均值，如果输入list,则axis=1
#计算方差
def variance(x):
    m,n=np.shape(x)
    mu=meanX(x)
    muall=np.tile(mu,(m,1))#以列为重复m次
    x1=x-muall
    my_variance=1.0/m*np.diag(x1.T*x1)#特征多个数
    return my_variance

#标准化
def normal(x):
    m,n=np.shape(x)
    mu=meanX(x)
    muall=np.tile(mu,(m,1))#以列为重复m次
    x1=x-muall
    x2=np.tile(np.diag(x.T*x),(m,1))
    xnorm=x1/x2
    return xnorm
"""
参数：
	- XMat：传入的是一个numpy的矩阵格式，行表示样本数，列表示特征
	- k：表示取前k个特征值对应的特征向量
返回值：
	- finalData：参数一指的是返回的低维矩阵，对应于输入参数二
	- reconData：参数二对应的是移动坐标轴后的矩阵
"""

def pca(x,k):
    average=meanX(x)
    m,n=np.shape(x)
    data_ajust=[]
    avgs=np.tile(average,(m,1))
    data_ajust=x-avgs
    conv=np.cov(data_ajust.T)#计算协方差矩阵
    featValue, featVec = np.linalg.eig(conv)  # 求解协方差矩阵的特征值和特征向量
    index=np.argsort(-featValue)#按照featValue进行从大到小排序
    final=[]
    if k>n:
        print "k must lower than feature number"
        return
    else:
        selectVec = np.matrix(featVec.T[index[:k]])#截取前k个主元素
        # 所以这里需要进行转置
        final = data_ajust * selectVec.T
        reconData = (final * selectVec) + average
    return final,reconData

def loaddata(datafile):
    return np.array(pd.read_csv(datafile,sep="\t",header=-1)).astype(np.float)


def plotBestFit(data1, data2):
    dataArr1 = np.array(data1)
    dataArr2 = np.array(data2)

    m = np.shape(dataArr1)[0]
    axis_x1 = []
    axis_y1 = []
    axis_x2 = []
    axis_y2 = []
    for i in range(m):
        axis_x1.append(dataArr1[i, 0])
        axis_y1.append(dataArr1[i, 1])
        axis_x2.append(dataArr2[i, 0])
        axis_y2.append(dataArr2[i, 1])
    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.scatter(axis_x1, axis_y1, s=50, c='red', marker='s')
    ax.scatter(axis_x2, axis_y2, s=50, c='blue')
    plt.xlabel('x1');
    plt.ylabel('x2');
    plt.savefig("outfile.png")
    plt.show()

def test():
    X = [[2.5, 0.5, 2.2, 1.9, 3.1, 2.3, 2, 1, 1.5, 1.1],
         [2.4, 0.7, 2.9, 2.2, 3.0, 2.7, 1.6, 1.1, 1.6, 0.9]]
    XMat = np.matrix(X).T
    # print XMat
    k = 2
    return pca(XMat, k)
def main():
    datafile = "/home/zzq/learngit/jupyter/ml/data/pca_data.txt"
    XMat = loaddata(datafile)
    k = 2
    return pca(XMat, k)
if __name__ == "__main__":
    finalData, reconMat = main()
    # plotBestFit(finalData, reconMat)
    print test()
