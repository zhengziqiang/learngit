#coding=utf-8
import numpy as np
class adaboost(object):
	def __init__(self,max_iter=100,numsteps=10,num_iter=50):
		self._max_iter=max_iter
		self._numsteps=numsteps
		self._numiter=num_iter

	def _stump(self,x,axis,thresh,thrneq):
		retarray=np.ones((np.shape(x)[0],1))
		if thrneq=='lt':
			retarray[x[:,axis]<=thresh]= -1.0
		else:
			retarray[x[:,axis]>thresh]=-1.0
		return retarray
	def _buildstump(self,x,y,d):
		data=np.mat(x)
		label=np.mat(y)
		m,n=np.shape(data)
		best_stump={}
		best_cls=np.mat(np.zeros((m,1)))
		min_error=np.inf
		for i in range(n):
			min_val=data[:,i].min()
			max_val=data[:,i].max()
			step_size=(max_val-min_val)/self._numsteps
			for j in range(-1,int(self._numsteps)+1):
				for ineque in ['lt','gt']:
					thresh=(min_val+float(j)*step_size)
					pre_val=self._stump(data,i,thresh,ineque)
					err_arr=np.mat(np.ones((m,1)))
					err_arr[pre_val==label]=0 #返回的是下标，两个np相等的值，然后返回的是下标
					weightederr=d.T*err_arr
					if weightederr<min_error:
						min_error=weightederr
						best_stump['dim']=i
						best_stump['thresh']=thresh
						best_stump['ineq']=ineque
		return best_stump,min_error,best_cls

	def fit(self,x,y):
		weak={}
		m=np.shape(x)[0]
		d=np.mat(np.ones((m,1))/m)
		aggcls=np.mat(np.zeros((m,1)))
		for i in range(self._numiter):
			best_stump,error,best_cls=self._buildstump(x,y,d)
			alpha=float(0.5*np.log((1.0-error)/max(error,1e-16)))#0.5ln[(1-epsilon)*epsilon]
			best_stump['alpha']=alpha
			weak.append(best_stump)
			expon=np.multiply(-1*alpha*np.mat(y).T,best_cls)
			d=np.multiply(d,np.exp(expon))
			d=d/d.sum()
			aggcls+=alpha*best_cls
			agg_error=np.multiply(np.sign(aggcls)!=np.mat(y).T,np.ones((m,1)))
			error_rate=agg_error.sum()/m
			if error_rate==0.0:
				break
		return weak
	def predict(self,test,class_arr):
		data=np.mat(test)
		m=np.shape(data)[0]
		aggcls=np.mat(np.zeros((m,1)))
		for i in range(len(class_arr)):
			cls_est=self._stump(data,class_arr[i]['dim'],class_arr[i]['thresh'],class_arr[i]['ineq'])
			aggcls+=class_arr[i]['alpha']*cls_est
		return np.sign(aggcls)

