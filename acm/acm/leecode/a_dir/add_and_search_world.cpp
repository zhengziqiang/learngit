/*==============================================================================
    > File Name: add_and_search_world.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月30日 星期五 12时44分51秒
 ==========================================================================*/

#include<iostream>
#include<string.h>
#include<string>
using namespace std;
const int max_chars = 26;
class trie_node{
	public:
		trie_node():isworld(false){
			memset(children,0,sizeof(children));
		}
		trie_node * & operator [](char idx){
			int i=(idx-'a')%max_chars;
			return children[i];
		}
		trie_node * & operator [](int idx){
			int i=idx%max_chars;
			return children[i];
		}
		bool isworld;
	private:
		trie_node* children[max_chars];
};

class trie{
	public:
		trie():root(new trie_node()){

		}
		~trie(){
			free_tree(root);
		}
		void put(string &s){
			trie_node *node=root;
			for(int i=0;i<s.size();i++){
				if((*node)[s[i]]==NULL){
					(*node)[s[i]]=new trie_node();

				}
				node=(*node)[s[i]];
			}
			node->isworld=true;
		}
		bool search(string &s){
			return get(s,this->root);
		}
	private:
		bool get(string &s,trie_node *root,int idx=0){
			trie_node *node=root;
			for(int i=idx;i<s.size();i++){
				if(s[i]=='.'){
					node=(*node)[s[i]];
					if(node==NULL)
						return false;
				}
				else {
					for(int j=0;j<max_chars;j++){
						trie_node *p=(*node)[j];
						if(p==NULL){
							continue;
						}
					if(i<s.size()-1){
						if(this->get(s,p,i+1)){
							return true;
						}
						continue;
					}
					if(p->isworld){
						return true;
					}
					}
				}
				return false;
			}
		return node->isworld;
		}
	private:
		void free_tree(trie_node* root){
			for(int i=0;i<max_chars;i++){
				if((*root)[i]!=NULL){
					free_tree((*root)[i]);
				}
			}
			delete root;
		}
		trie_node *root;
};

class word_dictionary{
	public:
		void add_word(string word){
			tree.put(word);
		}
		bool search(string word){
		return tree.search(word);
		}
	private:
		trie tree;
};

int main(){
	word_dictionary wd;
	wd.add_word("a");
	cout<<wd.search("a.")<<endl;
	cout<<wd.search(".a")<<endl;
	wd.add_word("bad");
	cout<<wd.search("b..")<<endl;
	return 0;
}
