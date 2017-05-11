/*==============================================================================
    > File Name: setw.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月29日 星期四 19时27分38秒
 ==========================================================================*/

#include<iostream>
#include<iomanip>
using namespace std;
int main(){
	int m=3;
	for(int i=0;i<5;i++){
		for(int j=0;j<4;j++){
			cout<<i*5+j<<setw(4);
		}
		cout<<endl;
	}
	return 0;
}
