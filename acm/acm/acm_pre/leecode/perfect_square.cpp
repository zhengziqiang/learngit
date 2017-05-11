/*==============================================================================
    > File Name: perfect_square.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月28日 星期三 20时09分30秒
 ==========================================================================*/

#include<iostream>
#include<limits.h>
#include<vector>
using namespace std;
class solution{
	public:
		int sum_square(int n){
			vector <int> dp(n+1,INT_MAX);
			dp[0]=0;
			for(int i=0;i<=n;i++){
				for(int j=1;i+j*j<=n;j++){
					dp[1+j*j]=min(dp[i+j*j],dp[i]+1);
				}
			}
			return dp[n];
		}
};
int main(){
	solution s1;
	int a=s1.sum_square(12);
	cout<<s1.sum_square(12)<<endl;
	cout<<a<<endl;
	return 0;
}
