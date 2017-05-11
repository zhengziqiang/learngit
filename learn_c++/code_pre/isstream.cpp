/*==============================================================================
    > File Name: isstream.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月13日 星期二 11时15分22秒
 ==========================================================================*/

#include<iostream>
#include<sstream>
using namespace std;
//int main(){
//	istringstream istr("156.7");
//	cout<<istr.str()<<endl;
//	int a=5;
//	istr>>a;//把istr的中的整数值赋给了a
//	float b;
//	istr>>b;
//	cout<<a<<endl;
//	cout<<b<<endl;
//	cout<<istr.str()<<endl;
//	return 0;
//}
int main(){
	ostringstream ostr("abc");
	ostr.put('d');//将a的值换为d
	cout<<ostr.str()<<endl;//打印ostr的值
	return 0;
}
