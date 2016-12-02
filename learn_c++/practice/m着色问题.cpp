/*==============================================================================
    > File Name: m着色问题.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月14日 星期一 17时42分52秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
int init_graph(int **w,int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			w[i][j]=1;
		}
	}
	return 0;
}
bool promising(int i,int **w,int *vcolor){
	int j;
	bool swi;
	swi=true;
	j=1;
	while(j<i&&swi){
		if(w[i][j]&&vcolor[i]==vcolor[j])
			swi=false;
		j++;
	}
	return swi;
}
void m_color(int i,int m,int n,int *vcolor,int **w){
	int color=1;
	if(promising(i,w,vcolor)){
		if(i==n){
			for(int j=0;j<n;j++){
				cout<<vcolor[j]<<" ";
			}
			cout<<endl;
		}
		else{
			for(color=1;color<=m;color++){
				vcolor[i+1]=color;
				m_color(i+1,m,n,vcolor,w);
			}
		}
	}
}
int main(){
	int **w;
	int n;
	cout<<"please input the number of the nodes"<<endl;
	cin>>n;
	w=new int *[n];
	for(int i=0;i<n;i++){
		w[i]=new int [n];
	}
	init_graph(w,n);
	int m=5;
	int *vcolor;
	vcolor=new int[n];
	m_color(0,m,n,vcolor,w);
	return 0;
}
