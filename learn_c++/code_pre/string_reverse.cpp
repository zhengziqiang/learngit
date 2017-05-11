/*==============================================================================
    > File Name: string_reverse.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月10日 星期六 15时57分38秒
 ==========================================================================*/

#include<iostream>
#include<string>
using namespace std;
void fun(string *str,int m){
	string *head=str;
	string *end=str+m-1;
	string ch;
	while(head<end){
		ch=*end;
		*end=*head;
		*head=ch;
		head++;
		end--;
	}
	cout<<"reverse success"<<endl;
	for(int i=0;i++){
		cout<<str[i];
	}
}
int main(){
	string str;
	cin>>str;
	int m=str.length();
	fun(&str,m);
	cout<<str<<endl;
	return 0;
}


