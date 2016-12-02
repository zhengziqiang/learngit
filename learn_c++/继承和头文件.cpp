/*************************************************************************
 > File Name: 继承和头文件.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年04月23日 星期六 19时44分19秒
 ************************************************************************/

#include<iostream>
#include "basedef.h"
using namespace std;
class derived1:public base{
	public:
		void printi(){
			cout<<"i="<<geti()<<endl;
		}
		void printj(){
			cout<<"j="<<getj()<<endl;
		}
		void printk(){
			cout<<"k="<<getk()<<endl;
		}
};
int main(){
	derived1 d;
	d.printi();
	d.printj();
	d.printk();
	cout<<"d.j="<<d.j<<endl;//通过访问继承而来的公有数据成员
	cout<<"d.getj()="<<d.getj()<<endl;//通过公有成员函数访问数据
	return 0;

}
