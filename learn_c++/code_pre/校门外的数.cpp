/*************************************************************************
 > File Name: 校门外的数.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年04月15日 星期五 17时33分04秒
 ************************************************************************/

#include<iostream>
using namespace std;
int *fun(int *a,int m,int n){
	for(int i=m-1;i<=n-1;i++){
		if(*(a+i)==1)*(a+i)-=1;
	}
	return 0;
}
int main(){
	int n,m;
	cin>>n>>m;
	int a[m][2];
	for(int i=0;i<m;i++)cin>>a[i][0]>>a[i][1];
	int b[n];
	for(int j=0;j<n;j++)b[j]=1;
	int *p=b;
	for(int l=0;l<m;l++){
		fun(p,a[l][0],a[l][1]);
	}
	int sum=0;
	for(int c=0;c<n;c++){
		sum+=b[c];
	}
	cout<<sum+1<<endl;
	return 0;
}
