/*==============================================================================
    > File Name: letter_combination.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月29日 星期四 13时57分16秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<string>
using namespace std;
class solution{
	public:
		vector <string> letter_combination(string digits){
			vector <string> ret;
			vector <string> dic;
			string tmp;
			dic.push_back(" ");
			dic.push_back(" ");
			dic.push_back("abc");
			dic.push_back("def");
			dic.push_back("ghi");
			dic.push_back("jkl");
			dic.push_back("mno");
			dic.push_back("pqrs");
			dic.push_back("tuv");
			dic.push_back("wxyz");
			combination(ret,tmp,digits,dic,0);
		}

		void combination(vector <string> &ret,string tmp,string digits,vector <string> dic,int level){
			if(level==digits.size()){
				ret.push_back(tmp);
				return ;
			}
			int index=digits[level]- '0';
			for(int i=0;i<dic[index].size();i++){
				ret.push_back(dic[index][i]);
				combination(ret,tmp,digits,dic,level+1);
				ret.pop_back();
			}
		}
};
int main(){
	vector <string> ans;
	solution s1;
	string digits="23";
	ans=s1.letter_combination(digits);
	vector <string>::iterator iter;
	for(iter=ans.begin();iter!=ans.end();iter++){
		cout<<*iter<<endl;
	}
	return 0;
}
