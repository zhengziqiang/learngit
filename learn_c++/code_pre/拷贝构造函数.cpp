/*************************************************************************
 > File Name: 拷贝构造函数.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年04月23日 星期六 14时05分28秒
 ************************************************************************/

#include<iostream>
using namespace std;
class point{
	private:
		int x,y;
	public:
		point(int xx=0,int yy=0){
			x=xx;y=yy;
		}
		point(point &p);
		int getx(){
			return x;
		}
		int gety(){
			return y;
		}
};
point::point(point &p){
	x=p.x;y=p.y;
}
int main(){
	point a(11,22);
	point b(a);
	cout<<b.gety()<<endl;
	return 0;
}
