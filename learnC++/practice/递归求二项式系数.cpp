/*==============================================================================
    > File Name: 递归求二项式系数.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月09日 星期三 22时15分21秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
int fun(int m,int n){
	if(m==0||m==n){
		return 1;
	}
	else{
		return fun(m,n-1)+fun(m-1,n-1);
	}
}
int main(){
	int n,m;
	cin>>n>>m;
	cout<<fun(n,m)<<endl;
	return 0;
}
