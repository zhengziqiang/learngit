/*==============================================================================
    > File Name: root树求和.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年02月15日 星期三 09时45分52秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
struct Treenode{
	int val;
	Treenode *left;
	Treenode *right;
	Treenode(int x):val(x),left(NULL),right(NULL){

	}
};
int method(Treenode *root){
	if(!root){
		return 0;
	}
	int sum=0;
	vector <Treenode *> v;
	v.push_back(root);
	while(v.size()>0){
		Treenode *node=v.back();
		v.pop_back();
		if(node->left){
			node->left->val+=(10*node->val);
			v.push_back(node->left);
		}
		if(node->right){
			node->right->val+=(10*node->val);
			v.push_back(node->right);
		}
		if(!node->left && !node->right){
			sum+=node->val;//左右节点空
		}
	}
	return sum;
}

int main(){
	return 0;
}
