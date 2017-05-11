/*==============================================================================
    > File Name: random_.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年03月08日 星期三 22时40分36秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<stdlib.h>
#include<time.h>
#include<fstream>
using namespace std;
double random_my(){
	return (double)rand()/RAND_MAX;
}
int random(int m){
	return (int)(random_my()*(m-1)+0.5);
}
int main(){
	int x,y;
	ofstream ofile;
	ofile.open("1.in");
	srand(time(NULL));
	for(int i=0;i<4;i++){
		while(1){
			x=random(10);
			y=random(10);
			if(x!=y)
				break;
		}
		ofile<<x<<" "<<y<<endl;
	}
	ofile.close();
	return 0;
}
