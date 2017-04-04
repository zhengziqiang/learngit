/*==============================================================================
    > File Name: great_mix.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年04月04日 星期二 17时55分24秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
bool get_sum(vector <int> coke,int cnt,int target){
	for(int i=0;i<coke.size();i++){
		int sub=target-coke[i];
		if(get_sum(coke,cnt-1,sub)&&cnt>1){
			return true;
		}

	}
}
int main(){
	int target;
	int types;
	cin>>target>>types;
	vector <int> coke(types);
	for(int i=0;i<types;i++){
		cin>>coke[i];
	}
	sort(coke.begin(),coke.end());
	if(coke.end()<target){
		cout<<"-1"<<endl;
		return 0;
	}
	int cnt=1;
	while(){
		int sum=target*cnt;
		if(get_sum(coke,cnt))
			break;
		cnt++;
	}
	cout<<cnt<<endl;
	return 0;
}
