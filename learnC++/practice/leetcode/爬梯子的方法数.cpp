/*==============================================================================
    > File Name: 爬梯子的方法数.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月18日 星期五 23时37分03秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
int fun(int n){
	if(n<=3)
		return n;
	int a[2]={2,3};
	for(int i=4;i<=n;i++){
		int t=a[0]+a[1];
		a[0]=a[1];
		a[1]=t;
		
	}
	return a[1];
}
int main(){
	cout<<fun(4)<<endl;
	return 0;
}
