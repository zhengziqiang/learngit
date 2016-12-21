/*==============================================================================
    > File Name: 环形加油站.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年12月16日 星期五 13时55分10秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
int return_index(vector <int> gas,vector <int> cost){
	int current=0;
	int start=gas.size();
	int total=0;
	do{
		if(gas[current]+total>=cost[current]){
			total+=(gas[current]-cost[current]);
			current++;
		}
		else{
			start--;
			total+=(gas[start]-cost[start]);
		}
	}while(current!=start);
	return total>=0?start%gas.size():-1;
}
int main(){
	return 0;
}
