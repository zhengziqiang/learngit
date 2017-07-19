#coding=utf-8
import os
import numpy as np
class DT():
	def __init__(self,criteria="ID3"):
		self._tree=None
		if criteria=='ID3' or criteria=='C4.5':
			self._criteria='ID3'
		else:
			raise Exception("criteria should be C4.5 or ID3")

	def _calEntropy(self,y):
		n=y.shape[0]
		labelcounts={}
		for label in y:
			if label not in labelcounts.keys():
				labelcounts[label]=1
			else:
				labelcounts[label]+=1
		entropy=0.0
		for k in labelcounts:
			prob =float(labelcounts[k])/n
			entropy-=prob*np.log2(prob)
			#prob 是每个值的可能性
		return entropy

	def _splitdata(self,x,y,axis,cutoff):
		"""
        参数：X为特征,y为label,axis为某个特征的下标,cutoff是下标为axis特征取值值
        输出：返回数据集中特征下标为axis，特征值等于cutoff的子数据集
        """
		ret=[]
		featvec=x[:,axis]#所有的样本的特征值制作成一个特征向量
		n=x.shape[1]#第二维的长度
		x=x[:,[i for i in range(n) if i!=axis]]#不和它一个维度的,i是特征的下标，剔除重复的下标值
		for i in range(len(featvec)):
			if featvec[i]==cutoff:
				ret.append(i)
		return x[ret,:],#第一维的指定维度，第二维的所有维度特征，拥有这个特征的所有样本的特征
		y[ret]#label
		#cutoff 剪枝的值

	def _choosebestsplit(self,x,y):
		"""
		x为特征
		y为label
		"""
		num_feat=x.shape[1]
		base_entropy=self._calEntropy(y)#基本的熵
		best_split=0.0
		best_idx=-1
		for i in range(num_feat):
			feat_list=x[:,i]#第某个特征的全部样本的值
			unique=set(feat_list)#剔除重复的下标值
			cur_entropy=0.0
			split_info=0.0
			for value in unique:
				sub_x,sub_y=self._splitdata(x,y,i,value)
				prob=len(sub_y)/float(len(y))#所占的比例
				cur_entropy+=prob*self._calEntropy(sub_y)#计算熵增益
				split_info-=prob*np.log2(prob)#分裂信息
			IG=base_entropy - cur_entropy
			#information gain gain=base_entropy - 两个不同分类的entropy
			if self._criteria=='ID3':
				if IG>best_split:
					best_split=IG
					best_idx=i
			if self._criteria=='C4.5':
				if split_info==0.0:
					pass
				IGR=IG/split_info
				if IGR>split_info:
					best_split=IGR
					best_idx=i
		return best_idx

	def _majoritycnt(self,labellist):
		#返回最普遍分类的结果
		labelcounts={}
		for vote in labellist:
			if vote not in labelcounts.keys():
				labelcounts[vote]=0
			labelcounts[vote]+=1
		sorted_cnt=sorted(labelcounts.iteritems(),key=lambda x:x[1],reverse=true)#字典的迭代方法
		return sorted_cnt[0][0]#第二个代表是字典中的key

	def _createtree(self,x,y,feature_index):
		labellist=list(y)
		if labellist.count(labellist[0])==len(labellist):
			return labellist[0]#全部都是一个数
		if len(feature_index)==0:
			return self._majoritycnt(labellist)
		best_featindex=self._choosebestsplit(x,y)#拿信息熵最大的作为决策的重要根据
		best_feataxis=feature_index[best_featindex]
		feature_index=list(feature_index)
		feature_index.remove(best_feataxis)#把已经成树的特征去掉
		feature_index=tuple(feature_index)
		my_tree={best_feataxis:{}}
		feat_values=x[:,best_featindex]#每一个样本的该特征的样本值
		unique=set(feat_values)
		for value in unique:
			#递归创建决策树
			sub_x,sub_y=self._splitdata(x,y,best_featindex,value)
			my_tree[best_feataxis][value]=self._createtree(sub_x,sub_y,feature_index)
			#现在建立的结构类似于一个二叉树的结构，根下面有很多节点，节点又可以作为根

		return my_tree

	def fit(self,x,y):
		if isinstance(x,np.ndarray) and isinstance(y,np.adarray):
			pass
		else:
			try:
				x=np.array(x)
				y=np.array(y)
			except:
				raise TypeError("numpy.ndarray must be required for x, y")
		feature_index=tuple(['x'+str(i) for i in range(x.shape[1])])
		self._tree=self._createtree(x,y,feature_index)
		return self #等于是返回所有的值

	def _classify(self,tree,sample):
		feat_index=tree.keys()[0]
		second_dict=tree[feat_index]
		axis=feat_index[1:]
		#之所以为[1:]是因为要排除当前已经使用过了的特征
		#获取特征名称，在上面我们构造的是x1,x2,x3
		key=sample[int(axis)]#获取keys,就是该样本该特征对应的相应的值
		valueofkey=second_dict[key]
		if type(valueofkey).__name__=='dict':
			return self._classify(valueofkey,sample)
		else:
			return valueofkey

	def predict(self,x):
		if self._tree==None:
			raise NotImplementedError("Estimator not fitted, call `fit` first")

		if len(x.shape)==1:
		    return self._classify(self._tree,x)
		else:
			result=[]
			for i in range(x.shape[0]):
				value=self._classify(self._tree,x)
				print str(i+1)+"-th sample is classfied as:",value
				result.append(value)
			return np.array(result)

if __name__=="__main__":
    trainfile=r"/home/zzq/imprave/MachineLearning/DecisionTree/data/train.txt"
    testfile=r"/home/zzq/imprave/MachineLearning/DecisionTree/data/test.txt"
    import sys
    sys.path.append(r"/home/zzq/imprave/MachineLearning/lib/")  
    import dataload as dload
    train_x, train_y = dload.loadData(trainfile)
    test_x, test_y = dload.loadData(testfile)
    
    clf = DT(criteria="C4.5")
    clf.fit(train_x, train_y)
    result = clf.predict(test_x)    
    # outpdf = r"tree.pdf"
    # clf.show(outpdf)