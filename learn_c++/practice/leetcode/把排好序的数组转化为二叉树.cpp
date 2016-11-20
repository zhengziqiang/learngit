/*==============================================================================
    > File Name: 把排好序的数组转化为二叉树.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月19日 星期六 17时29分11秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
struct tree_node{
	int val;
	tree_node *left;
	tree_node *right;
	tree_node(int x):val(x),left(NULL),right(NULL){

	};
};
tree_node* sorted_tobst(vector <int> &num){
	if(num.size()==0){
		return NULL;
	}
	if(num.size()==1){
		return new tree_node(num[0]);
	}
	int mid = num.size()/2;
	tree_node *node= new tree_node(num[mid]);
	vector <int>::const_iterator first;
	vector <int>::const_iterator last;
	first=num.begin();
	last=num.begin()+mid;
	vector <int> v(first,last);
	node->left=sorted_tobst(v);//递归
	if(mid==num.size()-1){
		node->right=NULL;//出口，最后的没有数的时候就用NULL来表示
	}
	else{
		first=num.begin()+mid+1;
		last=num.end();
		vector <int> v(first,last);
		node->right=sorted_tobst(v);
	}
	return node;
}
int main(){
	return 0;
}
