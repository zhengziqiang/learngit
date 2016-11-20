/*==============================================================================
    > File Name: convert_sorted_list_tobst.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月20日 星期日 09时59分19秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<stdlib.h>
#include<queue>
using namespace std;
struct list_node{
	int val;
	list_node *next;
	list_node(int x):val(x),next(NULL){

	};
};
struct tree_node{
	int val;
	tree_node *left;
	tree_node *right;
	tree_node(int x):val(x),left(NULL),right(NULL){

	};
};
tree_node *sorted_tobst(int low,int high,list_node *&head);//指针的引用

tree_node *sorted_tobst(list_node *head){
	int len=0;
	for(list_node *p=head;p!=NULL;p=p->next){
		len++;
	}
	return sorted_tobst(0,len-1,head);
}

tree_node *sorted_tobst(int low,int high,list_node *&head){//之所以使用指针的使用是因为在转化的时候会用到队列的next
	if(low>high||head==NULL){
		return NULL;
	}
	int mid=low+(high-low)/2;
	tree_node *left_node =sorted_tobst(low,mid-1,head);
	tree_node *node=new tree_node(head->val);
	node->left=left_node;
	head=head->next;//用到next
	tree_node *right_node=sorted_tobst(mid+1,high,head);
	node->right=right_node;
	return node;
}

void print(tree_node *root){
	queue <tree_node *> q;
	q.push(root);
	while(q.size()>0){
		tree_node *n=q.front();
		q.pop();
		if(n==NULL){
			cout<<"# ";
			continue;
		}
		cout<<n->val<<" ";
		q.push(n->left);
		q.push(n->right);

	}
	cout<<endl;
}

list_node *create(int a[],int n){
	list_node *head=NULL,*p=NULL;
	for(int i=0;i<n;i++){
		if(head==NULL){
			head=p=new list_node(a[i]);
		}else{
			p->next=new list_node(a[i]);
			p=p->next;//
		}
	}
	return head;
}
void print_list(list_node *h){
	while(h!=NULL){
		cout<<h->val<<" ";
		h=h->next;
	}
	cout<<endl;
}

int main(int argc,char **argv){
	int n=8;
	if(argc>1){
		n=atoi(argv[1]);
	}
	int *a=new int [n];
	for(int i=0;i<n;i++){
		a[i]=i+1;
	}
	list_node *head=create(a,n);
	print_list(head);
	tree_node *root=sorted_tobst(head);
	print(root);
	delete []a;
	return 0;
}
