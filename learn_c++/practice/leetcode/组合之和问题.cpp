/*==============================================================================
    > File Name: 组合之和问题.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月19日 星期六 12时12分18秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
void combination_helper(vector <int> &candidates,int start,int target,vector <int> &solution,vector <vector<int> > &result){
	if(target<0){
		return ;
	}
	if(target==0){
		result.push_back(solution);
		return ;
	}
	for(i=start;i<candidates.size();i++){
		if(i>start&&candidates[i]==candidates[i-1])
			continue;
		solution.push_back(candidates[i]);
		combination_helper(candidates,i,target-candidates[i],solution,result);//递归
		solution.pop_back();//更换另一个数，这个操作见过很多次了
	}
}
vector <vector <int> > combination_sum(vector <int > &candidates,int target){
	vector <vector <int> > result;
	if(candidates.size()<=0){
		return result;
	}
	sort(candidates.begin(),candidates.end());
	vector <int> solution;
	combination_helper(candidates,0,target,solution,result);
	return result;
}
int main(){
	return 0;
}
