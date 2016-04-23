/*************************************************************************
 > File Name: 静态成员+继承.cpp
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年04月23日 星期六 16时23分33秒
 ************************************************************************/

#include<iostream>
using namespace std;
class base{
	public:
		static int num;
};
int base::num=0;
class derived:public base{

};
int main(){
	base a;
	derived b;
	a.num++;
	cout<<"num 等于"<<a.num<<endl;
	b.num++;
	cout<<"b的num等于"<<b.num<<endl;
	return 0;
}
