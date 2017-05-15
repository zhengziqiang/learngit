/*==============================================================================
    > File Name: random_int.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年05月13日 星期六 09时29分14秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<time.h>
#include<algorithm>
using namespace std;
int main(){
	vector <int> ans(3);
	for(int i=0;i<3;i++){
		ans[i]=rand()%1000;
	}
	sort(ans.begin(),ans.end());
	cout<<ans[0]<<" "<<ans[1]<<" "<<ans[2]<<endl;
	return 0;
}
