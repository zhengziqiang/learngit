/*==============================================================================
    > File Name: 卖股票.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月18日 星期五 21时57分47秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
int fun(vector <int> equity){
	int n=equity.size();
	int begin=0,end=0,max=0,delta=0;
	for(int i=0;i<n;i++){
		end=i;
		delta=equity[end]-equity[begin];
		if(delta<=0){
			begin=i;
		}
		if(max<delta){
			max=delta;
		}
	}
	return max;
}
int main(){
	int a[]={
		1,2,8,3,10,4
	};
	vector <int> n(a,a+6);//新的赋值方式，vector的赋值方式
	cout<<fun(n)<<endl;
	vector <int> ans;
	ans.insert(ans.begin(),a,a+6);//新的赋值方式
	return 0;
}
