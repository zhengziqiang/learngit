/*==============================================================================
    > File Name: string_find.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月11日 星期日 18时46分23秒
 ==========================================================================*/

#include<iostream>
#include<string>
using namespace std;
//int main(){
//	string str("zhengziqiang");
//	string	str1="zheng";
//	if(str.find(str1,0))
//		cout<<"Matching success"<<endl;
//	return 0;
//}
//
int main(){
	string str("zhengziqiang");
	int num=0;
	size_t fi=str.find("zi",0);
	while(fi!=str.npos){
		cout<<fi<<" ";
		num++;
		fi=str.find("zi",fi+1);
	}
	if(0==num)
		cout<<"not find"<<endl;
	return 0;
}
