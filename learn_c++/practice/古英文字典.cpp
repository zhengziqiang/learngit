/*==============================================================================
    > File Name: 古英文字典.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月08日 星期二 20时58分48秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<string>
using namespace std;
bool has_xing(string dir){
	for(int i=0;dir[i]!='\0';i++){
		if(dir[i]=='*')
			return true;
	}
	return false;
}
int fun(string gzs,string dir){
	bool has_xing=false;
	if(has_xing)
		has_xing=true;
	

}
int main(){
	int T;
	cin>>T;
	int n,m;
	vector <vector <int> > ans;
	for(int i=0;i<T;i++){
		vector <string> dir;
		vector <string> gzs;
		cin>>n>>m;
		string tmp;
		for(int j=0;j<n;j++){
			cin>>tmp;
			dir.push_back(tmp);
		}
		for(int j=0;j<m;j++){
			cin>>tmp;
			gzs.push_back(tmp);
		}
		
	}
}
