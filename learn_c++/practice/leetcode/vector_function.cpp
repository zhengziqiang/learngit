/*==============================================================================
    > File Name: vector_function.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年03月15日 星期三 20时09分44秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct interval{
	int x;
	int y;
	interval():x(0),y(0){

	}
	interval(int s,int e):x(s),y(e){

	}
	//struct 也可以类似于class那样初始化
};
bool compare(interval v1,interval v2){
	return v1.x<v2.x;
}
int main(){
	vector <interval> ins;
	interval v1(3,4);
	interval v2(4,5);
	interval v3(5,5);
	ins.push_back(v1);
	ins.push_back(v3);
	ins.push_back(v2);
	sort(ins.begin(),ins.end(),compare);
	cout<<ins[2].x<<endl;//可以达到排序的作用
	return 0;
}
