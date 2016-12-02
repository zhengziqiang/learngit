/*==============================================================================
    > File Name: 复数归一化.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月08日 星期二 19时46分16秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<iomanip>
#include<math.h>
using namespace std;
int main(){
	int a,b;
	cin>>a>>b;
	double a_d,b_d;
	a_d=sqrt(a*a+b*b);
	a_d=a/a_d;
	b_d=sqrt(a*a+b*b);
	b_d=b/b_d;
	cout<<setprecision(1)<<a_d<<"+"<<setprecision(1)<<b_d<<"i"<<endl;
	return 0;
}
