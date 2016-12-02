/*==============================================================================
    > File Name: c的随机数.c
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月03日 星期六 14时40分45秒
 ==========================================================================*/

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int main(){
	int *ptr;
	ptr=(int*)malloc(sizeof(int)*5);
	int i=0;
	srand((unsigned)time(NULL));
	for(i=0;i<5;i++){
		int a=(int)rand();
		ptr[i]=a;
	}
	free(ptr);
	for(i=0;i<5;i++)
		printf("%d\n",ptr[i]);
	return 0;
}
