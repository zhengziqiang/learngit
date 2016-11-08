/*==============================================================================
    > File Name: remove_elem.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年10月05日 星期三 19时14分13秒
 ==========================================================================*/

#include<iostream>
using namespace std;
int fun(int a[],int m,int elem){
	int i=0;
	int j=0;
	for(i=0;i<m;i++){
		if(a[i]==elem){
			continue;
		}
		a[j]=a[i];
		j++;
	}
	return j;
}
int main(){
	int a[5]={
		1,2,2,3,5
	};
	int k=fun(a,5,2);
	for(int i=0;i<k;i++)
		cout<<a[i]<<endl;
	return 0;
}
