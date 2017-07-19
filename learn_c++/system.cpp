/*==============================================================================
    > File Name: system.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年05月11日 星期四 21时44分24秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<string>
#include <unistd.h>
using namespace std;
int fun(int n,string name){
	if(n==-99){
		cout<<"the varible "<<name<<" is empty"<<endl;
		pause();
	}
	else{
		return 0;
	}
}
int main(){
	int n=-99;
	string name="n_1_2";
	fun(n,name);
	cout<<"no problem"<<endl;
	return 0;
}
