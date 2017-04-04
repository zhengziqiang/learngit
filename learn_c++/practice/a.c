/*==============================================================================
    > File Name: a.c
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年03月12日 星期日 15时31分27秒
 ==========================================================================*/

#include<stdio.h>
#include<math.h>
void fun(int m,int k,int a[]){
	int i,j,g=0;
	int tmp=k;
	for(i=m+1;i<=m*m;i++){
		for(j=2;j<=i;j++){
			if(i%j==0){
				break;
			}
		}
		if(j>sqrt(i)){
			if(k>=0){
				a[g]=i;
				g++;
				k--;
			}else{
				break;
			}
		}
	}
	for(i=0;i<tmp;i++){
		printf("%d\t",a[i]);
	}
	printf("\n");
}
int main(){
	int i=0;
	int a[5];
	fun(5,2,a);
	for(i=0;i<5;i++){
		printf("%d\t",a[i]);//值传递
	}
	return 0;
}
