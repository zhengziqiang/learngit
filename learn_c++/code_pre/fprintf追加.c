/*==============================================================================
    > File Name: fprintf追加.c
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月25日 星期五 22时09分48秒
 ==========================================================================*/

#include<stdio.h>
int main(){
	FILE *out;
	out=fopen("/home/zzq/code/code/log_test","a");
	fprintf(out,"hello world");
	fclose(out);
	return 0;
}
