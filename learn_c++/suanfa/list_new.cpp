/*==============================================================================
    > File Name: list_new.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年04月07日 星期五 14时05分44秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
struct List{
	int val;
	List *next;
};
void josef(int m){
	List *p=new List;
	p->val=0;
	p->next=NULL;
	List *ptr;
	List *ptmp=p;
	for(int i=0;i<m;i++){
		ptr=new List;
		ptr->val=i+1;
		ptr->next=NULL;
		p->next=ptr;
		p=p->next;
	}
	p->next=ptmp;
	int cnt=0;
	while(ptmp){
		if(cnt>6){
			break;//没有break 就会陷入死循环，因为是一个环
		}
		cout<<ptmp->val<<endl;
		ptmp=ptmp->next;
		cnt+=1;
	}
	//连成一个环了
}
int main(){
	List *p1=new List;
	p1->val=1;
	cout<<"约瑟夫环"<<endl;
	josef(5);
	cout<<"endl"<<endl;
	p1->next=NULL;
	List *p2=new List;
	p2->val=2;
	p1->next=p2;
	List *ptr=p1;//等于是让一个随机指针去指向开头
	while(ptr){//地址不为空就能进行循环
		cout<<ptr->val<<endl;
		ptr=ptr->next;
	}//现在ptr已经为空,为NULL
	List *p;
	ptr=p1;
	List *ptr2;
	cout<<ptr->val<<endl;
	for(int i=0;i<5;i++){
		p=new List;//申请一个List 那么大的空间
		p->val=3;
		p->next=NULL;
		while(ptr->next){
			ptr=ptr->next;
		}
		ptr->next=p;//将整个list进行连接
	}
	ptr=p1;
	while(ptr){//地址不为空就能进行循环
		cout<<ptr->val<<endl;
		ptr=ptr->next;
	}
	return 0;
}
