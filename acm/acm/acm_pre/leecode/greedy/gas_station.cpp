/*==============================================================================
    > File Name: gas_station.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月29日 星期四 20时29分07秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
class solution{
	public:
		int can_complete_circuit(vector <int> &gas, vector<int> &cost){
			int sum=0;
			int total= 0;
			int k=0;
			for(int i=0;i<(int)gas.size();i++){
				sum+=gas[i]-cost[i];
				if(sum<0){
					k=i+1;
					sum=0;
				}
				total+=gas[i]-cost[i];
			}
			if(total<0){
				return -1;
				
			}
			else{
				return k;
			}
		}
};
int main(){
	return 0;
}
