/*==============================================================================
    > File Name: world_length.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年03月27日 星期一 21时47分26秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
bool isalpha(char c){
	if(c>='a'&&c<='z'){
		return true;
	}
	return false;
}
int length(const char *s){
	if(!s || !*s)
		return 0;
	int cnt=0;
	int wdlen=0;
	for(;*s!='\0';s++){
		if(isalpha(*s)){
			cnt++;
		}
		if(!isalpha(*s)){
			if(cnt>0){
				wdlen=cnt;
			}
			cnt=0;//重新赋值
		}
	}
	return cnt>0?cnt:wdlen;
}

int main(){
	char str[100]="hello world";
	char *ptr=str;
	cout<<length(ptr)<<endl;
	return 0;
}
