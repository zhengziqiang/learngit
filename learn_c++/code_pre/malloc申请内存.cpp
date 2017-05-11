/*==============================================================================
    > File Name: malloc申请内存.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年08月17日 星期三 08时38分11秒
 ==========================================================================*/

#include<iostream>
#include<stdlib.h>
#include<malloc.h>
using namespace std;
int main(){
	int *p;
	p=(int*)malloc(sizeof(int)*5);
	for(int i=0;i<5;i++){
		*(p+i)=i+2;
	}
	for(int i=0;i<5;i++){
		cout<<*(p+i)<<endl;
	}
	free(p);
	p=NULL;
	return 0;
}
