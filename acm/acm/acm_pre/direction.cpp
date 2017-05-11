/*==============================================================================
    > File Name: direction.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月10日 星期六 20时38分28秒
 ==========================================================================*/

#include<iostream>
using namespace std;
int main(){
	string str;
	string first;
	string second;
	cin>>str;
	cin>>first;
	cin>>second;
	int str_n=str.length();
	int first_n=first.length();
	int second_n=second.length();
	bool forward=false;
	bool backward=false;
	for(int i=0;i<str_n+1-first_n;i++){
		for(int j=0;j<first_n;j++){
			if(str[i+j]!=fist[j])
				forward=false;
		}
	}
	for(int i=0;i<str_n+1-second_n;i++){
		for(int j=0;j<second_n;j++){
			if(str[i+j]!=second[j])
				forward=false;
		}
	}
	for(int i=str_n-1;i>first_n-2;i--){
		for(int j=first_n-1;j>=0;j--){
			if(str[i-j]!=
		}
	}
}
