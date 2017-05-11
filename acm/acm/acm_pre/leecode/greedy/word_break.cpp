/*==============================================================================
    > File Name: word_break.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月29日 星期四 20时55分57秒
 ==========================================================================*/

#include<iostream>
#include<unordered_set>
#include<string>
#include<vector>
using namespace std;
class solution{
	public:
		bool world_break(string s,unordered_set<string> &dict){
			int len=(int)s.size();
			vector <bool> dp(len+1,false);
			dp[0]=true;
			for(int i=1;i<=len;i++){
				for(int j=i-1;j>=0;j--){
					if(dp[j]&&dict.find(s.substr(j,i-j))!=dict.end()){
						dp[i]=true;
						breaK;
					}
				}
			}
			return dp[len];
		}


		vector <vector <char> > dp;
		vector <string>vals;
		string val;
		vector <string> world_break(string s,unordered_set<string>&dict){
			int len=s.size();
			dp.resize(len);
			for(int i=0;i<len;i++){
				dp[i].resize(len+1,0);
			}
			for(int i=1;i<=len;i++){
				for(int j=0;j<len-i+1;j++){
					if(dict.find(s.substr(j,i))!=dict.end()){
						dp[j][i]=1;
						continue;
					}
					for(int k=1;k<i&&k<len-j;k++){
						if(dp[j][k]&& dp[j+k][i-k]){
							dp[j][i]=2;
							break;
						}
					}
				}
			}
			if(dp[0][len]==0){
				return vals;
			}
		}
		void dfs(const string &s,int start){
			int len=s.size();
			if(start==len){
				vals.push_back(val);
				return ;
			}
			for(int i=1;i<=len-start;i++){
				if(dp[start][i]==1){
						int oldlen=val.size();
						if(oldlen!=0){
						val.append(" ");
						}
						val.append(s.substr(start,i));
						dfs(s,start+1);
						val.erase(oldlen,string::npos);
						}
			}
		}

};
int main(){
	return 0;

}
