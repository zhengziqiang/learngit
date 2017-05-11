/*************************************************************************
 > File Name: putback.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年04月15日 星期五 14时47分59秒
 ************************************************************************/

#include<iostream>
using namespace std;
int main(){
	char ch1,ch2,ch3;
	cin>>ch1>>ch2>>ch3;
	cout<<ch1<<ch2<<ch3<<endl;
	cin>>ch1;
	cin.putback(ch1);
	cin>>ch2>>ch3;
	cout<<ch1<<ch2<<ch3<<endl;
	return 0;
}
