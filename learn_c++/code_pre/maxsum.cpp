/*==============================================================================
    > File Name: maxsum.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年10月27日 星期四 20时29分42秒
 ==========================================================================*/

#include<iostream>
using namespace std;
int maxsum(int a[],int m,int n){
	int sum=0;
	if(m==n){
		return a[m];
	}
	else{
		int center,midsum,leftsum,rightsum;
		int s1,lefts,s2,rights;
		center=(m+n)/2;
		leftsum=maxsum(a,m,center);
		rightsum=maxsum(a,center+1,n);
		s1=0;lefts=0;
		for(int i=center;i>=m;i--){
			lefts+=a[i];
			if(lefts>s1)
				s1=lefts;
		}
		s2=0;rights=0;
		for(int i=center+1;i<=n;i++){
			rights+=a[i];
			if(rights>s2)
				s2=rights;
		}
		midsum=(s1+s2);
		if(midsum<leftsum)
			midsum=leftsum;
		if (midsum<rightsum)
			midsum=rightsum;
		sum=midsum;
	}
	return sum;
	
}
int main(){
	int a[10]={
		-1,4,-8,9,10,12,-1,-1,-3,-6
	};
	cout<<maxsum(a,0,9);
	return 0;
}
