/*************************************************************************
 > File Name: random.h
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年05月09日 星期一 18时50分12秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define random(x)(rand()%x)
int fun(){
	int x;
	for(x=0;x<10;x++)printf("%d\n",random(100));
	return 0;
}
