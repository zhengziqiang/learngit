/*==============================================================================
    > File Name: 链表操作.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年02月20日 星期一 16时18分36秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
struct linklist{
	int val;
	linklist *next;
	linklist():val(0),next(NULL){

	}
	linklist(int x):val(x),next(NULL){

	}
};
linklist *remove(linklist *head,int target){
	static linklist dummy(-1);
	dummy.next=head;
	linklist *p=&dummy;//取开头的地址
	while(p->next){
		if(p->val==target){//在循环遍历
			p->next=p->next->next;
		}else{
			p=p->next;
		}
	}
	return dummy.next;//由于我们添加了一个dummy这样一个不需要的值，所以在这里我们返回的是它下面一个值的指针
}
int main(){
	linklist *n=new linklist[5];
	for(int i=0;i<5;i++){
		n[i].val=i+1;
		if(i+1<5){
			n[i].next=&n[i+1];//连接在一起
		}
	}
	linklist *p=NULL;
	p=n;
	while(p!=NULL){
		cout<<p->val<<endl;
		p=p->next;
	}
	//在这里就是增加一个节点，然后将节点插入到链表中
	linklist fakehead(0);
	fakehead.next=n;//直接进行插入操作
	//fakehead.next=&n[1];
	//输出会是0 2 3 4 5，因为1的位置被fakehead占据
	cout<<"my testing "<<endl;
	n=&fakehead;
	p=n;
	while(p!=NULL){
		cout<<p->val<<endl;
		p=p->next;
	}
	return 0;
}
