/*************************************************************************
 > File Name: 试探法生成彩票组合.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年05月12日 星期四 16时37分08秒
 ************************************************************************/

#include<iostream>
#include<string>
using namespace std;
#define num 5
#define max 3
int lottery[max];
int num[num];
int fun(int n,int m){
	int i,j;
	for(i=n;i>=m;i--){
		lottery[m-1]=num[i-1];
		if(m>1)fun(i-1,m-1);
		else
		{
			for(j=max-1;j>=0;j--)cout<<setfill(' ')<<setw(3)<<lottery[j];
			cout<<endl;
		}
	}
	return 0;
}
int main(){
	int i,j;
	for(i=0;i<num;i++)num[i]=i+1;
	for(i=0;i<max;i++)lottery[i]=0;
	fun(num,max);
	return 0;
}
