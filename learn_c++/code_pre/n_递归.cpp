/*==============================================================================
    > File Name: n_递归.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月06日 星期日 23时06分00秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
int fun(int n){
	int num=0;
	(n>0)&&(num=n+fun(n-1));
	return num;
}
int main(){
	int n;
	cin>>n;
	int sum=fun(n);
	cout<<sum<<endl;
	return 0;
}
