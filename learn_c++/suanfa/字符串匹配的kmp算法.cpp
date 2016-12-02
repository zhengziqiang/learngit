/*==============================================================================
    > File Name: 字符串匹配的kmp算法.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月08日 星期二 21时40分26秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<string>
using namespace std;
int num_same(string str1,string str2){
	int count=0;
	for(int i=0;i<str1.length();i++){
		if(str1[i]==str2[i]){
			count++;
		}
		else{
			count=0;
			return count;
		}
	}
	return count;
}
vector <int> table_str(string str){
	vector <string> pre;
	vector <string> post;
	vector <int> table;
	for(int i=1;i<=str.length()-1;i++){
		string tmp;
		tmp.assign(str,0,i);
		pre.push_back(tmp);
	}
	for(int i=str.length()-1;i>=1;i--){
		string tmp;
		tmp.assign(str,i,str.length());
		post.push_back(tmp);
	}
	int n=str.length()-1;
	for(int i=0;i<n;i++){
		for(int j=n-1;j>=0;j--){
			int count=num_same(pre[i],post[j]);
			table.push_back(count);
		}
	}
	return table;
}
int main(){
	return 0;
}
