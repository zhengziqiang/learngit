/*==============================================================================
    > File Name: 子集之和_回朔算法.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月14日 星期一 17时25分52秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
int n=5;
int w[5]={2,3,5,7,9};
int W=15;
int total=15;
int weight=0;
vector <int> include(n,0);
bool promising(int i){
	return (weight+total>=W)&&(weight==W||weight+w[i+1]<=W);
}
void sum_of_weight(int i,int weight,int total){
	if(promising(i)){
		if(weight==W){
			for(int j=0;j<include.size();j++){
				cout<<include[j]<<" ";
			}
			cout<<endl;
		}
		else{
			include[i+1]=1;//包含这个重量
			sum_of_weight(i+1,weight+w[i+1],total-w[i+1]);
			include[i+1]=0;
			sum_of_weight(i+1,weight,total-w[i+1]);
		}
	}
}
int main(){
	return 0;
}
