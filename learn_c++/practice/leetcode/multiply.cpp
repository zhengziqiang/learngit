/*==============================================================================
    > File Name: multiply.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年03月29日 星期三 14时24分48秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
string multiply(string &num,char ch){
	int n=ch-'0';//强制转换成一个int型的数
	string s;
	int carry=0;
	int x;
	for(int i=num.size()-1;i>=0;i--){
		x=(num[i]-'0')*n+carry;
		carry=x/10;
		s.insert(s.begin(),x%10+'0');

	}
	if(carry>0)
		s.insert(s.begin(),carry+'0');
	return s;
}
