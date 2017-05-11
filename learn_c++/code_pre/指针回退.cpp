/*==============================================================================
    > File Name: 指针回退.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月07日 星期三 15时02分27秒
 ==========================================================================*/

#include<iostream>
using namespace std;
int main(){
	int *p;
	p=new int[5];
	for(int i=0;i<5;i++)
		p[i]=i;
	for(int i=0;i<5;i++){
		cout<<*p<<endl;
		p++;
	}
	p-=5;
	for(int i=0;i<5;i++){
		cout<<*p<<endl;
		p++;
	}
	p-=5;//必须回退到首地址，要不然会删出界
	delete p;//delete的删除机制是从头删到尾，删除固定个数
	return 0;
}
