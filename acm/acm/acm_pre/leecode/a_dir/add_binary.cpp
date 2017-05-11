/*==============================================================================
    > File Name: add_binary.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月30日 星期五 22时59分52秒
 ==========================================================================*/

#include<iostream>
#include<string>
using namespace std;
string binary(string a,string b){
	int alen=a.size();
	int blen=b.size();
	bool carry=false;
	string result;
	while(alen>0||blen>0){
		int abit=alen<=0?0:a[alen-1]-'0';
		int bbit=blen<=0?0:b[blen-1]-'0';
		int cbit=carry?1:0;
		result.insert(result.begin(),'0'+((abit+bbit+cbit)&1));
		carry=(abit+bbit+cbit>1);//相当于进1操作
		alen--;
		blen--;
	}
	if(carry){
		result.insert(result.begin(),'1');
	}
	return result;
}
int main(){
	string str1;
	string str2;
	cout<<"please input the two string"<<endl;
	cin>>str1>>str2;
	string result=binary(str1,str2);
	cout<<result<<endl;
	return 0;
}
