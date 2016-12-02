/*************************************************************************
 > File Name: 类中的函数.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年04月23日 星期六 15时03分49秒
 ************************************************************************/

#include<iostream>
using namespace std;
class Tpoint{
	private:
		int X,Y;
	public:
		void point(int x,int y);
		int getX(){
			return X;
		}
		int getY(){
			return Y;
		}
		void Move(int xset,int yset);
};
void Tpoint::point(int x,int y){
	X=x;Y=y;
}
void Tpoint::Move(int xset,int yset){
	X+=xset;
	Y+=yset;
}
int main(){
	Tpoint D1;
	D1.point(2,3);
	cout<<D1.getX()<<" "<<D1.getY()<<endl;
	D1.Move(2,3);
	cout<<D1.getX()<<" "<<D1.getY()<<endl;
	return 0;
}
