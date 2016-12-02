/*==============================================================================
    > File Name: vector_find.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月28日 星期三 22时17分29秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<algorithm>//find函数在algorithm这个头文件里,必须要加这个头文件
using namespace std;
int main(){
	vector <int> vec;
	for(int i=0;i<25;i++){
		vec.push_back(i);
	}
	vector <int>::iterator iter=std::find(vec.begin(),vec.end(),13);
	if(iter!=vec.end()){
		cout<<distance(vec.begin(),iter)<<endl;
	}
	return 0;
}
