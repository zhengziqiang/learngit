/*==============================================================================
    > File Name: 数位偶数.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月10日 星期六 10时59分05秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<stdio.h>
using namespace std;
int main(){
	int n;
	int a=1;
	int res=0;
	int count=0;
	vector <int> ans;
	while(cin>>n){
		while(n/a){
			if(((n%(a*10))/a)%2==0)
				res+=((n%(a*10)/a));
			a*=10;
		}
		a=1;
		ans.push_back(res);
		res=0;
		count++;
	}
	for(int i=0;i<count;i++){
		cout<<ans[i]<<endl<<endl;
	}
	return 0;
	//最后键盘输入一个eof来结束输入,并且后面的语句也会正常运行
}
