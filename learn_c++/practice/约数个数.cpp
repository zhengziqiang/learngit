/*==============================================================================
    > File Name: 约数个数.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月08日 星期二 19时24分46秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<math.h>
using namespace std;
int fun(int n){
	int m=sqrt(n);
	int count=0;
	if(m*m==n)
		count++;
	for(int i=1;i<=m;i++){
		if(n%i==0)
			count++;
	}
	return 2*count;
}
int main(){
	int a;
	cin>>a;
	cout<<fun(a)<<endl;
	return 0;
}
