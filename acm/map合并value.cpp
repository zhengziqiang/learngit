/*==============================================================================
    > File Name: map合并value.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月10日 星期六 14时25分07秒
 ==========================================================================*/

#include<iostream>
#include<map>
using namespace std;
int main(){
	map<int,int> m;
	int a,b;
	map<int,int>::iterator m_iter;
	for(int i=0;i<3;i++){
		cin>>a>>b;
		m.insert(pair<int,int>(a,b));
	}
	int tmp1;
	int tmp2;
	for(m_iter=m.begin();m_iter!=m.end();m_iter++){
		
	}
	for(m_iter=m.begin();m_iter!=m.end();m_iter++){
		cout<<m_iter->first<<" "<<m_iter->second<<endl;
		
	}
	//map的简单插入和计算
	//map<int ,int>map1
	//这里的[]操作如果key值不存在,则新建一个这样的pair对,如果已经存在,就更新value值
	//while(cin>>key>>value){
	//	map1[key]=value;
	//}
	//map的简单循环
	//for(iterator i=map1.begin();i!=map1.end();i++){
	//	cout<<i->first<<" "<<i->second<<endl;
	//}
	return 0;
}
