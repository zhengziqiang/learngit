/*************************************************************************
 > File Name: while输入.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年04月30日 星期六 22时14分47秒
 ************************************************************************/

#include<iostream>
using namespace std;
int main(){
	int a;
	while(cin>>a){
		cout<<a<<endl;
		if(a==0)break;
	}
	return 0;
}
