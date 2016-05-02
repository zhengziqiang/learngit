/*************************************************************************
 > File Name: fun.h
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年04月10日 星期日 00时29分10秒
 ************************************************************************/

#include<iostream>
using namespace std;
int fun(int m,int n)
{
	cout<<"this is the function"<<endl;
	for(int i=0;i<n;i++)m*=m;
	cout<<m<<endl;
	return m;
}
