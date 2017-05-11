/*==============================================================================
    > File Name: vector_new.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月04日 星期日 14时57分54秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
int main(){
	vector <int> *a;
	a=new vector<int>[3];
	vector<int>::iterator g;
	for(g=a.begin();g!=a.end();g++)
		cout<<g<<endl;
	delete []a;
	return 0;
}
