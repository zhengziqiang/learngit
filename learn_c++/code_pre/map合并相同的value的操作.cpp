/*==============================================================================
    > File Name: map合并相同的value的操作.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月11日 星期日 18时33分55秒
 ==========================================================================*/

#include<iostream>
#include<map>
using namespace std;
int main(){
	map <int ,int> ma;
	int m;
	int n;
	map<int ,int>::iterator iter;
	while(true){
		cin>>m;
		if(m==0)
			break;
		cin>>n;
		iter=ma.find(m);
		if(iter==ma.end())
			ma[m]=n;
		else{
			iter->second+=n;
		}
	}
	for(map<int ,int>::iterator i=ma.begin();i!=ma.end();i++)
		cout<<i->first<<"  "<<i->second<<endl;
	return 0;
}
