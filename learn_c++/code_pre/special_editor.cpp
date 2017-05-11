/*==============================================================================
    > File Name: special_editor.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月10日 星期六 16时50分55秒
 ==========================================================================*/

#include<iostream>
#include<string>
using namespace std;
void rfun(string &str,int m,int n){
	m-=1;
	n-=1;
	char tmp;
	tmp=str[m];
	str[m]=str[n];
	str[n]=tmp;
}
void sfun(string &str,int m){
	m-=1;
	str[m]+=1;
	if(str[m]==123)
		str[m]=97;
	if(str[m]==91)
		str[m]=65;
}
void qfun(string str,int m){
	m-=1;
	cout<<str[m]<<endl;
}
int main(){
	int T;
	cin>>T;
	char cmd;
	int t1,t2;
	int lenth,m;
	for(int i=0;i<T;i++){
		cin>>lenth>>m;
		string str;
		cin>>str;
		for(int j=0;j<m;j++){
			cin>>cmd;
			switch(cmd){
				case 'R':
					cin>>t1>>t2;
					rfun(str,t1,t2);
					break;
				case 'S':
					cin>>t1;
					sfun(str,t1);
					break;
				case 'Q':
					cin>>t1;
					qfun(str,t1);
					break;
				defaut:
					break;

			}
		}
		str='\0';
	}
	return 0;
}
