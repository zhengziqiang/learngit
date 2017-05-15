/*==============================================================================
    > File Name: 二叉树.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年10月05日 星期三 23时22分47秒
 ==========================================================================*/

#include<iostream>
using namespace std;
struct tree{
	int data;
	tree *left,*right;
};
class btree{
	static int n;
	static int m;
	public:
		tree *root;
		btree(){
			root=NULL;
		}
		void create(int x);
		void preorder(tree *);
		void inorder(tree *);
		void postorder(tree *);
		void display1(){
			preorder(root);
			cout<<endl;
		}
		void display2(){
			inorder(root);
			cout<<endl;
		}
		void display3(){
			postorder(root);
			cout<<endl;
		}
		int count(tree *);
		int find_leaf(tree *);
		int find_node(tree *);

};
int btree::m=0;
int btree::n=0;
void btree::create(int x){
	tree *newnode=new tree;
	newnode->data=x;
	newnode->right=newnode->left=NULL;
	if(root==NULL){
		root=newnode;

	}
	else{
		tree *back;
		tree *current;
		while(current!=NULL){
			back=current;
			if(current->data>x){
				current=current->left;

			}
			else{
				current=current->right;
			}

		}
		if(back->data>x){
			back->left=newnode;
		}
		else{
			back->right=newnode;
		}
	}
}

int btree::count(tree *p){
	if(p==NULL){
		return 0;
	}
	else 
		return count(p->left)+count(p->right)+1;//使用递归的思想

}
void btree::preorder(tree *tmp){
	if(tmp!=NULL){
		cout<<tmp->data<<" ";
		preorder(tmp->left);
		preorder(tmp->right);//使用递归
	}
}
void btree::inorder(tree *tmp){
	if(tmp!=NULL){
		inorder(tmp->left);
		cout<<tmp->data<<" ";
		inorder(tmp->right);
	}
}
void btree::postorder(tree *tmp){
	if(tmp!=NULL){
		postorder(tmp->left);
		postorder(tmp->right);
		cout<<tmp->data<<" ";
	}
}
//叶子的个数
int btree::find_leaf(tree *tmp){
	if(tmp==NULL){
		return 0;
	}
	else{
		if(tmp->left==NULL&&tmp->right==NULL)
			return n+=1;//递归出口
		else{
			find_leaf(tmp->left);
			find_leaf(tmp->right);
		}
		return n;
	}
}
//节点的个数
int btree::find_node(tree *tmp){
	if(tmp==NULL){
		return 0;
	}
	else{
		if(tmp->left!=NULL&&tmp->right!=NULL){
			find_node(tmp->left);
			find_node(tmp->right);

		}
		if(tmp->left!=NULL&&tmp->right==NULL){
			m+=1;
			find_node(tmp->left);
		}
		if(tmp->left==NULL&&tmp->right!=NULL){
			m+=1;
			find_node(tmp->right);
		}
	}
	return m;
}
int main(){
	return 0;
}
