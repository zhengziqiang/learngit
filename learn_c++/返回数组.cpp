/*************************************************************************
 > File Name: 返回数组.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年05月09日 星期一 19时26分49秒
 ************************************************************************/

#include<iostream>
#include<string>
using namespace std;
int fun(int a[],int m){
	for(int i=0;i<m;i++)a[i]=i;
	return a[m];
}
int main(){
	int m;
	cin>>m;
	int a[m];
	int *p=a;
	fun(a,m);
	for(int i=0;i<m;i++)cout<<a[i]<<endl;
	return 0;
}
