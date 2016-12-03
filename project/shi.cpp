/*==============================================================================
    > File Name: shi.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月28日 星期一 19时37分24秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
vector < vector <double> > data_transform(int m,int n,vector <double> data){
	n/=2;
	vector <vector <double> > new_data(m,vector<double>(n,0));
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			new_data[i][j]=data[i*m+2*j]*10000+data[i*m+2*j+1];
		}
	}
	return new_data;
}
int main(){
	vector <vector <double> > new_data;
	vector <double> data(12,1);
	new_data=data_transform(3,4,data);
	for(int i=0;i<3;i++){
		for(int j=0;j<2;j++){
			cout<<new_data[i][j]<<endl;
		}
	}
	return 0;
}
