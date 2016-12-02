/*************************************************************************
 > File Name: shishi.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年05月11日 星期三 19时29分59秒
 ************************************************************************/

#include<iostream>
#include<string>
#include "quick.h" 
using namespace std;
 
int fun(int a[][2],int m,int n){
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			cin>>a[i][j];
		}
	}
	return 0;
}
int fun2(int a[][2],int m,int n){
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			cout<<a[i][j]<<endl;
		}
	}
	return 0;
}
int main(){
	int a[2][2]={
		1,2,3,4
	};
	fun(a,2,2);
	fun2(a,2,2);
	return 0;
}
