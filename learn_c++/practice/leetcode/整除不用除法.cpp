/*==============================================================================
    > File Name: 整除不用除法.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月21日 星期一 12时50分36秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<string>
using namespace std;
int divide(int dividend,int divisor){
	int sign=(float)dividend/divisor >0 ? 1: -1;
	unsigned int dvd=dividend > 0 ? dividend : -dividend;
	unsigned int dvs=divisor > 0 ? divisor : -divisor;
	unsigned int bit_num[32];
	unsigned int i=0;
	long long d=dvs;
	bit_num[i]=d;
	while(d<=dvd){
		bit_num[++i]=d=d<<1;
	}
	i--;
	unsigned int result=0;
	while(dvd>=dvs){
		if(dvd>=bit_num[i]){
			dvd-=bit_num[i];
			result+=(1<<i);
		}
		else{
			i--;
		}
	}
	return (int)result*sign;
}
int main(){
	cout<<(5,2)<<endl;
	return 0;
}
