/*==============================================================================
    > File Name: class申请class.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月06日 星期二 10时12分50秒
 ==========================================================================*/

#include<iostream>
using namespace std;
class Point{
	public:
		int x;
		int setx(int m){
			x=m;
			return 0;
		}
		Point *p;//class中也能调用自己的class，也能用指针
};
int main(){
	Point p1;
	p1.p=new Point [2];
	for(int i=0;i<2;i++)
		p1.p[i].setx(i);
	for(int i=0;i<2;i++)
		cout<<p1.p[i].x<<endl;
	delete []p1.p;
	return 0;
}
