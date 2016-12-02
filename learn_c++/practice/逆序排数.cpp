/*==============================================================================
    > File Name: 逆序排数.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月08日 星期二 19时56分24秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
int main(){
	vector <int> shu;
	int n;
	while(cin>>n){
		if(n==0)
			break;
		shu.push_back(0);

	}
	shu.reserve();
	for(int i=shu.size()-1;i>=0;i--){
		cout<<shu[i]<<" ";
	}
}
