/*************************************************************************
 > File Name: basedef.h
 > Author: zhengziqiang
 > Mail: 1174986943@qq.com 
 > Created Time: 2016年04月23日 星期六 19时40分20秒
 ************************************************************************/

#include<iostream>
#ifndef _base_h_
#define _base_h_
using namespace std;
class base{
	private:
		int i;
	public:
		base(){
			i=1;j=2;k=3;
		}
		int j;
		int getj(){
			return j;
		}
		int geti(){
			return i;
		}
	protected:
		int k;
		int getk(){
			return k;
		}
};
#endif
