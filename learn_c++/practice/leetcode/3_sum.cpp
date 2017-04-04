/*==============================================================================
    > File Name: 3_sum.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年04月04日 星期二 16时36分15秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<algorithm>
#define INT_MAX 12345
//#define 没有分号没有等于号
using namespace std;
int three(vector <int> &num,int target){
	sort(num.begin(),num.end());
	int n=num.size();
	int distance=INT_MAX;
	int result;
	for(int i=0;i<n-2;i++){
		if(i>0&&num[i]==num[i-1]){
			continue;
		}
		int a=num[i];
		int low=i+1;
		int high=n-1;
		while(low<high){
			int b=num[low];
			int c=num[high];
			int sum=a+b+c;
			if(sum-target==0){
				return target;
			}else{
				if(abs(sum-target)<distance){
					distance=abs(sum-target);
					result=sum;
				}
				if(sum-target>0){
					while(high>0&&num[high]==num[high-1]){
						high--;
					}
					high--;
				}else{
					while(low<n&&num[low]==num[low+1]){
						low++;
					}
					low++;
				}
			}
		}
	}
	return result;
}

int main(){

	return 0;
}
