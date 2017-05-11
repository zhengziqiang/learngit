/*==============================================================================
    > File Name: 文件流.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年10月08日 星期六 20时59分33秒
 ==========================================================================*/

#include<iostream>
#include<fstream>
using namespace std;
int main(){
	int a=5;
	FILE *fp;
	fp=fopen("hehe","w");
	fprintf(fp,"%d",a);
	fclose(fp);
	return 0;
}
