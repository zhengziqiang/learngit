/*************************************************************************
 > File Name: 替身.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年04月15日 星期五 15时33分28秒
 ************************************************************************/

#include<iostream>
using namespace std;
int main(){
	int  i=5;
	int *p;
	p=&i;
	cout<<i<<endl;
	*p=6;
	cout<<i<<endl;
	return 0;
}
