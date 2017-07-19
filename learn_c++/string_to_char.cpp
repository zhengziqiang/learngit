/*==============================================================================
    > File Name: string_to_char.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年05月18日 星期四 19时43分37秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<string>
#include<stdio.h>
using namespace std;
int main(){
	string str="/home/zzq/learngit/learn_c++/hello";
	const char *ptr=str.c_str();
	remove(ptr);
	return 0;
}
