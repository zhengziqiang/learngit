/*==============================================================================
    > File Name: 克隆图.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月18日 星期五 23时52分11秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
struct undic_graph{
	int label;
	vector <undic_graph *> neighbors;
	undic_graph(int x):label(x){

	};

};
class solution{
	public:
		undic_graph *clone_graph(undic_graph *node){
			if(node==NULL){
				return NULL;
			}

		}
}
