/*==============================================================================
    > File Name: 必修课依赖关系.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月20日 星期日 19时07分21秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<map>
using namespace std;
bool has_cycle(int n,vector <int> &explored,vector <int> &path,map <int,vector <int> > &graph){
	for(int i=0;i<graph[n].size();i++){
		if(path[graph[n][i]])
			return true;
		path[graph[n][i]]=true;
		if(has_cycle(graph[n][i],explored,path,graph)){
			return true;
		}
		path[graph[n][i]]=false;
	}
	explored[n]=true;
	return false;
}
bool canfinish(int num,vector <pair<int,int > > &prerequites){
	map<int,vector <int> > graph;
	for(int i=0;i<prerequites.size();i++){
		graph[prerequites[i].first].push_back(prerequites[i].second);

	}
	vector <int> explored(num,false);
	vector <int> path(num,false);
	for(int i=0;i<num;i++){
		if(explored[i])
			continue;
		if(has_cycle(i,explored,path,graph))
			return false;
	}
	return true;
}
int main(){
	return 0;
}
