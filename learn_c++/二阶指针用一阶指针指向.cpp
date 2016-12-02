/*==============================================================================
    > File Name: 二阶指针.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月11日 星期日 17时11分31秒
 ==========================================================================*/

#include<iostream>
using namespace std;
void fun(float **weight,int m){
	float *tmp=&weight[m][2];
	*tmp=0;
	tmp++;
	*tmp=0;
}
int main(){
	float **weight;
	weight=new float*[4];
	for(int i=0;i<4;i++){
		weight[i]=new float[5];
		for(int j=0;j<5;j++){
			weight[i][j]=i*5+j;
		}
	}
	fun(weight,2);
	for(int i=0;i<4;i++)
		for(int j=0;j<5;j++)
			cout<<weight[i][j]<<endl;
	return 0;
}
