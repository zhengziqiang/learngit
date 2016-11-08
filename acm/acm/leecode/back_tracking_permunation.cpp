/*==============================================================================
    > File Name: back_tracking_permunation.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月29日 星期四 14时51分05秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
class solution{
	public:
		vector <vector <int> > permute(vector <int> &num){
			vector <vector <int> > permutations;
			if(num.size()==0)
				return permutations;
			vector <int> curr;
			vector <bool> isvisited(num.size(),false);
			back_tracking(permutations,curr,isvisited,num);
			return permutations;
		}
		void back_tracking(vector <vector <int> > &ret,vector <int> curr,vector <bool> isvisited,vector <int> num){
			if(curr.size()==num.size()){
				ret.push_back(curr);
				return ;
			}
			for(int i=0;i<num.size();++i){
				if(isvisited[i]==false){
					isvisited[i]=true;
					curr.push_back(num[i]);
					back_tracking(ret,curr,isvisited,num);
					curr.pop_back();
				}
			}
		}
};
int main(){

}
