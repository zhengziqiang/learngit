/*==============================================================================
    > File Name: summary连续问题.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年02月15日 星期三 10时09分03秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<sstream>
using namespace std;
string make_range(int start,int end){
	ostringstream oss;
	if(start!=end){
		oss<<start<<"->"<<end;
	}else{
		oss<<start;
	}
	return oss.str();
}
vector <string> sum_ranges(vector <int> num){
	int start=num[0],end=num[0];
	vector <string> res;
	int len=num.size();
	for(int i=1;i<len;i++){
		if(num[i]=end+1){
			end=num[i];
			continue;
		}
		//if not
		res.push_back(make_range(start,end));
		start=end=num[i];
	}
	return res;
}

int main(){
	return 0;
}
