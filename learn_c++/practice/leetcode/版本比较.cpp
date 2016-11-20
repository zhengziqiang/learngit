/*==============================================================================
    > File Name: 版本比较.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月19日 星期六 16时16分21秒
 ==========================================================================*/
/********************************************************************************** 
 * 
 * Compare two version numbers version1 and version1.
 * If version1 > version2 return 1, if version1 < version2 return -1, otherwise return 0.
 * 
 * You may assume that the version strings are non-empty and contain only digits and the . character.
 * The . character does not represent a decimal point and is used to separate number sequences.
 * For instance, 2.5 is not "two and a half" or "half way to version three", it is the fifth second-level revision of the second first-level revision.
 * 
 * Here is an example of version numbers ordering:
 * 0.1 < 1.1 < 1.2 < 13.37
 * 
 * Credits:Special thanks to @ts for adding this problem and creating all test cases.
 *               
 **********************************************************************************/
#include<iostream>
#include<vector>
#include<stdlib.h>
#include<sstream>
using namespace std;
class solution{
	public:
		vector <int> &split(const string &s,char delim,vector <int>	&elems){
			stringstream ss(s);
			string item;
			while(getline(ss,item,delim)){
				elems.push_back(atoi(item.c_str()));
			}
			return elems;
		}
		vector <int> split(const string &s,char delim){
			vector <int> elems;
			split(s,delim,elems);
			return elems;
		}
		
		void trim_zero(vector <int> &v){
			while(v.back()==0){
				v.pop_back();
			}
		}
		int compare(string version1,string version2){
			vector <int> ver1=split(version1,'.');
			vector <int> ver2=split(version2,'.');
			trim_zero(ver1);
			trim_zero(ver2);
			for(int i=0;i<ver1.size()&&i<ver2.size();i++){
				if(ver1[i]<ver2[i]){
					return 1;
				}
				else if(ver1[i]>ver2[i]){
					return -1;
				}
			}
		if(ver1.size()<ver2.size()){
			return 1;
		}
		else if(ver2.size()<ver1.size()){
			return -1;
		}
		return 0;
		}
};
int main(){
	return 0;
}
