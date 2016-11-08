/*==============================================================================
    > File Name: 度度熊翻转实验.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月23日 星期五 15时53分37秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<map>
#include<multimap>
using namespace std;
void char_reverse(char c){
	if(c=='B')
		c=='W';
	else
		if(c=='W')
			c=='B';
}
void reverse(char **net,int m,int n,int height,int wide){
	m-=1;
	n-=1;
	char_reverse(&net[m][n]);
	if(m+1<height)
		char_reverse(&net[m+1][n]);
	if(m-1>0)
		char_reverse(&net[m-1][n]);
	if(n+1<wide)
		char_reverse(&net[m][n+1]);
	if(n-1>0)
		char_reverse(&net[m][n-1]);
}
int fun(char **net,multimap <int,int> &broken){
	
}
int main(){
	int T;
	cin>>T;
	int m,n,k;
	char **net;
	multimap <int,int> broken;
	int row,col;
	for(int i=0;i<T;i++){
		cin>>n>>m>>k;
		net=new *char[n];
		for(int j=0;j<n;j++){
			net[i]=new char[m];
			for(int k=0;k<m;k++){
				cin>>net[j][k];
			}
		}
		for(int i=0;i<k;i++){
			cin>>row>>col;
			broken[row]=col;
		}

	}
}
