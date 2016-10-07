/*************************************************************************
 > File Name: 折半查找.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年05月22日 星期日 10时26分40秒
 ************************************************************************/

#include<iostream>
#include<string>
using namespace std;
int fun(int s[],int n,int key){
	int high,low,mid;
	low=0;high=n-1;
	while(low<=high){
		mid=(low+high)/2;
		if(s[mid]==key)return mid;
		else if(s[mid]>key)high=mid-1;
		else low=mid+1;
	}
	return -1;
}
int main(){
	int a[10];
	for(int i=0;i<10;i++)cin>>a[i];
	int k=fun(a,10,3);
	cout<<k<<endl;
	return 0;
}
