/*==============================================================================
    > File Name: 运算符重载.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年01月22日 星期日 17时29分05秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
class trie_node{
	public:
		trie_node * & operator [](int x){
			return children[x];
		}
		trie_node* & operator [](char x){
			int a=(x-'a')%26;
			return children[a];
		}
		trie_node *children[5];
};
int main(){
	cout<<(&1)<<endl;
	return 0;
}
