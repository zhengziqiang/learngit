/*==============================================================================
    > File Name: 约瑟夫.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年10月05日 星期三 19时28分52秒
 ==========================================================================*/

#include<iostream>
using namespace std;
typedef struct List{
	int num;
	struct List	*next;
}*plist;
class jose{
	public:
		jose(){}
		jose(int number,int mes):n(number),m(mes){}
		void set();
		void create();
		void del();
	private:
		plist head;
		int n,m,tmp_n;
};
void jose::set(){
	cout<<"please input the two numbers"<<endl;
	cin>>n>>m;
	tmp_n=n;
}
void jose::create(){
	plist p1,p2;
	plist p=new List;
	n+=1;
	p->num=1;
	p2=head=p;
	for(int i=2;i<n;i++){
		p=new List;
		p->num=i;
		p1=p2;
		p2=p;
		p1->next=p2;

	}
	p2->next=head;//连成一个环

}
void jose::del(){
	plist p1=NULL;
	plist p2=head;
	n=tmp_n+1;
	while(n--){
		int s=m-1;
		while(s--){//由于是第m个人就出列
			p1=p2;
			p2=p2->next;
		}
		if(n==0){
			p2=p2->next;
			p1->next=NULL;
			cout<<"the result is "<<p2->num<<endl;

		}
		else{
			p2=p2->next;
			p1->next=p2;//在逐渐消去和递减
		}
	}
}
int main(){
	jose j;
	j.set();
	j.create();
	j.del();
	return 0;

}
