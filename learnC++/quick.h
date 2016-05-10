/*************************************************************************
 > File Name: quick.h
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年05月10日 星期二 15时01分21秒
 ************************************************************************/

#include<iostream>
#include<string>
using namespace std;
int division(int a[],int m,int n){
	int base=a[m];
	while(m<n){
		while(m<n&&a[n]>base)--n;
		a[m]=a[n];
		while(m<n&&a[m]<base)++m;
		a[n]=a[m];
	}
	a[m]=base;
	return m;
}
int fun(int a[],int m,int n){
	int i,j;
	if(m<n){
		i=division(a,m,n);
		fun(a,m,i-1);
		fun(a,i+1,n);
	}
}
int input(int a[],int m){
	for(int i=0;i<m;i++)cin>>a[i];
}
int create(int a[],int n){
	for(int i=0;i<n;i++)cin>>a[i];
	return 0;
}
int out(int a[],int m){
	for(int i=0;i<m;i++)cout<<a[i]<<endl;
	return 0;
}
int create(int m){
	cin>>m;
	return 0;
}
