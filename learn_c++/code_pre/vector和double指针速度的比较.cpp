/*==============================================================================
    > File Name: vector和double指针速度的比较.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月06日 星期二 14时43分18秒
 ==========================================================================*/

#include<iostream>
#include<time.h>
#include<vector>
using namespace std;
int main(){
	time_t t1;
	t1=time(NULL);
	vector <vector <int> > vec(1000,vector<int>(1000,0));
	for(int i=0;i<1000;i++)
		for(int j=0;j<1000;j++)
			vec[i][j]=1;
	time_t t2;
	t2=time(NULL);
	cout<<t1<<endl;
	cout<<t2<<endl;
	cout<<t2-t1<<endl;
	return 0;
}
