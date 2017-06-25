/*==============================================================================
    > File Name: a.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年03月15日 星期三 22时27分52秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<stdio.h>
using namespace std;
int main ()
{
	int i,j,g,count=0,flag=0;
	int N;int A[100][100];
	int a[100][100];
	scanf("%d\n",&N);
	for(i=0;i<N;i++){
	  for(j=0;j<N;j++){
		a[i][j]=0;		//建立一个初始地图每个坐标点的值都为0
	  }
	}
	//for(i=0;i<N;i++)
	// {
	//   for(j=0;;j++)
	//   {
	//	 scanf("%d\n",&A[i][j]);//输入各地点之间的关系，以二维数组表示 
	//		if(A[i][0]==0)
	//	  	break;
	//	}
	//	if(A[i][0]==0)
	//		break;
	// }
	int n;
	cin>>n;
	if(n!=0){
		for(int i=0;i<n;i++){
			cin>>
		}
	}
	cout<<"initial finished"<<endl;
	 for(i=0;A[i][0]!=0;i++)
         for(j=0;*(*(A+i)+j)!='\0';j++)
	     {
		    a[A[i][j]-1][A[i][j]]=1;//互相有联系的地点之间对应的坐标值改为1 
	      }
	for(i=0;i<N;i++)
	 for(j=0;j<N;j++)
	 {
 		if(a[i][j]==1) flag++;//flag表示每行中有联系地点的个数 
 		if(flag>1) {count++;flag=0;break;}//如果每行中有联系的点数超过2则计数并跳出本次循环 
 	}
 	printf("%d\n",count); 
	return 0;
}
