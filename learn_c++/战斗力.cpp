/*************************************************************************
 > File Name: 战斗力.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年05月09日 星期一 22时08分40秒
 ************************************************************************/

#include<iostream>
#include<string>
using namespace std;
int main(){
	int n;
	cin>>n;
	int a[n];
	for(int i=0;i<n;i++)cin>>a[i];
	int b[n];
	int m;
	for(int i=0;i<n;i++){
		cin>>b[i];
		if(b[i]==0){
			m=i+1;
			break;
		}
	}
	int c[m];
	for(int i=0;i<m;i++)c[i]=b[i];
	for(int i=0;i<n;){
		for(int j=0;j<m;j++){
			if(a[i]==c[j]){
				a[i]=0;
			}
		}
	}	
	int flag=0;
	int t;
	for(int i=0;i<n-1;i++){
		for(int j=n-1;j>i;j--){
			if(a[j-1]>a[j]){

			t=a[j-1];
			a[j-1]=a[j];
			a[j]=t;
			flag=1;
			}
		}
		if(flag==0)break;
		else flag=0;
	}
	for(int i=0;i<n;i++){
		if(a[i]>0)cout<<a[i]<<" ";
	}
	return 0;
}
