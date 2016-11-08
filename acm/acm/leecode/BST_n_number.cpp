/*==============================================================================
    > File Name: BST_n_number.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月28日 星期三 15时10分00秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include "tree.h"
using namespace std;
class solution{
	public:
		//动态方程是
		//dp[i]=sum(dp[k]*dp[i-k-1])
		int num_tree(int n){
			vector <int> dp(n+1,0);
			dp[0]=1;
			dp[1]=1;
			for(int i=2;i<=n;i++){
				for(int j=0;j<i;j++){
					dp[i]+=dp[j]*dp[i-j-1];
				}
			}
		return dp[n];
		}
		vector <TreeNode * > generate_trees(int n){
			return generate(1,n);
		}
		vector <TreeNode *> generate(int start,int end){
			vector <TreeNode *> vs;
			if(start>end){
				vs.push_back(NULL);
				return vs;
			}
			for(int i=start;i<=end;i++){
				auto l=generate(start,i-1);
				auto r=generate(i+1,end);
				for(int j=0;j<l.size();j++){
					for(int k=0;k<r.size();k++){
						TreeNode * n=new TreeNode(i);
						n->left=l[j];
						n->right=r[k];
						vs.push_back(n);
					}
				}
			}
			return vs;
		}
};
int main(){
	solution s1;
	return 0;
}
