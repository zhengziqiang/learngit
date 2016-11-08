/*==============================================================================
    > File Name: 链表.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年10月05日 星期三 20时17分04秒
 ==========================================================================*/

#include<iostream>
using namespace std;
typedef struct node{
	int val;
	struct node *next;
}*pnode;
class mynode{
	private:
		pnode phead;
	public:
		mynode(){
			this->phead=NULL;
		}
		~mynode(){
			while(this->phead!=NULL){
				pnode ptmp=phead->next;
				delete phead;
				phead=ptmp;
			}
		}
		void init(){
			int a;
			char ans;
			pnode ptail,pnew;
			do{

			
			cout<<"please input the number of the node"<<endl;
			cin>>a;
			if(phead ==NULL){
				phead = new node;
				phead->val=a;
				phead->next=NULL;
				ptail=phead;
			}
			else{
				ptail=phead;
				while(ptail->next!=NULL){
					ptail=ptail->next;

				}
				pnew =new node;//new 一个新的节点来接收新的值
				pnew->val=a;
				pnew->next=NULL;
				
				ptail->next=pnew;//tail是前一个的意思,现在是在串联整个数据结构
				ptail=ptail->next;
			}
			cout<<"是否继续"<<endl;
			cin>>ans;
		
		
			}
			while(ans=='y'|ans=='Y');
		}
		
		void add(int val){
			if(phead=NULL){
				phead=new node;
				phead->val=val;
				phead->next=NULL;

			}
			else {
				pnode ptmp=phead;
				while(ptmp->next!=NULL){
					ptmp=ptmp->next;
				}
				pnode pnew= new node;
				pnew->val=val;
				pnew->next=NULL;
				ptmp->next=pnew;//串联在一起
			}
		}
		int get_count(){
			int count=0;
			pnode ptmp=phead;
			while(ptmp->next!=NULL){
				count++;
				ptmp=ptmp->next;
			}
			return count;
		}
		int delat(int k){
			pnode p1,p2,ptmp;
			if(phead==NULL){
				return -1;
			}
			if(k<0||k>this->get_count()-1){
				return -1;
			}
			if(this->get_count()==1){
				delete phead;
				phead=NULL;
				return 0;
			}
			if(k==0){
				ptmp=phead;
				phead=ptmp->next;
				delete ptmp;
				return 0;
			}
			if(k==this->get_count()-1){
				pnode p,ptmp;
				p=phead;
				while(p->next->next!=NULL){
					p=p->next;
				}
				ptmp=p->next;
				p->next=NULL;
				delete ptmp;
				return 0;
			}
			p1=phead;
			int i=0;
			while(i<k-1){
				p1=p1->next;
				i++;
			}
			ptmp=p1->next;
			p2=p1->next->next;
			p1->next=p2;
			delete ptmp;
			return 0;
		}

		int	insert_at(int val,int k){
			pnode p1,p2,pnew,ptmp;
			if(phead==NULL){
				return -1;

			}
			if(k<0||k>this->get_count()-1){
				return -1;
			}
			if(k==0){
				ptmp=phead;
				pnew=new node;
				pnew->val=val;
				pnew->next=NULL;
				phead=pnew;
				pnew->next=ptmp;
				return 0;
			}

			p1=phead;
			int i=0;
			while(i<k-1){
				p1=p1->next;
				i++;

			}
			p2=p1->next;
			pnew =new node;
			pnew->val=val;
			pnew->next=NULL;
			p1->next=pnew;
			pnew->next=p2;
			return 0;
		}

		int find(int val){
			int i=0;
			pnode ptmp=phead;
			while(ptmp!=NULL){
				if(ptmp->val==val){
					return i;
				}
				ptmp=ptmp->next;
				i++;
			}
			return -1;
		}

		int travel(){
			pnode ptmp=this->phead;
			while(ptmp->next!=NULL){
				cout<<ptmp->val<<endl;
				ptmp=ptmp->next;
			}
			cout<<endl;
		}
		
		void sort(){
			int n=this->get_count();
			pnode p1,p2;
			for(int i=0;i<n-1;i++){
				p1=phead;
				for(int j=0;j<n-1-i;j++){
					p2=p1->next;
					if(p1->val<p2->val){
						int k=p1->val;
						p1->val=p2->val;
						p2->val=k;
					}
					p1=p1->next;
				}
			}
		}
};
int main(){
	mynode list;
	return 0;
}
