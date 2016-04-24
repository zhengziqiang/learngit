/*************************************************************************
 > File Name: 多个返回值.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年04月24日 星期日 15时13分16秒
 ************************************************************************/

#include<iostream>
using namespace std;
int fun(int a,int b){
	if(a==1){
		return (b+1);
	}
	else{
		return b;
	}
}
int  main(){
	int m,n;
	cout<<"please input a number:"<<endl;
	cin>>m>>n;
	int p=fun(m,n);
	cout<<p<<endl;
	return 0;
}
