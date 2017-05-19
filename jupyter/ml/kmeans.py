import os
import numpy as np

class kmeans():
    def __init__(self,k=3,initcent='random',max_iter=500):
        self._k=k
        self._initcent=initcent
        self._max_iter=max_iter
        self._clussassign=None
        self._labels=None
        self._css=None
    def _caldist(self,arra,arrb):
        return np.sqrt(np.sum(np.power(arra-arrb,2)))

    def _calMdist(self,arra,arrb):
        return np.sum(abs(arra-arrb))

    def _randcent(self,data,k):
        n=data.shape[1]
        centroids=np.empty((k,n))
        for j in range(n):
            minj=min(data[:,j])
            rangej=float(max(data[:,j]-minj))
            centroids[:,j]=(minj+rangej*np.random.rand(k,1)).flatten()#拉伸成为一个list
        return centroids

    def fit(self,data):
        if not isinstance(data,np.ndarray) or isinstance(data,np.matrixlib.defmatrix.matrix):
            try:
                data=np.asarray(data)
            except:
                raise TypeError("data must be required for np.ndarray")
        m=data.shape[0]
        self._clussassign=np.zeros((m,2))
        if self._initcent=='random':
            self._centroids=self._randcent(data,self._k)

        cluschanged=True
        for _ in range(self._max_iter):
            cluschanged=False
            for i in range(m):
                mindist=np.inf
                mindex=-1
                for j in range(self._k):
                    arra=self._centroids[j,:]#第j个数的所有特征
                    arrb=data[i,:]
                    dist=self._caldist(arra,arrb)
                    if dist<mindist:
                        mindist=dist
                        mindex=j
                if self._clussassign[i,0]!=mindex:
                    cluschanged=True
                    self._clussassign[i,:]=mindex,dist**2
            if not cluschanged:
                break
            for i in range(self._k):
                index_all=self._clussassign[:,0]#将所有的下标值都提取出来
                value=np.nonzero(index_all==i)
                plsinclust=data[value[0]]
                self._centroids[i,:]=np.mean(plsinclust,axis=0)
        self._labels=self._clussassign[:,0]
        self._css=self._clussassign[:,1]


    def predict(self,x):
        if not isinstance(x,np.ndarray):
            try:
                x=np.asarray(x)
            except:
                raise TypeError("numpy.ndarray must be required")
        m=x.shape[0]
        preds=np.shape((m,))
        for i in range(m):
            mindist=np.inf
            for j in range(self._k):
                distji=self._caldist(self._centroids[j,:],x[i,:])
                if distji<mindist:
                    mindist=distji
                    preds[i]=j
        return preds


