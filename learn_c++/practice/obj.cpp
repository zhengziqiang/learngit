/*==============================================================================
    > File Name: obj.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年03月17日 星期五 23时07分03秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
class A{
	public:
		int val;
		A a();
		A(int x=123):val(x){

		}
		A get_obj1(){
			return a;
		}
		int &get_obj(){
			return val;
		}
		~A(){
		
		}
};
int main(){
	A a(2);
	A b;
	cout<<b.val<<endl;
	int m,n;
	cin>>m>>n;
	a.get_obj()=m;
	cout<<a.val<<endl;
	a.get_obj1()=A(n);
	cout<<a.val<<endl;
	return 0;
}
