/*************************************************************************
 > File Name: 方框内引用变量.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年04月23日 星期六 16时16分28秒
 ************************************************************************/

#include<iostream>
using namespace std;
int main(){
	int a[3];
	for(int i=0;i<3;i++)cin>>a[i];
	for(int j=0;j<3;j++)cout<<"a["<<j<<"]="<<a[j]<<endl;
	return 0;
}
