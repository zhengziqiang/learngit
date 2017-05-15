/*==============================================================================
    > File Name: treenode.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年03月27日 星期一 19时07分03秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
struct treenode{
	int val;
	treenode *left;
	treenode *right;
	treenode(int x):val(x),left(NULL),right(NULL){

	}
};
treenode *recursive(treenode *root){
	if(root==NULL)
		return root;
	treenode *node=recursive(root->left);
	root->left=recursive(root->right);
	root->right=node;
	return root;
}
