/*==============================================================================
    > File Name: triangle_minmum_path.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月28日 星期三 14时31分50秒
 ==========================================================================*/

#include<iostream>
#include<limits.h>
#include<vector>
using namespace std;
class solution{
	//动态方程如下
	//这里应该是从三角形的上面到下面计算,from top to bottom
	//dp[m+1][n]= min(dp[m][n],dp[m][n-1])+triangle[m+1][n] if(n>0)
	//dp[m+1][0]=dp[m][0]+triangle[m+1][0]
	//从后向前计算
	public:
		int minimum_total(vector <vector <int> > &triangle){
			int row = triangle.size();
			if(row==0){
				return 0;
			}
			vector <int> total (row,INT_MAX);//初始化为最大值,每一行都有一个最大值
			total[0]=triangle[0][0];
			int mintotal=INT_MAX;
			for(int i=1;i<row;i++){
				for(int j=i;i>=0;j--){
					if(j==0){
						total[j]+=triangle[i][j];
					}
					else{
						total[j]=min(total[j-1],total[j])+ triangle[i][j];
						//上一层total[i]为INT_MAX,不会影响最小值
					}

				}
			}
			for(int i=0;i<row;i++){
				mintotal=min(mintotal,total[i]);
			}
			return mintotal;
		}
		//
		//from bottom to top
		//动态方程为
		//dp[m][n]=min(dp[m+1][n],dp[m+1][n+1])+ triangle[m][n];
		int minimum_total_bt(vector <vector <int> > &triangle){
			if(triangle.empty()){
				return 0;
			}
			int row=triangle.size();
			vector <int> dp;
			dp.resize(row);
			for(int i=0;i<dp.size();i++){
				dp[i]=triangle[row-1][i];
			}
			for (int i=row-2;i>=0;i--){
				for(int j=0;j<=1;j++){
					dp[j]=triangle[i][j]+min(dp[j],dp[j+1]);
				}
			}
			return dp[0];
		}
};
int main(){
	vector <vector <int> > triangle;
	int n;
	cout<<"please input the row of the triangle"<<endl;
	cin>>n;
	int tmp;
	cout<<"debug"<<endl;
	for(int i=0;i<n;i++){
		vector <int> pa(n+1,0);
		triangle[i]=pa;
		for(int j=0;j<=i;j++){
			cin>>tmp;
			triangle[i][j]=tmp;
		}
	}
	cout<<"debug"<<endl;
	solution s1;
	cout<<s1.minimum_total(triangle)<<endl;
	return 0;
}
