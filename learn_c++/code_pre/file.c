/*==============================================================================
    > File Name: file.c
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月09日 星期五 20时21分58秒
 ==========================================================================*/

#include<stdio.h>
int main(){
	FILE *fp;
	fp=fopen("hehe","r");
	int a;
	char b;
	int c;
	fscanf(fp,"%d",&a);
	fscanf(fp,"%c",&b);
	fscanf(fp,"%d",&c);
	printf("%d\n",a);
	printf("%c\n",b);
	printf("%d\n",c);
	fclose(fp);
	return 0;
}
