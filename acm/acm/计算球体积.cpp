/*==============================================================================
    > File Name: 计算球体积.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月12日 星期一 17时08分14秒
 ==========================================================================*/

#include<iostream>
#include<iomanip>
#include<vector>
using namespace std;
#define pi 3.1415927
int main(){
	float n;
	vector <float> ans;
	int count=0;
	while(cin>>n){
		float tmp=pi*4*n*n*n/3;
		ans.push_back(tmp);
		count++;
	}
	for(int i=0;i<count;i++){
		cout<<setiosflags(ios::fixed)<<setprecision(3)<<ans[i]<<endl;
	}
	return 0;
}
