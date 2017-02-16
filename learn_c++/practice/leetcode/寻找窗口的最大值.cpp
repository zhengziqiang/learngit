/*==============================================================================
    > File Name: 寻找窗口的最大值.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年02月16日 星期四 11时19分25秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<set>
using namespace std;
vector <int> max_num(vector <int> num,int k){
	vector <int> res;
	multiset<int> m;
	for(int i=0;i<num.size();i++){
		if(i>=k){
			w.erase(w.find(num[i-k]));
		}
		w.insert(num[i]);
		if(i>=k-1){
			res.push_back(*w.rbegin());//插入最大值
		}
	}
	return res;
}
