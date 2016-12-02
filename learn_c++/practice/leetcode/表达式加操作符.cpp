/*==============================================================================
    > File Name: 表达式加操作符.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月21日 星期一 13时44分29秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<string>
using namespace std;
//DFS算法
void helper(const string &num,const int target,
		vector <string> &result,
		string solution,
		int idx,
		long long val,
		long long prev,
		char preop){
	if(target==val&&idx==num.size()){
		result.push_back(solution);
		return ;//递归出口
	}
	if(idx==num.size())
		return ;
	string n;
	long long v=0;
	for(int i=idx;i<num.size();i++){

	}
}
vector <string> add_operator(string num,int target){
	vector <string>	result;
	if(num.size()==0)
		return result;
	helper(num,target,result,"",0,0,0,' ');
}
