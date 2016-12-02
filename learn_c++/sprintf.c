/*==============================================================================
    > File Name: file.c
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月09日 星期五 09时59分04秒
 ==========================================================================*/

#include<stdio.h>
int main(){
	FILE *fp;
	int n=1;
	char tempchar[100];
	sprintf(tempchar,"test%d",n);//将两个文件连接在一起
	fp=fopen(tempchar,"w");
	fprintf(fp,"%s\n","hello world");
	fclose(fp);
	FILE *a;
	int acc;
	a=fopen("a","r");
	fscanf(a,"%d",&acc);//读取文件中的数据到数组中去
	fclose(a);
	printf("%d",acc);
	return 0;

}
