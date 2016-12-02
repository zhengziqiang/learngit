/*************************************************************************
 > File Name: random.h
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年05月09日 星期一 18时50分12秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define random(x) (rand()%x)
//宏的基本操作和实现
//如果要实现其他的一些随机数,可以这样做
int fun(){
	int x;
	for(x=0;x<10;x++)printf("%d\n",random(100));
	float a=(float)rand()/((float)RAND_MAX/10);//得到0,10之间的随机浮点数

	printf("浮点数a=%f",a);
	int mn=(int)rand()%(n-m+1) + m;//得到[m,n]区间的一些整型的数
	return 0;
}
