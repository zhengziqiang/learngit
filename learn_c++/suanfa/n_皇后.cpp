/*==============================================================================
    > File Name: n_皇后.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月07日 星期一 17时13分29秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<math.h>
#include<stdlib.h>
using namespace std;
int col[4];
int n=4;
bool promising(int i){
	int k;
	k=1;
	bool switch_use;
	switch_use=true;
	while(k<i&&switch_use){
		if(col[i]==col[k]||abs(col[i]-col[k])==i-k){
			switch_use=false;
		}
		k++;
	}
	return switch_use;
}
void queens(int i){
	int j;
	if(promising(i)){
		if(i==n){
			for(int k=0;k<n;k++){
				cout<<col[k]<<" ";
			}
			cout<<endl;
		}
		else{
			for(j=1;j<=n;j++){
				col[i+1]=j;
				queens(i+1);
			}
		}
	}
}
int main(){
	int n;
	cout<<"please input the number of queens"<<endl;
	cin>>n;
	queens(n);
	return 0;
}
