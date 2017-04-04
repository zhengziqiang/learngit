/*==============================================================================
    > File Name: move_zeroes.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年03月29日 星期三 13时50分32秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
void move(vector <int> &num,int n){
	int	i=0,pos=0;
	cout<<"fun"<<endl;
	for(i=0;pos<n&&i<n;i++){
		while(num[pos]==0)//如果现在的位置不为0 一定要保证这里的数是pos
			pos++;
		if(pos<n){
			num[i]=num[pos];
		}else{
			i--;//move the position
		}
		pos++;
	}
	for(;i<n;i++){
		num[i]=0;
	}
	cout<<"finished fun"<<endl;
}

int main(){
	vector <int> num;
	num.push_back(0);
	num.push_back(2);
	num.push_back(0);
	num.push_back(1);
	num.push_back(2);
	num.push_back(0);
	move(num,6);
	for(int i=0;i<num.size();i++){
		cout<<num[i]<<endl;
	}
	return 0;
}
