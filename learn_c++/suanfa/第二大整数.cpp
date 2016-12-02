/*==============================================================================
    > File Name: 第二大整数.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月08日 星期二 19时19分34秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main(){
	int a;
	vector <int> shu;
	while(cin>>a){
		if(a==0)
			break;
		shu.push_back(a);
	}
	sort(shu.begin(),shu.end());
	int i=shu.size()-2;
	cout<<shu[i]<<endl;
	return 0;
}
