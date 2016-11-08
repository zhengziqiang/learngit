/*==============================================================================
    > File Name: remove_element_in_place.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月26日 星期一 20时08分59秒
 ==========================================================================*/

#include<iostream>
using namespace std;
class solution{
	public:
		int remove(int a[],int n,int elem){
			int i=0;
			int j=0;
			for(i=0;i<n;i++){
				if(a[i]==elem)
					continue;
				a[j]=a[i];
				j++;
			}
			return j;
		}
		int remove_sorted_array(int a[],int n){
			if(n==0){
				return 0;
			}
			int j=0;
			for(int i=1;i<n;i++){
				if(a[j]!=a[i]){
					a[++j]=a[i];
				}
			}
			return j+1;
		}

		int remove_two(int a[],int n){
			if(n==0){
				return 0;
			}
			int j=0;
			int num=0;
			for(int i=1;i<n;i++){
				if(a[j]==a[i]){
					num++;
					if(num<2){
						a[++j]=a[i];
					}
				}
				else {
					a[++j]=a[i];
					num=0;
				}
			}
			return j+1;
		}
};
