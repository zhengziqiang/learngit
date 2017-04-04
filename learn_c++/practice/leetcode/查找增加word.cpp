/*==============================================================================
    > File Name: 查找增加word.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年04月04日 星期二 16时50分01秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<string>
using namespace std;
class trie_node{
	public:
		trie_node():isword(false){
			memeset(children,0,sizeof());
		}
		trie_node * & operator [](char idx){
			int i=(idx-'a')%max_char;
			return children[i];
		}
		trie_node * & operator [](int idx){
			int i=idx%max_char;
			return children[i];
		}
		bool isword;
	private:
		trie_node * children[max_char];
};

