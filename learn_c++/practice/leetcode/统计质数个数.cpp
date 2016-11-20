/*==============================================================================
    > File Name: 统计质数个数.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月20日 星期日 18时57分50秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
int count_prime(int n){
	vector <bool> is_prime(n,true);
	for(int i=2;i*i<n;i++){
		for(int j=i*i;j<n;j+=i){
			is_prime[j]=false;//很精妙的一步计算
		}
	}
	int cnt=0;
	for(int i=2;i<n;i++){
		if(is_prime[i])
			cnt++;
	}
	return cnt;
}
int main(){
	int n;
	cout<<"please input a number"<<endl;
	cin>>n;
	cout<<count_prime(n)<<endl;
	return 0;
}
