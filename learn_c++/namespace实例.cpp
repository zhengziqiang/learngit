/*==============================================================================
    > File Name: namespace实例.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月12日 星期一 16时43分01秒
 ==========================================================================*/

#include<iostream>
using namespace std;

namespace A{
	class point{
		public:
			int x;
			int set_x(int m){
				x=m;
				return 0;
			}
			int get_x(){
				return x;
			}
	};
	void fun(){
		cout<<"this is namespace A"<<endl;
	}
};

namespace B{
	class point{
		public:
			int x;
			int set_x(int m){
				x=m;
				return 0;
			}
			int get_x(){
				return x;
			}
	};
	void fun(){
		cout<<"this is namespace B"<<endl;
	}
};
int main(){
	A::point p;
	p.set_x(5);
	A::fun();
	B::point pb;
	return 0;
}
