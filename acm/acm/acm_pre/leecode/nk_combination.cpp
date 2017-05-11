/*==============================================================================
    > File Name: nk_combination.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月28日 星期三 20时51分16秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class solution{
	public:
	int combine(int n,int k){
		vector <vector <int> > ret;
		if(n<=0)
			return 0;
		vector <int> curr;
		DFS(ret,curr,n,k,1);
		return ret.size();
	}
	void DFS(vector <vector <int> > &ret,vector <int> curr,int n,int k,int level){
		if(curr.size()==k){
			ret.push_back(curr);
			return ;
		}
		if(curr.size()>k){
			return ;
		}
		for(int i=level;i<=n;++i){
			curr.push_back(i);
			DFS(ret,curr,n,k,i+1);
			curr.pop_back();
		}
	}


	//
	//
	vector <vector <int> > combination_sum(vector <int> &candidates,int target){
		vector <vector <int> > ret;
		if(candidates.size()==0||target<0)
			return ret;
		vector <int> curr;
		sort(candidates.begin(),candidates.end());
		back_tracking(ret,curr,candidates,target,0);
		return ret;
	}
	void back_tracking(vector <vector <int> > &ret,vector <int> curr,vector <int> candidates,int target,int level){
		if(target==0){
			ret.push_back(curr);
			return ;
		}
		else if(target<0){
			return ;
		}
		for(int i=level;i<candidates.size();++i){
			target-=candidates[i];
			back_tracking(ret,curr,candidates,target,i);
			curr.pop_back();
			target+=candidates[i];
		}
	}
	//
	//
	vector <vector <int> > combination_sum2(vector <int> &num,int target){
		vector <vector <int> > ret;
		if(num.size()==0||target <0){
			return ret;
		}
		vector <int> curr;
		sort(num.begin(),num.end());
		back_tracking2(ret,curr,num,target,0);
		return ret;

	}
	void back_tracking2(vector <vector <int> > &ret,vector <int> curr,vector <int> num,int target,int level){
		if(target==0){
			ret.push_back(curr);
			return ;

		}
		else if(target<0){
			return ;
		}
		for(int i=level;i<num.size();++i){
			target -=num[i];
			curr.push_back(num[i]);
			back_tracking2(ret,curr,num,target,i+1);
			curr.pop_back();
			target +=num[i];
			while(i<num.size()-1&& num[i]==num[i+1])
				++i;
		}
	}
};
int main(){
	solution s1;
	cout<<s1.combine(3,2)<<endl;
	return 0;
}
