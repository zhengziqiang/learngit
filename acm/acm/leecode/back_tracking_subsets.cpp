/*==============================================================================
    > File Name: backtracking_sort.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月29日 星期四 14时21分13秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class solution{
	public:
		vector <vector <int> > res;
		vector <vector <int> > subsets(vector <int> &s){
			if(s.empty()){
				return res;
			}
			sort(s.begin(),s.end());
			res.push_back(vector <int>());
			vector <int> v;
			generate(0,v,s);
			return res;
		}
		void generate(int start,vector <int> &v,vector <int> &s){
			if(start==s.size()){
				return ;
			}
			for(int i=start;i<s.size();i++){
				v.push_back(s[i]);
				res.push_back(v);
				generate(i+1,v,s);
				v.pop_back();
			}
		}


		vector <vector <int> > subsets_with_dup(vector <int> &s){
			if(s.empty()){
				return res;
			}
			sort(s.begin(),s.end());
			res.push_back(vector <int> ());
			vector<int> v;
			generate2(0,v,s);
			return res;

		}
		void generate2(int start,vector <int> &v,vector <int>&s){
			if(start==s.size()){
				return ;
			}
			for(int i=start;i<s.size();i++){
				v.push_back(s[i]);
				res.push_back(v);
				generate(i+1,v,s);
				v.pop_back();
				while(i<s.size()-1&&s[i]==s[i+1]){
					i++;
				}
			}
		}
};
int main(){
	solution s1;
	vector <int> s;
	for(int i=0;i<3;i++)
		s.push_back(i+1);
	s1.subsets(s);
	for(int i=0;i<s1.res.size();i++){
		for(int j=0;j<s1.res[i].size();j++){
			cout<<s1.res[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;

}
