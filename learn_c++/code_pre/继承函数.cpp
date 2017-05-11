/*************************************************************************
 > File Name: 继承函数.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年04月26日 星期二 14时36分58秒
 ************************************************************************/

#include<iostream>
using namespace std;
class p{
	private:
		int i;
	public:
		p(int j=0){
			i=j;
		}
		void printi(){
			cout<<"i="<<i<<endl;
		}
		int geti(){
			return i;
		}
};
class derived:public p{
	public:
		void printj(){
			cout<<geti()<<endl;
		}
};
int main(){
	derived d;
	d.printj();
	return 0;
}
