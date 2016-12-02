/*==============================================================================
    > File Name: vector_vector作为返回值.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月29日 星期四 13时38分13秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
vector <vector <int> > fun(int m,int n){
	vector <vector <int > > ret(m,vector<int>(n,1));
	return ret;
}
int main(){
	int m=3,n=4;
	vector <vector <int > > ret(m,vector<int>(n,1));
	ret=fun(3,4);
	for(int i=0;i<3;i++){
		for(int j=0;j<4;j++){
			cout<<ret[i][j]<<endl;
		}
	}
	return 0;
}
