/*==============================================================================
    > File Name: rand.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月10日 星期四 13时49分06秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<time.h>
#include<stdlib.h>
#include<fstream>
using namespace std;
int main(){
	srand(time(NULL));
	ofstream ofile;
	ofile.open("out");
	int n=100;
	while(n){
		ofile<<rand()<<endl;
		n--;
	}
	ofile.close();
	return 0;
}
