/*==============================================================================
    > File Name: new申请内存.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年08月17日 星期三 08时32分53秒
 ==========================================================================*/

#include<iostream>
using namespace std;
int main(){
	int *p;
	p=new int[5];
	for(int i=0;i<5;i++){
		*(p+i)=i+2;
	}
	for(int i=0;i<5;i++){
		cout<<*(p+i)<<endl;
	}
	delete []p;
	return 0;
}
