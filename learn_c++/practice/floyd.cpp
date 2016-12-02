/*==============================================================================
    > File Name: floyd.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月08日 星期二 22时20分35秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
void floyd()
{
    for(int k = 0; k < n; k ++){ //作为循环中间点的k必须放在最外一层循环 
        for(int i = 0; i < n; i ++){
            for(int j = 0; j < n; j ++){
                if(dist[i][j] > dist[i][k] + dist[k][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];    //dist[i][j]得出的是i到j的最短路径 
                }     
            }    
        }    
    }    
}
int main(){
	return 0;
}
