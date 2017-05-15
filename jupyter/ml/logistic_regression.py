#coding=utf-8
import numpy as np

class logistic():
	def __init__(self,data):
		self._alpha=data

	def _sigmoid(self,fx):
		return 1.0/(1+np.exp(-fx))

	def _graddescent(self,feat,label,alpha,max_iter):
		datamat=np.mat(feat)
		labelmat=np.mat(label).transpose()#进行转置变成一个m*1的矩阵
		m,n=np.shape(datamat)
		weight=np.ones((n,1))
		for i in range(max_iter):
			hx=self._sigmoid(datamat*weight)
			error=labelmat-hx #m*1
			weight=weight+alpha*datamat.transpose()*error #n*m 	m*1
		return weight
	def fit(self,train_x,train_y,alpha=0.01,max_iter=500):
		return self._graddescent(train_x,train_y,alpha,max_iter)

	def predict(self,test_x,test_y,weight):
		datamat=np.mat(test_x)
		labelmat=np.mat(test_y).transpose()
		hx=self._sigmoid(datamat*weight)
		m=len(hx)
		error=0.0
		for i in range(m):
			if int(hx[i])>0.5:
				if int(labelmat[i])!=1:
					error+=1.0
			else:
				if int(labelmat[i])!=0:
					error+=1.0
		error_rate=error/m
		print 'the error rate is','%.4f' %error_rate

def loadDataSet(datafile):
    featData = []; labelDate = []
    with open(datafile, 'r') as fr_file:
        for eachline in fr_file:
            oneline = eachline.split('\t')
            tempArr = []
            for i in range(len(oneline)-1):
                tempArr.append(float(oneline[i]))
            featData.append(tempArr)
            labelDate.append(int(float(oneline[-1].strip())))
    return featData, labelDate   #返回的数据是list

if __name__=="__main__":
	trainfile = r"/home/zzq/imprave/MachineLearning/Logistic Regression/data/train.txt"
	testfile = r"/home/zzq/imprave/MachineLearning/Logistic Regression/data/test.txt"
	train_X, train_y = loadDataSet(trainfile)
	test_X, test_y = loadDataSet(testfile)
	clf=logistic(0.001)
	weight=clf.fit(train_X,train_y,alpha=0.01,max_iter=2000)
	clf.predict(test_X,test_y,weight)