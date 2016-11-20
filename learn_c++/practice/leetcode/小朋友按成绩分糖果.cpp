/*==============================================================================
    > File Name: 小朋友按成绩分糖果.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月18日 星期五 23时06分39秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
int print(vector <int> candy){
	int n=candy.size();
	for(int i=0;i<n;i++){
		cout<<candy[i]<<" ";
	}
	cout<<endl;
	return 0;
}
int candy(vector <int> &ratings){
	vector <int> candycnt(ratings.size());
	candycnt[0]=1;
	for(int i=1;i<ratings.size();i++){
		candycnt[i]=ratings[i]>ratings[i-1]?candycnt[i-1]+1:1;//加1操作

	}
	print(candycnt);
	int total=candycnt[ratings.size()-1];
	for(int i=ratings.size()-2;i>=0;i--){
		candycnt[i]=(ratings[i]>ratings[i+1]&&candycnt[i+1]+1>candycnt[i])?candycnt[i+1]+1:candycnt[i+1];//这个过程要从最后一个节点开始进行操作
		total+=candycnt[i];
	}
	return total;
}
int main(){
	return 0;
}
