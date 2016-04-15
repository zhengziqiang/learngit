/*************************************************************************
 > File Name: const数组.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年04月15日 星期五 15时16分51秒
 ************************************************************************/

#include<iostream>
using namespace std;
int main(){
	int a[2];
	cin>>a[0]>>a[1];
	int *const p=a;
	*p=8;
	cout<<*p<<" "<<*(p+1)<<endl;
	return 0;
}
