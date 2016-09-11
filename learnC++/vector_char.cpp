/*==============================================================================
    > File Name: vector_char.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月11日 星期日 19时28分46秒
 ==========================================================================*/

#include<iostream>
#include<string>
#include<vector>
using namespace std;
int main(){
	vector <char> ch;
	char tmp;
	string str("zhengziqiang");
	for(int i=str.length()-1;i>=0;i--){
		ch.push_back(str[i]);
	}
	vector<char>::iterator iter;
	for(iter=ch.begin();iter!=ch.end();iter++)
		cout<<*iter<<endl;
	return 0;
}
