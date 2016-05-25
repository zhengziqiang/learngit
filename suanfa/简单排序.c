/*************************************************************************
 > File Name: 简单排序.c
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年05月13日 星期五 12时47分25秒
 ************************************************************************/

#include<stdio.h>
#include "random.h"
int selectsort(int a[],int n){
	int i,j,t,k;
	for(i=0;i<n-1;i++){
		k=i;
		for(j=i+1;j<n;j++)
			if(a[k]>a[j]) k=j;
		t=a[i];
		a[i]=a[k];
		a[k]=t;
	}
	return 0;
}
int main(){
	int a[10],i;
	createdata(a,10);
	for(i=0;i<10;i++)printf("%3d\n",a[i]);
	printf("排序后：\n");
	selectsort(a,10);
	for(i=0;i<10;i++)printf("%3d\n",a[i]);
	return 0;
}
