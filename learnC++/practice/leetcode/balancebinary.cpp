/*==============================================================================
    > File Name: balancebinary.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月18日 星期五 22时16分11秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<stdlib.h>
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
		bool isbalanced(tree_node *root){
			int height=0;
			return isbalanceutil(root,height);
		}
		bool isbalanceutil(tree_node *root,int &height){//height值也在改变
			if(root==NULL){
				height=0;
				return true;
			}
			int lh=0;
			int rh=0;
			bool isleft=isbalanceutil(root->left,lh);//这个递归是从最上层递归到最底层，然后从最底层开始计数
			bool isright=isbalanceutil(root->right,rh);
			height=(lh>rh?lh:rh)+1;//从０开始计算
			return (abs(lh-rh)<=1&&isleft&&isright);//递归
		}
};

class solution2{
	public:
		bool isbalance(tree_node *root){
			if(root=NULL){
				return true;
			}
			int left=tree_depth(root->left);
			int right=tree_depth(root->right);
			if(left-right>1||left-right<-1){
				return false;
			}
			return isbalance(root->left)&&isbalance(root->right);
		}
		int tree_depth(tree_node *root){
			if(root==NULL){
				return 0;
			}
			int left=1;
			int right=1;
			left+=tree_depth(root->left);
			right+=tree_depth(root->right);
			return left>right?left:right;
		}
};
int main(){
	return 0;
}
