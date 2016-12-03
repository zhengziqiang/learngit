/*==============================================================================
    > File Name: read_csv.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月26日 星期六 16时58分56秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<stdlib.h>
const int INT_MAX=99999;
using namespace std;
int fun(int row,int col,vector <int> &data){
	ifstream ifile("data.csv");
	string line;
	row=0;
	col=0;
	vector <string> ans;
	while(getline(ifile,line)){
		cout<<"原始数据："<<line<<endl;
		istringstream sin(line);
		string field;
		row+=1;
		while(getline(sin,field,',')){
			ans.push_back(field);
		}
	}
	for(int i=0;i<ans.size();i++){
		col+=1;
		if(ans[i]==""){
			data.push_back(INT_MAX);
		}
		else{
			int m=atoi(ans[i].c_str());
			data.push_back(m);
		}
	}
	for(int i=0;i<data.size();i++){
		cout<<data[i]<<endl;
	}
	return 0;	
}
int main(){
	int row=0;
	int col=0;
	vector <int> data;
	fun(row,col,data);
	return 0;
}
