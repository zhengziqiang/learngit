/*************************************************************************
 > File Name: const.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年04月15日 星期五 15时05分43秒
 ************************************************************************/

#include<iostream>
using namespace std;
int main(){
	int b=6;
	const int i=5;
	const int *p=&i;
	cout<<*p<<endl;
	p=&b;
	cout<<*p<<endl;
	return 0;
}
