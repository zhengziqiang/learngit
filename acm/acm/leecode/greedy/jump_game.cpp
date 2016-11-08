/*==============================================================================
    > File Name: jump_game.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月29日 星期四 20时22分55秒
 ==========================================================================*/

#include<iostream>
using namespace std;
class solution{
	public:
		bool canjump(int a[],int n){
			if(n==0){
				return true;
			}
			int v=a[0];
			for(int i=1;i<n;i++){
				v--;
				if(v<0){
					return false;

				}
				if(v<a[i]){
					v=a[i];
				}
			}
			return true;
		}

		int jump(int a[],int n){
			int step=0;
			int cur=0;
			int next=0;
			int i=0;
			while(i<n){
				if(cur>=n-1){
					break;
				}
				while(i<=cur){
					next=max(next,a[i]+1);
					i++;
				}
				step++;
				cur=next;

			}
			return step;
		}
};
int main(){
	return 0;
}
