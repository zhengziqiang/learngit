/*==============================================================================
    > File Name: nk组合问题.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月19日 星期六 10时38分44秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int	get_combination(int n,int k,vector <int> solution,vector <vector <int> > &result){
	if(k==0){
		vector <int> solution;
		sort(solution.begin(),solution.end());
		result.push_back(solution);
		return 0;//递归出口
	}
	for(int i=n;i>0;i--){
		solution.push_back(i);
		get_combination(n-1,k-1,solution,result);//递归寻找下一个数
		solution.pop_back();//更换另外一个数
	}

}
vector <vector <int> > recursive_fun(int n,int k){
	vector <int> solution;
	vector <vector <int> > result;
	return result;
}

//非递归方法
vector <vector <int > > combine(int n,int k){
	vector <vector <int> > result;
	vector <int > d;
	for(int i=0;i<n;i++){
		d.push_back((i<k)?1:0);//i<k的话就是1
	}
	while(1){
		vector <int> v;
		for(int x=0;x<n;x++){
			if(d[x]){
				v.push_back(x+1);
			}
		}
		result.push_back(v);
		int i;
		bool found=false;
		int ones=0;
		for(i=0;i<n-1;i++){
			if(d[i]==1&&d[i+1]==0){
				d[i]=0;
				d[i+1]=1;
				found=true;
				for(int j=0;j<i;j++){
					d[j]=(ones>0)?1:0;
					ones--;
				}
				break;

			}
			if(d[i]==1)
				ones++;

		}
		if(!found){
			break;
		}
	}
	return result;
}
int main(){
	return 0;
}
