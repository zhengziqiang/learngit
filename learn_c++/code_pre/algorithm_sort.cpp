/*==============================================================================
    > File Name: algorithm_sort.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月14日 星期三 00时05分15秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
bool is_great(int a,int b){
	return a>b;
}
int main(){
	vector <int> vec;
	vec.push_back(3);
	vec.push_back(2);
	vec.push_back(5);
	vec.push_back(1);
	vec.push_back(7);
	sort(vec.begin(),vec.end(),is_great);//这是反序输出
	vector <int>::iterator iter;
	for(iter=vec.begin();iter!=vec.end();iter++){
		cout<<*iter<<endl;
	}
	return 0;
}
