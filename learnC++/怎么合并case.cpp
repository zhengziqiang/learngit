/*************************************************************************
 > File Name: case.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年04月17日 星期日 19时02分36秒
 ************************************************************************/

#include<iostream>
using namespace std;
int main(){
	int m;
	cin>>m;
	switch(m){
		case 1:
		case 2:
			cout<<"hello"<<endl;break;
		default:
			cout<<"default"<<endl;
	}
	return 0;
}
