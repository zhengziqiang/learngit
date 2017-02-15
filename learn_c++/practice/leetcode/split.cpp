/*==============================================================================
    > File Name: split.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年02月14日 星期二 16时16分13秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;
vector <string> split(string str,char delimiter){
	vector <string> interval;
	stringstream ss(str);
	string tok;
	while(getline(ss,tok,delimiter)){
		interval.push_back(tok);
	}
	return interval;
}
int main(){
	string str="hello world";
	vector <string> ans=split(str,' ');
	for(int i=0;i<ans.size();i++){
		cout<<ans[i]<<endl;

	}
	return 0;
}
