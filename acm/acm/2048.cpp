/*==============================================================================
    > File Name: 2048.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月11日 星期日 10时58分56秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
int sort(int *a,int n){
	int t,k;
	for(int i=0;i<n-1;i++){
		k=i;
		for(int j=i+1;j<n;j++)
			if(a[k]>a[j])k=j;
		t=a[i];
		a[i]=a[k];
		a[k]=t;
	}
	return 0;
}
void reduce(int *data,int begin,int  
int fun(int *data,int m){
	sort(data,m);
	int sum=0;
	for(int i=0;i<m;i++){
		sum+=data[i];
	}
	if(sum<2048)
		return 0;
	if(sum==2048)
		return 1;
	if(sum>2048){
		
		
	}
}
int main(){
	int m;
	int count;
	vector <int> ans;
	while(true){
		cin>>m;
		if(m==0)
			break;
		int *input;
		input =new int[m];
		for(int i=0;i<m;i++)
			cin>>input[i];
		int ans=fun(input,m);
		cout<<ans<<endl;
	}
	return 0;
}
