/*==============================================================================
    > File Name: code_lina.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月09日 星期五 20时47分04秒
 ==========================================================================*/

#include<iostream>
#include<stdio.h>
using namespace std;
int main(){
	FILE *fp;
	fp=fopen("uci","r");
	int a[569];
	char tmp;
	long int m;
	char label;
	double data[569][30];
	for(int i=0;i<569;i++){
			fscanf(fp,"%ld",&m);
			fscanf(fp,"%c",&tmp);
			fscanf(fp,"%c",&label);
			if(label=='M')
				a[i]=1;
			else
				a[i]=0;
			fscanf(fp,"%c",&tmp);
		for(int j=0;j<29;j++){
			fscanf(fp,"%lf",&data[i][j]);
			fscanf(fp,"%c",&tmp);
		}
		fscanf(fp,"%lf",&data[i][29]);
	}
	fclose(fp);
	FILE *raw;
	raw=fopen("data","w");
	for(int i=0;i<569;i++){
		for(int j=0;j<30;j++){
			fprintf(fp,"%lf\t",data[i][j]);
		}
		fprintf(fp,"\n");
	}
	fclose(raw);
	FILE *la;
	la=fopen("lab","w");
	for(int i=0;i<569;i++){
		fprintf(la,"%d\n",a[i]);
	}
	fclose(la);
	return 0;
}
