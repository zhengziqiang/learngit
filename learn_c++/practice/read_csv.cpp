/*==============================================================================
    > File Name: read_csv.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年03月17日 星期五 16时24分20秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>
#include<stdlib.h>
using namespace std;
const int MAX=23;
int read_data(int &row,int &col,vector <vector <int> > &data,string filename){
    ifstream ifile("/home/zzq/demo.csv");
    string line;
    row=0;
    col=0;
    vector <string> ans;
    while(getline(ifile,line)){
        istringstream sin(line);
        string field;
        while(getline(sin,field,',')){
            ans.push_back(field);
        }
        for(int i=0;i<ans.size();i++){
            col+=1;
            if(ans[i]==""){
                data[row].push_back(MAX);
            }
            else{
                int m=atoi(ans[i].c_str());
                data[row].push_back(m);
            }
        }
		ans.clear();
		row+=1;
    }
	col/=row;
    ifile.close();
    return 0;
}
int main(){
	vector <vector <int> > data;
	int m,n;
	string filename="/home/zzq/demo.csv";
	read_data(m,n,data,filename);
	cout<<"initial finished"<<endl;
	cout<<data.size()<<" "<<data[0].size()<<endl;
	return 0;
}
