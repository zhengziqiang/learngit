/*==============================================================================
    > File Name: add_digits.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月30日 星期五 22时00分57秒
 ==========================================================================*/

#include<iostream>
#include<stdlib.h>
using namespace std;
class solution{
	public:
		int add_digits(int num){
			switch(random()%5+1){
				case 1:
					return add_digits01(num);
				case 2:
					return add_digits02(num);
				case 3:
					return add_digits03(num);
				case 4:
					return add_digits04(num);
				default:
					return add_digits05(num);
			}
		}
		int add_digits01(int num){
			while(num>9){
				int sum;
				for(sum=0;num>0;sum+=num%10,num/10);
				num=sum;
			}
			return num;
		}
		int add_digits02(int num){
			while(num>9){
				num=num/10+num%10;
			}
			return num;
		}
		int add_digits03(int num){
			return num>9?((num%9)==0?9:num%9):num;
		}
		int add_digits04(int num){
			return (num-1)%9+1;
		}
		int add_digits05(int num){
			return num-9*((num-1)/9);
		}
};
int main(){
	solution s;
	int m;
	cout<<"please input the number"<<endl;
	cin>>m;
	cout<<s.add_digits(m)<<endl;
	return 0;
}
