/*==============================================================================
    > File Name: map_find_many.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月10日 星期六 14时44分19秒
 ==========================================================================*/

#include<iostream>
#include<map>
using namespace std;
int main(){
	map<int,int> a;
	int m=0;
	for(int i=0;i<3;i++)
		a.insert(pair<int,int>(1,i));
	map<int,int>::iterator iter;
//	a.erase(1);//erase()会将全部索引为1的都删掉
	if(a.empty())
		cout<<"the map is empty"<<endl;
	iter=a.find(1);
	cout<<iter->second<<endl;
//	while(iter!=a.end()){
//		iter=a.find(1);
//		m+=iter->second;
//		a.erase(1);
//	}
	cout<<m<<endl;
//	for(iter=a.begin();iter!=a.end();iter++){

//	}
	
	return 0;
}
