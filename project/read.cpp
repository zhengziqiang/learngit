/*==============================================================================
    > File Name: read.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月26日 星期六 11时15分13秒
 ==========================================================================*/

#include<iostream>
#include<stdio.h>
#include<vector>
#include<fstream>
using namespace std;
int main(){
//	ifstream ifile("cs.txt");
//	int a[100];
//	for(int i=0;i<10;i++){
//		ifile>>a[i];
//	}
//	for(int i=0;i<10;i++){
//		cout<<a[i]<<endl;
//	}
//	ifile.close();
	FILE *out;
	out=fopen("a.csv","r");
	int b[2];
	char tmp;

	fscanf(out,"%d",&b[0]);
	cin>>tmp;
	fscanf(out,"%d",&b[1]);
	for(int i=0;i<2;i++){
		cout<<b[i]<<endl;
	}
	fclose(out);
	return 0;
}
