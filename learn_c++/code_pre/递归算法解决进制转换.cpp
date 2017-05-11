/*************************************************************************
 > File Name: 递归算法解决进制转换.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年05月12日 星期四 16时20分42秒
 ************************************************************************/

#include<iostream>
#include<string>
#include<stdlib.h>
#include<string.h>
using namespace std;
int fun(char *s,int n,int b){
	char bit[]={
		"0123456789ABCDEF"
	};
	int len;
	if(n==0){
		strcpy(s,"");
		return 0;
	}
	fun(s,n/b,b);
	len=strlen(s);
	s[len]=bit[n%b];
	s[len+1]='\0';
}
int main(){
	system("cls");
	char s[80];
	cout<<"please input a number:"<<endl;
	int i,base,old;
	cin>>old;
	cout<<"tranform mission:"<<endl;
	cin>>base;
	fun(s,old,base);
	cout<<"转换后的数：";
	cout<<s<<endl;
	return 0;
}
