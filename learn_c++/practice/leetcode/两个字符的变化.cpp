/*==============================================================================
    > File Name: 两个字符的变化.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月21日 星期一 13时09分37秒
 ==========================================================================*/
/********************************************************************************** 
* 
* Given two words word1 and word2, find the minimum number of steps required to 
* convert word1 to word2. (each operation is counted as 1 step.)
* 
* You have the following 3 operations permitted on a word:
* 
* a) Insert a character
* b) Delete a character
* c) Replace a character
* 
*               
**********************************************************************************/
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
int min(int x,int y,int z){
	return std::min(x,std::min(y,z));
}
int mindistance(string word1,string word2){
	int n1=word1.size();
	int n2=word2.size();
	if(n1==0)
		return n2;
	if(n2==0)
		return n1;
	vector <vector <int> > m(n1+1,vector <int>(n2+1));
	for(int i=0;i<m.size();i++){
		m[i][0]=i;
	}
	for(int i=0;i<m[0].size();i++){
		m[0][i]=i;
	}
	//动态规划
	int row,col;
	for(row=1;row<m.size();row++){
		for(col=1;col<m[row].size();col++){
			if(word1[row-1]==word2[col-1]){
				m[row][col]=m[row-1][col-1];
			}
			else{
				int minvalue=min(m[row-1][col-1],m[row-1][col],m[row][col-1]);
				m[row][col]=minvalue+1;
			}
		}
	}
	return m[row-1][col-1];
}
int main(){
	string s1="hello";
	string s2="world";
	cout<<mindistance(s1,s2)<<endl;
	return 0;
}
