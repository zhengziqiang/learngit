/*==============================================================================
    > File Name: candy.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月29日 星期四 20时45分51秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
class solution{
	public:
		int candy(vector <int> &ratings){
			vector <int> candys;
			candys.resize(ratings.size(),1);
			for(int i=1;i<ratings.size();i++){
				if(ratings[i]>ratings[i-1]){
					candys[i]=candys[i-1]+1;
				}
			}
			for(int i=ratings.size()-2;i>=0;i--){
				if(ratings[i]>ratings[i+1]&&candys[i]<=candys[i+1]){
					candys[i]=candys[i+1]+1;
				}
			}
			int n=0;
			for(int i=0;i<candys.size();i++){
				n+=candys[i];
			}
			return n;
		}
};
int main(){
	return 0;
}
