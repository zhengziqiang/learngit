/*************************************************************************
 > File Name: cin.read.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年04月15日 星期五 14时54分02秒
 ************************************************************************/

#include<iostream>
using namespace std;
int main(){
	char a[10];
	int i;
	cin.read(a,5);
	for(i=0;a[i]!='\0';i++);
	cout.write(a,i);
	return 0;
}
