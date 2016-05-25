/*************************************************************************
 > File Name: random.h
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年05月13日 星期五 12时58分23秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define random(x)(rand()%x)
int createdata(int arr[],int n){
	srand(time(0));
	int i;
	for(i=0;i<n;i++)arr[i]=random(100);
	return 0;
}
 
