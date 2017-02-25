/*==============================================================================
    > File Name: forwenti.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年02月21日 星期二 09时20分17秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
int main(){
	int m=0;

	for(int i=0;i<2;i++){
		for(int j=0;j<4;j++){
			if(j>2){
				break;
			}else{
				cout<<"i am from j"<<" and i="<<i<<endl;
			}
			for(int k=0;k<2;k++){
				m=0;
				
				for(int l=0;l<4;l++){
					if(m>2){
						break;//结束的是本层循环
					}else{
						m++;
						cout<<"I am from l and j="<<j<<"and k="<<k<<endl;
						continue;
					}
				}
			}
		}
	}
	return 0;
}
