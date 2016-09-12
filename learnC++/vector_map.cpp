/*==============================================================================
    > File Name: vector_map.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月12日 星期一 16时07分37秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<map>
using namespace std;
int main(){
	vector < map<int,int> > net;
	map<int ,int> ma;
	ma[1]=2;
	ma[2]=3;
	net.push_back(ma);
	map<int ,int > ma2;
	ma2[4]=5;
	ma2[5]=6;
	net.push_back(ma2);
	map<int ,int>::iterator iter;
	for(iter=net[1].begin();iter!=net[1].end();iter++)
		cout<<iter->first<<"  "<<iter->second<<endl;
	return 0;
}
