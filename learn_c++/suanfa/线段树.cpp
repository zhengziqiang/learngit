/*==============================================================================
    > File Name: 线段树.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月15日 星期二 19时45分57秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
const int maxnum=100;
const int INFINITE=INT_MAX;
struct seg_tree{
	int val;
	int add_mark;
}seg[maxnum];
//构建线段树
void build(int root,int arr[],int start,int end){
	seg[root].add_mark=0;//设置标延迟记忆域
	if(start==end){
		seg[root].val=arr[start];
	}
	else{
		int mid=(start+end)/2;
		build(root*2+1,arr,start,mid);
		build(root*2+2,arr,mid+1,end);
		seg[root].val=min(seg[root*2+1].val,seg[root*2+2].val);
	}
}
//标志域向孩子节点传输
void push_down(int root){
	if(seg[root].add_mark!=0){
		seg[root*2+1].add_mark+=seg[root].add_mark;
		seg[root*2+2].add_mark+=seg[root].add_mark;
		seg[root*2+1].val+=seg[root].add_mark;
		seg[root*2+2].val+=seg[root].add_mark;
		seg[root].add_mark=0;//清理操作
	}
}
//线段树的区间查询
int query(int root,int nstart,int nend,int qstart,int qend){
	if(qstart>nend||qend<nstart)
		return INFINITE;
	if(qstart<=nstart&&qend>=nend)
		return seg[root].val;
	push_down(root);
	int mid=(nstart+nend)/2;
	return min(query(root*2+1,nstart,mid,qstart,qend),
			query(root*2+2,mid+1,nend,qstart,qend));
}

void update(int root ,int nstart ,int nend,int ustart,int uend,int add_val){
	if(ustart>nend||uend<nstart){
		return ;
	}
	if(ustart<=nstart&&uend>=nend){
		seg[root].add_mark+=add_val;
		seg[root].val+=add_va;
		return ;
	}
	int mid=(nstart+nend)/2;
	update(root*2+1,nstart,mid,ustart,uend,add_val);
	update(root*2+2,mid+1,nend,ustart,uend,add_val);
	seg[root].val=min(seg[root*2+1].val,seg[root*2+2].val);


}
