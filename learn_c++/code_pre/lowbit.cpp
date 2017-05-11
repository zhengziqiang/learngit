/*==============================================================================
    > File Name: lowbit.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月26日 星期一 18时42分03秒
 ==========================================================================*/

#include<iostream>
using namespace std;
int fun(int x){
	return x&(-x);
}
int main(){
	cout<<fun(5)<<endl;
	cout<<fun(4)<<endl;
	
	cout<<fun(24)<<endl;
	cout<<fun(99)<<endl;
}
