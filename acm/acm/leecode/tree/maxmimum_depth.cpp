/*==============================================================================
    > File Name: maxmimum_depth.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月29日 星期四 15时49分41秒
 ==========================================================================*/

#include<iostream>
#include<algorithm>
#include<TREENODE>
using namespace std;
class solution{
	public:
		int num;
		int max_depth(TreeNode *root){
			if(!root){
				return 0;
			}
			
			num=numeric_limits<int>::min();
			travel(root,1);
			return num;
		}
		void travel(TreeNode *node,int level){
			if(!node->left&&!node->right){
				num=max(num,level);
				return ;
			}
			if(node->left){
				travel(node->left,level+1);

			}
			if(node->right){
				travel(node->right,level+1);
			}
		}

		int min_depth(TreeNode *root){
			if(!root){
				return 0;
			}
			n=numeric_limits<int>::max();
			int d=1;
			depth(root,d);
			return n;
		}
		void depth(TreeNode *node,int &d){
			if(!node->left&&!node->right){
				n=min(n,d);
				return ;
			}
			if(node->left){
				d++;
				depth(node->left,d);
				d--;
			}
			if(node->right){
				d++;
				depth(node->right,d);
				d--;
			}
		}
};
int main(){

}
