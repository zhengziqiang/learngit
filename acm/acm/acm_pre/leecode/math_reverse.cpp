/*==============================================================================
    > File Name: math_reverse.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月29日 星期四 15时36分17秒
 ==========================================================================*/

#include<iostream>
using namespace std;
class solution{
	public:
		int reverse(int x){
			if(x==0){
				return x;
			}
			int ret=0;
			while(x!=0){
				ret=ret*10+x%10;
				x/=10;
			}
			return ret;
		}
};
int main(){
	int n;
	cin>>n;
	solution s;
	int ret=s.reverse(n);
	cout<<ret<<endl;
}
