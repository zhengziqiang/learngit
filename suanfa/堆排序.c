/*************************************************************************
 > File Name: 堆排序.c
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年05月13日 星期五 13时22分54秒
 ************************************************************************/

#include<stdio.h>
#include "random.h"
int headadjust(int a[],int s,int n){
	int j,t;
	while(2*s+1<n){
		j=2*s+1;
		if((j+1)<n){
			if(a[j]<a[j+1])j++;
		}
		if(a[s]<a[j]){
			t=a[s];
			a[s]=a[j];
			a[j]=t;
			s=j;
		}
		else break;
	}
	return 0;
}
int headsort(int a[],int n){
	int t,i;
	int j;
	for(i=n/2-1;i>=0;i--)headadjust(a,i,n);
	for(i=n-1;i>0;i--){
		t=a[0];
		a[0]=a[i];
		a[0]=t;
		headadjust(a,0,i);
	}
}
int main(){
	printf("原数据：\n");
	int i;
	int a[6];
	createdata(a,6);
	for(i=0;i<6;i++)
	printf("%4d",a[i]);
	printf("\n");
	printf("排序后：\n");
	headsort(a,6);
	for(i=0;i<6;i++)printf("%4d",a[i]);
	return 0;
}
