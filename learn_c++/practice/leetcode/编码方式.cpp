/*==============================================================================
    > File Name: 编码方式.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月20日 星期日 19时42分58秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<string.h>
using namespace std;
int check(char ch){
	return (!is_digit(ch)||ch=='0')?0:1;
}
int check(char ch1,char ch2){
	return (ch1=='1'||(ch1=='2'&&ch2<='6'))?1:0;
}

int num_decoding(string s){
	if(s.size()<=0){
		return 0;
	}
	if(s.size()==1){
		return check(s[0]);
	}
	int *dp=new int[s.size()];
	memset(dp,0,s.size()*sizeof(int));
	dp[0]=
}
