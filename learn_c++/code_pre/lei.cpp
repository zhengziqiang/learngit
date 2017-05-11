/*************************************************************************
 > File Name: lei.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年05月06日 星期五 23时07分37秒
 ************************************************************************/

#include<iostream>
#include<string>
using namespace std;
class point{
	private:
		int x,y;
	public:
		int init(int i,int j){
			x=i;y=j;
		}
		int setxy(int m,int n){
			x=m;y=n;
		}
		int move(int mx,int my){
			x+=mx;y+=my;
		}
		int getx(){
			return x;
		}
		int gety(){
			return y;
		}
};
int main(){
	point p1;
	p1.init(1,2);
	cout<<p1.getx()<<endl;
	p1.setxy(3,4);
	cout<<p1.getx()<<endl;
	int m,n;
	cout<<"please input a number:"<<endl;
	cin>>m>>n;
	p1.setxy(m,n);
	cout<<p1.getx()<<endl;
	int mx,my;
	cout<<"please input the distance:"<<endl;
	cin>>mx>>my;
	p1.move(mx,my);
	cout<<p1.getx()<<endl;
	return 0;
}
