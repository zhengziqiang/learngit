/*==============================================================================
    > File Name: merge_sort_array.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月26日 星期一 21时36分48秒
 ==========================================================================*/

#include<iostream>
using namespace std;
class solution{
	public:
		void merge(int a[],int m,int b[],int n){
			int i=m+n-1;
			int j=m-1;
			int k=n-1;
			while(i>=0){
				if(j>=0&&k>=0){
					if(a[j]>b[k]){
						a[i]=a[j];
						j--;
					}
					else{
						a[i]=b[k];
						k--;
					}
				}
				else if(j>=0){
					a[i]=a[j];
					j--;
				}
				else if(k>=0){
					a[i]=b[k];
					k--;
				}
				i--;
			}
		}
};
