/*************************************************************************
 > File Name: 快速排序.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年05月09日 星期一 17时06分41秒
 ************************************************************************/

#include<iostream>
#include<string>
using namespace std;
int fun(int a[],int n){
	int i,j,t,k;
	for(i=0;i<n-1;i++){
		k=i;
		for(j=i+1;j<n;j++)
			if(a[k]>a[j])k=j;
		t=a[i];
		a[i]=a[k];
		a[k]=t;
	}
	return 0;
}
int main(){
	int a[8];
	for(int i=0;i<8;i++){
		cin>>a[i];
	}
	fun(a,8);
	for(int j=0;j<8;j++)cout<<a[j]<<endl;
	return 0;
}
