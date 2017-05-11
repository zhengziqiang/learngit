/*==============================================================================
    > File Name: stl_string_reverse.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月11日 星期日 20时05分22秒
 ==========================================================================*/

#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
int main(){
	string str("zhengziqiang");
	reverse(str.begin(),str.end());
	cout<<str<<endl;
	return 0;
}

