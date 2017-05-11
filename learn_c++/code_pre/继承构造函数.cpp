/*==============================================================================
    > File Name: 继承构造函数.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年08月18日 星期四 10时10分28秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
class layer{
	public:
		int x;
		int y;
		vector <vector <double> > mn;
};
class pl:public layer{
	public:
		pl(int m,int n){
			x=m;
			y=n;
			vector <vector <double> > dd(3,vector<double>(5,0));
			mn=dd;
		}
};
int main(){
	pl p1(5,6);
	cout<<p1.x<<endl;
	cout<<p1.mn[2][2]<<endl;
	return 0;
}
