/*==============================================================================
    > File Name: a_getobj.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年03月17日 星期五 22时56分32秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
class A{
	public:

		int val;
		A(int x):val(x){
		}
	int &get_obj(){
		return val;
	}
	~A(){

	}
};
int main{
	A a(2);
	cout<<a.val<<endl;
	return 0;
}
