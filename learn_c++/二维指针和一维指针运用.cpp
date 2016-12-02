/*==============================================================================
    > File Name: 二维指针和一维指针运用.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月06日 星期二 14时28分44秒
 ==========================================================================*/

#include<iostream>
using namespace std;
int main(){
	int **p;
	p=new int*[4];
	for(int i=0;i<4;i++){
		p[i]=new int [5];
		for(int j=0;j<5;j++)
			p[i][j]=i*5+j;
	}
	int **ptr=p;//二维指针给二维指针赋值
	int *ptr1=*ptr;//二维指针指向一维指针的第一个方向
	for(int i=0;i<5;i++){
		cout<<*(ptr1+i)<<endl;
	}
	ptr1=*(ptr+2);//第二次换方向的时候应该是不加*，因为二维指针的一维就是地址
	for(int i=0;i<5;i++){
		cout<<*(ptr1+i)<<endl;
	}
	return 0;
}
