/*************************************************************************
 > File Name: 类中读取数值.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年04月23日 星期六 15时18分54秒
 ************************************************************************/

#include<iostream>
using namespace std;
class P{
	private:
		int X,Y;
	public:
		P(){
			X=0;
			Y=0;
		}
		P(int a,int b){
			X=a;Y=b;
		}
		int getX(){
			return X;
		}
		int getY(){
			return Y;
		}
};
int main(){
	P p1;
	P p2(2,3);
	P *p;
	p=&p2;
	cout<<p1.getX()<<endl;
	cout<<p->getX()<<endl;
	return 0;
}
