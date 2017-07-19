/*==============================================================================
    > File Name: matmul.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年03月27日 星期一 21时09分42秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
vector <vector <double> > matmul(vector <vector <double> > m,vector <vector <double > > n){
	vector <vector <double> > ans;
	for(int i=0;i<m.size();i++){
		for(int j=0;j<n[0].size();j++){
			double tmp=0;
			for(int k=0;k<m[0].size();k++){
				tmp+=(m[i][k]*n[k][j]);
			}
			ans[i][j]=tmp;
		}
	}
	return ans;
}
vector <vector <double> > traverse(vector <vector <double> > &m){
	int hang=m.size();
	vector <vector <double> > ans;
	vector <vector <double> > diag(hang,vector <double>(hang,0));
	for(int i=0;i<hang;i++){
		diag[i][i]=1;
	}
	for(int i=0;i<m.size();i++){
		if(m[i][0]==0)
			return ans;
	}
}
int main(){
	return 0;
}
