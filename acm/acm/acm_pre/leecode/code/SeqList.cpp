/*==============================================================================
    > File Name: SeqList.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年10月06日 星期四 11时31分39秒
 ==========================================================================*/

#include<iostream>
#include<stdlib.h>
using namespace std;
template <class Type> class SeqList{
	private:
		Type *elem;
		int length;
		int listsize;
	public:
		SeqList(int size);
		~SeqList(void){
			delete []elem;
		}
		int SeqList_empty(void)const{
			return length==0;
		}
		int SeqList_length(void)const{
			return length;
		}
		Type & Seq_getelem(int i)const{
			return elem[i-1];
		}
		int replace_elem(int i,Type &e);//用元素e替代顺序表中的第i个元素
		int locate_elem(Type e);//在表中找到一个元素e
		int seq_insert(int i,Type &e);//将数据元素插入到第i个元素之前
		int seq_insertafter(int i,Type &e);//将数据元素插入到第i个元素之后
		int seq_delete(int i,Type &e);//将数据元素的第I个元素删掉
		Type & seq_prior(int i);//求第i个元素的直接前驱
		Type & seq_next(int i);//求后驱
		void clear(void){
			length=0;
		}

};
template<class Type> SeqList<Type>::SeqList(int size){
	elem=new Type[size];
	if(!elem){
		cout<<"内存溢出"<<endl;
		exit(0);
	}
	listsize=size;
	length=0;
}
template <class Type>int SeqList<Type>::locate_elem(Type e){
	if(length==0)
		return 0;
	int i=1;
	while(i<=length&&e!=elem[i-1])
		i++;
	if(i<=length)
		return i;
	else
		return 0;
}
template <class Type>int SeqList<Type>::replace_elem(int i,Type &e){
	if(length>=i){
		elem[i-1]=e;
		return 1;
	}
	return 0;
}
template <class Type>int SeqList<Type>::seq_insert(int i,Type &e){
	if(i<1||i>length+1)
		return 0;
	if(length==listsize){
		Type *p=new Type[listsize+10];
		if(!p){
			cout<<"内存申请失败"<<endl;
			exit(0);
		}
		for(int j=0;j<length;j++)p[j]=elem[j];//赋值
		delete []elem;//消除原先的数据
		elem=p;//将新赋的值传给elem
		p=NULL;
		listsize+=10;
	}
	for(int j=length-1;j>=i-1;j--)
		elem[j+1]=elem[j];//hou=后移元素
	elem[i-1]=e;//c插入元素
	length++;//长度加1
	return 1;
}

template <class Type>int SeqList<Type>::seq_delete(int i,Type &e){
	if(i<1||i>length){
		return 0;
	}
	e=elem[i-1];
	for(int j=i-1;j<length-1;j++){
		elem[j]=elem[j+1];
	}
	--length;
	return 1;
}
template<class Type>
void merge(SeqList <Type> &la,SeqList<Type> &lb,SeqList<Type> &lc){
	Type data;
	int i;
	int la_length=la.SeqList_length();
	int lb_length=lb.SeqList_length();
	for(i=1;i<la_length;i++){
		data=la.Seq_getelem(i);
		lc.Seq_insert(i,data);
	}
	int lc_length=lc.SeqList_length();
	for(i=1;i<lb_length;i++){
		data=lb.Srq_getelem(i);
		if(!lc.lacate_elem(data))//去除重复的元素
		lc.Seq_insert(++lc_length,data);
	}
}
template <class Type>void bubble_sort(SeqList<Type> &lc){
	Type tmp;
	int flag=1;
	int n=lc.SeqList_length();
	for(int i=1;i<n&&flag==1;i++){
		flag=0;
		for(int j=1;j<=n-1;j++){
			if(lc.Seq_getelem(j)>lc.Seq_getelem(j+1)){
				tmp=lc.Seq_getelem(j);
				lc.replace_elem(j,lc.Seq_getelem(j+1));
				lc.replace_elem(j+1,tmp);
				flag=1;
			}
		}
	}
}
int main(){
	SeqList<int> la(5);
	SeqList<int> lb(6);
	return 0;
}
