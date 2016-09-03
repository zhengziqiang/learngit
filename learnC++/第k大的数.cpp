/*************************************************************************
 > File Name: 第k大的数.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年04月05日 星期二 18时09分49秒
 ************************************************************************/

#include<iostream>
using namespace std;
int main()
{
	int n,k,b,m;
	cin>>n>>k;
	int a[n];
	for(int i=0;i<n;i++)
	{
		cin>>a[i];
	}
	for(int j=0;j<n;j++)
	{
		m=0;
		b=0;
		for(int l=0;l<n;l++)
		{
			if(a[l]>a[j])
				m+=1;
			else if(a[l]==a[j]){
				b+=1;
			}
		}
		if(k>=m+1&&k<=m+b){
			cout<<a[j]<<endl;
			break;
		}
	}
	return 0;
	
}
