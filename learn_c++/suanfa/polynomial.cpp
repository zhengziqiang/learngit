/*==============================================================================
    > File Name: polynomial.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年03月30日 星期四 16时26分08秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
struct polynomial{
	int coe;
	int index;
	polynomial *next;
	polynomial(){
		coe=0;
		index=0;
		next=NULL;
	}
};
bool is_exist(polynomial *h,int coe,int target){
	polynomial *ptr=h;
	while(ptr){
		if(target==ptr->index){
			ptr->coe=ptr->coe+coe;
			return true;
		}
		ptr=ptr->next;
	}
	return false;
}
void add_index(polynomial *h1,int coe_,int index_){
	polynomial *node;
	node->coe=coe_;
	node->index=index_;
	node->next=NULL;
	polynomial *head=h1;
	while(head){
		if(head->next==NULL)
			break;
		head=head->next;
	}
	head->next=node;
}
polynomial *matmul(polynomial *h1,polynomial *h2){
	polynomial *ans=new polynomial[20];
	polynomial *ptr1=h1;
	polynomial *ptr2=h2;
	while(ptr1->next){
		ptr2=h2;
		while(ptr2->next){
			int tmp_coe=0;
			int tmp_index=0;
			tmp_coe=(ptr1->coe)*(ptr2->coe);
			tmp_index=(ptr1->index)*(ptr2->index);
			if(is_exist(ans,tmp_coe,tmp_index)){
				ptr2=ptr2->next;
			}
			else{
				add_index(ans,tmp_coe,tmp_index);
				ptr2=ptr2->next;
			}
		}
	}
	return ans;
}
int main(){
	polynomial *h1=new polynomial[10];
	polynomial *h2=new polynomial[10];
	int m,n;
	polynomial *head=NULL;
	int count=0;
	cout<<"please input h1"<<endl;
	while(cin>>m>>n){
		if(m==n&&n==0)
			break;
		h1[count].coe=m;
		h1[count].index=n;
		h1[count].next=&h1[++count];
	}
	h1[count].next=NULL;
	count=0;
	while(cin>>m>>n){
		if(m==n&&n==0){
			break;
		}
		h2[count]coe=m;
		h2[count].index=n;
		h2[count].next=&h2[++count]
	}
	h2[count].next=NULL;
	head=h1;
	while(head->next){
		cout<<head->coe<<" "<<head->index<<endl;
		head=head->next;
	}
	return 0;
}
