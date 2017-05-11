/*==============================================================================
    > File Name: balance_binary_tree.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年10月01日 星期六 11时06分59秒
 ==========================================================================*/

#include<iostream>
using namespace std;
struct tree_node{
	int val;
	tree_node *left;
	tree_node *right;
	tree_node(int x):val(x),left(NULL),right(NULL){

	}
};
class solution{
	public:
		bool is_balance(tree_node *root){
			int height=0;
			return is_balance_util(root,height);
		}
		bool is_balance_util(tree_node *root,int &height){
			if(root==NULL){
				height=0;
				return true;
			}
			int lh=0,rh=0;
			bool is_left=is_balance_util(root->left,lh);
			bool is_right=is_balance_util(root->right,rh);
			height=(lh>rh?lh:rh)+1;
			return (abs(lh-rh)<=1&&is_left&&is_right);
		}
};
class sulotion{
	public:
		bool is_balance(tree_node *root){
			if(root=NULL)return true;
			int left=tree_depth(root->left);
			int right=tree_depth(root->right);
			if(left-right>1||left-right<-1){
				return false;
			}
			return is_balance(root->left&&is_balance(root->right);
		}
		int tree_depth(tree_node *root){
			if(root==NULL){
			return 0;
			}
			int left=1,right=1;
			left+=tree_depth(root->left);
			right+=tree_depth(root-right);
			return left>right?left:right;
		}
};
