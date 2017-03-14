/*==============================================================================
    > File Name: coin_change.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年03月12日 星期日 10时40分58秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
int main(){
	int amount=12;
	vector <int> sol(amount+1,amount+1);
	sol[0]=0;
	int coins[3]={2,6,8};
	for(int i=0;i<3;i++){
		for(int j=coins[i];j<=amount;j++)
			sol[j]=min(sol[j],sol[j-coins[i]]+1);//from sol[0] start,plus 1 shows that we use the coin once,twice,.....
	}
	if(sol[amount]!=amount+1)
		cout<<sol[amount];
	return 0;
}
