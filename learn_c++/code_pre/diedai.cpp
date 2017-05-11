/*************************************************************************
 > File Name: diedai.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年05月09日 星期一 00时07分24秒
 ************************************************************************/

#include<iostream>
#include<string>
#include<ctime>
using namespace std;
int fun(int m){
	if(m>0)
		return fun(m-1)*m;
	else 
		return 1;
}
int main(){
	int k;
	int sum=1;
	cin>>k;
	double s1,s2,e1,e2;
	s1=clock();
	for(int i=1;i<=k;i++){
		sum*=i;
	}
	e1=clock();
	cout<<"time is "<<e1-s1<<endl;
	s2=clock();
	fun(k);
	e2=clock();
	cout<<"time is "<<e2-s2<<endl;
	return 0;
}
