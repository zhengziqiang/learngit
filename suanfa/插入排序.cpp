/*************************************************************************
 > File Name: 插入排序.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年05月22日 星期日 09时30分30秒
 ************************************************************************/

#include<iostream>
#include<string>
#include "random.h"
using namespace std;
int insertsort(int a[],int n){
	int i,j,t;
	for(i=1;i<n;i++){
		t=a[i];
		for(j=i-1;j>=0;--j){
			a[j+1]=a[j];
		}
		a[j+1]=t;
	}
	return 0;
}
int main(){
	int i,length=10;
	int a[length];
	createdata(a,length);
	for(int i=0;i<length;i++)cout<<a[i]<<endl;
	insertsort(a,length);
	for(int i=0;i<length;i++)cout<<a[i]<<endl;
	return 0;
}
