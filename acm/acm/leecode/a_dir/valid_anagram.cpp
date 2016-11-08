/*==============================================================================
    > File Name: valid_anagram.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年10月01日 星期六 10时48分19秒
 ==========================================================================*/

#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
class solution{
	public:
		bool is_anagram01(string s,string t){
			sort(s.begin(),s.end());
			sort(t.begin(),t.end());
			return s==t;
		}

		bool is_anagram02(string s,string t){
			int map[26]={0};
			for(int i=0;i<s.size();i++){
				map[s[i]-'a']++;
			}
			for(int i=0;i<t.size();i++){
				map[t[i]-'a']--;
			}
			for(int i=0;i<sizeof(map)/sizeof(map[0]);i++){
				if(map[i]!=0)return false;
			}
			return true;
		}
		bool is_anagram(string s,string t){
			return is_anagram02(s,t);//时间短
			return is_anagram01(s,t);//时间长
		}
};
int main(){
	string s1;
	string s2;
	cout<<"please input the two strings"<<endl;
	cin>>s1>>s2;
	solution s;
	cout<<s.is_anagram(s1,s2)<<endl;
	return 0;
}
