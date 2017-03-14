/*==============================================================================
    > File Name: do_while.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年03月14日 星期二 09时49分17秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
int main(){
	int i=0;
	int j=10;
	do{
		i++;
	}while(i!=j);//直到不满足条件
	cout<<i<<" "<<j<<endl;
	return 0;
}
