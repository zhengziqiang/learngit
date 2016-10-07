/*************************************************************************
 > File Name: 模板.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年05月23日 星期一 21时51分37秒
 ************************************************************************/

#include<iostream>
#include<string>
using namespace std;
template<class T>
T max(T x,T y){
	return (x>y)?x:y;
}
int main(){
	int a=10,b=12;
	cout<<max(a,b)<<endl;
	return 0;
}
