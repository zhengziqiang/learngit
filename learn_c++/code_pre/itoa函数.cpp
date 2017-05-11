/*==============================================================================
    > File Name: itoa函数.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月11日 星期日 18时30分43秒
 ==========================================================================*/

#include<iostream>
#include<stdlib.h>
using namespace std;
int main(){
	int a=12345;
	string str;
	itoa(a,str,10);
	cout<<str<<endl;
	return 0;
}
