/*************************************************************************
 > File Name: 析构函数.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年04月23日 星期六 15时46分57秒
 ************************************************************************/

#include<iostream>
using namespace std;
class P{
	private:
		int X,Y;
	public:
		P(int x,int y){
			X=x;Y=y;
			cout<<"函数正在执行"<<endl;
		}
		int getX(){
			return X;
		}
		int getY(){
			return Y;
		}
		~P(){
			cout<<"析构"<<endl;
		}
};
int main(){
	P *p=new P(1,2);
	cout<<p->getX()<<endl;
	for(int i=1;i<3;i++){
		P p(i*1,i+1);
	}
	return 0;
}
