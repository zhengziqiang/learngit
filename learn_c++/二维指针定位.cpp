/*==============================================================================
    > File Name: 二维指针定位.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年05月26日 星期五 14时35分59秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
double print_weight(double *wei,int n){
	for(int i=0;i<n;i++){
		cout<<*wei<<endl;
		wei++;
	}
	return 0;
}
int main(){
	double **weight;
	weight=new double*[5];
	for(int i=0;i<5;i++){
		weight[i]=new double[5];
		for(int j=0;j<5;j++){
			weight[i][j]=i*5+j;
		}
	}
	double *ptr;
	ptr=&weight[2][0];
	print_weight(ptr,5);
	return 0;
}
