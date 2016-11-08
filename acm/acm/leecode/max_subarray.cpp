/*==============================================================================
    > File Name: max_subarray.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月27日 星期二 22时59分25秒
 ==========================================================================*/

#include<iostream>
#include<limits.h>
using namespace std;
class solution{
	public:
		int max_subarray(int a[],int n){
			int sum=0;
			int m=INT_MIN;
			for(int i=0;i<n;i++){
				sum+=a[i];
				m=max(m,sum);
				if(sum<0)
					sum=0;
			}
			return m;
		}
		int max_subarray_divide(int a[],int n){
			return divide(a,0,n-1,INT_MIN);
		}
		int divide(int a[],int left,int right,int maxp){
			if(left>right){
				return INT_MIN;
			}
			int mid=left+(right - left)/2;
			int lmax=divide(a,left,mid-1,maxp);
			int rmax=divide(a,mid+1,right,maxp);
			maxp=max(maxp,lmax);
			maxp=max(maxp,rmax);
			int sum=0;
			int mlmax=0;
			for(int i=mid-1;i>=left;i--){
				sum+=a[i];
				mlmax=max(mlmax,sum);
			}
			sum=0;
			int mrmax=0;
			for(int i=mid+1;i<=right;i++){
				sum+=a[i];
				mrmax=max(maxp,sum);
			}
			maxp=max(maxp,a[mid]+mrmax+mlmax);
			return maxp;
		}


		//maxmimum product subarray
		//
		int max_product(int a[],int n){
			if(n==0){
				return 0;
			}
			else if(n==1){
				return a[0];
			}
			int p=a[0];
			int maxp=a[0];
			int minp=a[0];
			for(int i=1;i<n;i++){
				int t=maxp;
				maxp=max(max(maxp*a[i],a[i]),minp*a[i]);
				minp=min(min(t*a[i],a[i]),minp*a[i]);
				p=max(maxp,p);
			}
			return p;
		}



		int set_array(){
			cout<<"please input n"<<endl;
			cin>>n;
			cout<<"please input n numbers"<<endl;
			a=new int[n];
			for(int i=0;i<n;i++){
				cin>>a[i];
			}
			return 0;
		}
		int del_array(){
			delete []a;
			return 0;
		}
	private:
		int *a;
		int n;
};
int main(){
	solution s1;
	int n;
	cin>>n;
	int a[n];
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	cout<<s1.max_product(a,n)<<endl;
	for(int i=0;i<n;i++)
		cout<<a[i]<<endl;
	return 0;
}
