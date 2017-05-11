/*************************************************************************
 > File Name: 数字统计.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年05月09日 星期一 21时24分53秒
 ************************************************************************/

#include<iostream>
#include<string>
using namespace std;
struct p{
	int x;
	int y;
};
int main(){
	int n;
	cin>>n;
	int a[n];
	for(int i=0;i<n;i++)cin>>a[i];
	struct p p[n];
	for(int i=0;i<n;i++){
		p[i].x=0;
		p[i].y=0;
	}
	int m=0;
	int flag=0;
	p[m].x=a[0];
	p[m].y=1;
	for(int i=1;i<n;i++){
		for(int j=0;j<=m;j++){
			if(p[j].x==a[i]){
				p[j].y+=1;
				flag=1;
				break;
			}
			}
		if(flag==0){
			m+=1;
			p[m].x=a[i];
			p[m].y=1;
		}
		else flag=0;
		}
	for(int i=0;i<=m;i++){
		cout<<p[i].x<<": "<<p[i].y<<endl;
	}
	return 0;
}
