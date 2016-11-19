/*==============================================================================
    > File Name: 重现二叉树.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月19日 星期六 16时39分58秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct tree_node{
	int val;
	tree_node *left;
	tree_node *right;
	tree_node(int x):val(x),left(NULL),right(NULL){

	};
};
tree_node *build(vector <int> &inorder,int in_offset,vector <int> &post_order,int post_offset,int n){
	if(n<=0 || inorder.size()<=0 || post_order.size()<=0){
		return NULL;
	}
	tree_node *root = new tree_node(post_order[post_offset+n-1]);
	if(n==1){
		return root;
	}
	int i;

}
tree_node *build(vector <int> &inorder,vector <int> &post_order){
	return build(inorder,0,post_order,0,post_order.size());
}
