/*==============================================================================
    > File Name: multimap.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月11日 星期日 18时14分45秒
 ==========================================================================*/

#include<iostream>
#include<map>
using namespace std;
int main(){
	map <int , int> ma;
	ma.insert(pair<int ,int >(1,2));
	ma.insert(pair<int ,int >(1,3));
	//map的默认操作是不承认俩个相同的key值的,所以第二个没有插入成功
	for(map<int ,int>::iterator i=ma.begin();i!=ma.end();i++)
		cout<<i->first<<" "<<i->second<<endl;
	map<int ,int>::iterator i;
	i=ma.end();//end值为0;
	cout<<i->first<<" "<<i->second<<endl;
	cout<<"测试multimap的功能"<<endl;
	multimap <int ,int>mul;
	mul.insert(pair<int ,int>(1,2));
	mul.insert(pair<int ,int>(1,3));
	for(map<int ,int>::iterator j=mul.begin();j!=mul.end();j++)//测试成功,果然multimap可以插入相同键值相同的pair,而且map和multimap的迭代器可以互相混用
		cout<<j->first<<" "<<j->second<<endl;
	return 0;
}
