/*==============================================================================
    > File Name: 硬币组合.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月19日 星期六 09时49分09秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
int fun(vector <int> &coin,int mount){
	int sol[mount+1];
	sol[0]=0;
	for(int i =1;i<=mount;i++){
		sol[i]=mount+1;
	}
	for(int i=0;i<coin.size();i++){
		for(int j=coin[i];j<=mount;j++){
			sol[j]=min(sol[j],sol[j-coin[i]]+1);
		}
	}
	if(sol[mount]!=mount+1){
		return sol[mount];
	}
	else{
		return -1;
	}
}
int fun2(vector <int> &coin,int mount){
	const int max=mount+1;
	vector <int> dp(mount+1,max);
	dp[0]=0;
	for(int i=1;i<=mount;i++){
		for(int j=0;j<coin.size();j++){
			if(i>=coin[j]){
				dp[i]=min(dp[i],dp[i-cion[j]]+1);//从每一个小于固定mount的数开始，尝试使用最大的面值，然后动态规划
			}
		}
	}
	return dp[mount]!=max?dp[mount]:-1;
}
int main(){
	vector <int> coin;
	coin.push_back(1);
	coin.push_back(2);
	coin.push_back(5);
	coin.push_back(10);
	coin.push_back(20);
	cout<<fun(coin,123)<<endl;
	return 0;
}
