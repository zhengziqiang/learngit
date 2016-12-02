/*==============================================================================
    > File Name: train_test.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年10月26日 星期三 21时20分35秒
 ==========================================================================*/

#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main(){
	int lines[103];
	ifstream iofile;
	iofile.open("/deep/DataSet/MVCO_103/filelog/number");
	for (int i=0;i<103;i++){
		iofile>>lines[i];
	}
	iofile.close();
	for(int i=0;i<103;i++){
		lines[i]=(lines[i]*2)/3;
	}
	for(int i=0;i<103;i++){

		char tmp[100];
		sprintf(tmp,"/deep/DataSet/MVCO_103/filelog/log%d.txt",i);
		ifstream ifile;
		ifile.open(tmp);
		ofstream out("train_label.txt","app");
		int count=1;
		while(!ifile.eof()){
			char str[1024];
			ifile.getline(str,sizeof(str),"\n");
			if(count<lines[i]){
				out<<str<<endl;
			}
			count++;
		}
		ifile.close();
		out.close();
		ifstream tifle(tmp);
		ofstream tout("test_label.txt","app");
		count=1;
		while(!tifile.eof()){
			char str[1024];
			tifile.getline(str,sizeof(str),"\n");
			if(count>=lines[i]){
				tout<<str<<endl;
			}
		}
		tifile.close();
		tout.close();
	}
	return 0;
}
