/*==============================================================================
    > File Name: 修建工程.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月23日 星期五 11时34分55秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;

int main(){
	int N;
	vector <int> ans;
	int n_lines;
	int *no_1;
	int *no_2;
	int *money;
	int *state;
	while(cin>>N){
		if(N==0)
			break;
		n_lines=(N*(N-1))/2;
		no_1=new int[n_lines];
		no_2=new int[n_lines];
		money=new int[n_lines];
		state=new int[n_lines];
		for(int i=0;i<N;i++){
			cin>>no_1[i]>>no_2[i]>>money[i]>>state[i];
		}

		free(no_1);
		free(no_2);
		free(money);
		free(state);
	}
}
