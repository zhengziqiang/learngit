/*==============================================================================
    > File Name: additivenumber.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月30日 星期五 23时21分33秒
 ==========================================================================*/

#include<iostream>
#include<string>
using namespace std;
class solution{
	public:
		bool is_additive(string num){
			int len=num.size();
			for(int i=1;i<len/2+1;i++){
				string n1=num.substr(0,1);
				if(n1.size()>1&&n1[0]=='0')break;
				for(int j=i+1;j<len;j++){
					string n2=num.substr(i,j-1);
					if(n2.size()>1&&n2[0]=='0')break;
					string n3=num.substr(j);
					if(is_additive_number(n1,n2,n3)) return true;
				}
			}
			return false;
		}
	private:
		bool is_additive_number(string &n1,string &n2,string &n3){
			string add=string_add(n1,n2);
			if(add.size()>n3.size())return false;
			if(add=n3)return true;
			string cut=n3.substr(0,add.size());
			if(add=cut){
				string rest=n3.substr(add.size());
				return is_additive_number(n2,add,rest);
			}
			return false;
		}

		string string_add(string n1,string n2){
				if(n1.size()<n2.size()){
					string tmp=n1;
					n1=n2;
					n2=tmp;
				}
				int carry=0;
				string result;
				for(int i=n1.size()-1,j=n2.size()-1;i>=0;i--,j--){
					int n=n1[i]-'0'+carry;
					if(j>=0){
						n +=n2[j] - '0';
					}
					char ch=n%10+'0';
					carry=n/10;
					result=ch+result;
				}
				if(carry>0)
					result=(char)(carry+'0')+result;
				return result;
		}
};

