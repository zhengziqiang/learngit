/*==============================================================================
    > File Name: 最大公约数.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月12日 星期一 19时01分37秒
 ==========================================================================*/

#include<iostream>
using namespace std;
//辗转相乘法
//int main(){
//	int a,b;
//	cin>>a>>b;
//	int c;
//	int m=a,n=b;
//	while(b!=0){
//		c=a%b;
//		a=b;
//		b=c;
//	}
//	cout<<m*n/a<<endl;
//	return 0;
//}
//相减法求最大公约数
//int main(){
//	int a,b;
//	cin>>a>>b;
//	int m=a,n=b;
//	while(a!=b){
//		if(a>b)
//			a=a-b;
//		else
//			b=b-a;
//	}
//	cout<<m*n/a<<endl;
//	return 0;
//}
int main(){
	int a,b;
	cin>>a>>b;
	int m=a,n=b;
	int t=m>n?n:m;
	while(true){
		if(m%t==0&&n%t==0)
			break;
		t--;
	}
	cout<<m*n/t<<endl;
	return 0;
}
