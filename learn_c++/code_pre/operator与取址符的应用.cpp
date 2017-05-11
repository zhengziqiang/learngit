/*==============================================================================
    > File Name: operator与取址符的应用.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月11日 星期日 22时02分03秒
 ==========================================================================*/

#include<iostream>
using namespace std;
class Empty{
	public:
		Empty *operator&(){
			cout<<"AAA"<<endl;
			return this;//这里两个都没有指针符号,是因为返回的都是
		}
		const Empty *operator&()const{
			cout<<"BBB"<<endl;
			return this;
		}
};
int main(){
	Empty e;
	Empty *p=&e;
	const Empty e1;
	const Empty *p1=&e1;
	cout<<sizeof(Empty)<<endl;//空类的大小是一个字节
	return 0;
}
