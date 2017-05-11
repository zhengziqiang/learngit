/*==============================================================================
    > File Name: 矩阵相乘.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月25日 星期日 22时51分39秒
 ==========================================================================*/

#include<iostream>
#include<time.h>
#include<stdlib.h>
using namespace std;
int get_rng(){
	int a=(int)rand()%10;
	return a;
}
int main(){
	int m,n,k;
	cout<<"please input the row and column of the matrix"<<endl;
	cin>>m>>n;
	cout<<"please input the row and column of the seconde matrix,and the column of the first matrix and the row of the second matrix must be equal"<<endl;
	cin>>n>>k;
	int **mat1;
	int **mat2;
	mat1=new int*[m];
	for(int i=0;i<m;i++){
		mat1[i]=new int[n];
		for(int j=0;j<n;j++){
			mat1[i][j]=get_rng();
		}
	}
	mat2=new int*[n];
	for(int i=0;i<n;i++){
		mat2[i]=new int [k];
		for(int j=0;j<k;j++){
			mat2[i][j]=get_rng();
		}
	}
	int sum;
	int **ans;
	ans=new int*[m];
	for(int i=0;i<m;i++){
		ans[i]=new int[k];
	}
	for(int i=0;i<m;i++){
		for(int j=0;j<k;j++){
			sum=0;
			for(int k=0;k<n;k++){
				sum+=mat1[i][k]*mat2[k][j];
			}
		ans[i][j]=sum;
		}
	}
	return 0;
}

