/*==============================================================================
    > File Name: 3_sum_closed.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月18日 星期五 18时16分59秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<algorithm>
#define INT_MAX 99999
using namespace std;
int fun(vector <int> num,int target){
	sort(num.begin(),num.end());
	int n=num.size();
	int distance = INT_MAX;
	int result;
	for(int i=0;i<n-2;i++){
		if(i>0&&num[i-1]==num[i])
			continue;
		int a=num[i];//这是
		int low=i+1;
		int high=n-1;
		while(low<high){
			int b=num[low];
			int c=num[high];
			int sum=a+b+c;
			if(sum==target){
				return target;
			}
			else{
				if(abs(sum-target)<distance){//保证实时更新
					distance=abs(sum-target);
					result=sum;
				}
				if(sum-target>0){
					while(high>0&&num[high]==num[high-1])//跳过重复值
						high--;
					high--;
				}
				else{
					while(low<n&&num[low]==num[low+1])
						low++;
					low++;
				}
			}
		}
		
	}
	return result;
}
int main(){
	vector <int> vec;
	vec.push_back(-1);
	vec.push_back(2);
	vec.push_back(1);
	vec.push_back(-4);
	cout<<fun(vec,1)<<endl;
	return 0;
}
