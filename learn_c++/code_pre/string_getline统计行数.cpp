/*==============================================================================
    > File Name: string_getline统计行数.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月12日 星期一 16时25分29秒
 ==========================================================================*/

#include<iostream>
#include<string>
#include<fstream>
using namespace std;
int main(){
//	FILE *fp;
//	fp=fopen("hehe","r");
//	fclose(fp);
	int count=0;
	string str;
	ifstream fin("data");
	//ifstream fin;
	//fin.open("hehe");
	while(getline(fin,str)){
		cout<<str<<endl;
		count++;
	}
	cout<<count<<endl;
	return 0;
}
