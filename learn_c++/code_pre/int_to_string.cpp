/*==============================================================================
    > File Name: int_to_string.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月10日 星期六 15时47分17秒
 ==========================================================================*/

#include<iostream>
#include<stdio.h>
#include<string>
using namespace std;
int main(){
	int m=234;
	char a[10];
	sprintf(a,"%d",m);
	string str(a);
	for(int i=0;str[i]!='\0';i++)
		cout<<str[i]<<endl;
	return 0;
}
