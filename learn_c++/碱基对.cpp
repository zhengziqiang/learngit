/*************************************************************************
 > File Name: 碱基对.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年05月05日 星期四 22时37分09秒
 ************************************************************************/

#include<iostream>
#include<string>
using namespace std;
int main(){
	int m;
	cin>>m;
	string str[m];
	for(int i=0;i<m;i++){
		cin>>str[i];
	}
	for(int j=0;j<m;j++){
		int p=str[j].length();
		char strn[p];
		for(int k=0;k<p;k++){
			if(str[j][k]=='A')strn[k]='T';
			if(str[j][k]=='G')strn[k]='C';
			if(str[j][k]=='C')strn[k]='G';
			if(str[j][k]=='T')strn[k]='A';

		}
		for(int l=0;l<p;l++)
		cout<<strn[l];
		cout<<endl;
	}
	return 0;
}
