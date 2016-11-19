/*==============================================================================
    > File Name: prime算法.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月08日 星期二 22时04分32秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
int prime(int cur)
{
    int index;
    int sum = 0;
    memset(visit, false, sizeof(visit));
    visit[cur] = true;
    for(int i = 0; i < m; i ++){
        dist[i] = graph[cur][i];    
    }
    
    for(int i = 1; i < m; i ++){
        
        int mincost = INF;
        for(int j = 0; j < m; j ++){
            if(!visit[j] && dist[j] < mincost){
                mincost = dist[j];
                index = j;    
            }    
        }
        
        visit[index] = true;
        sum += mincost;
        
        for(int j = 0; j < m; j ++){
            if(!visit[j] && dist[j] > graph[index][j]){
                dist[j] = graph[index][j];
            }    
        }    
    } 
    return sum;    
}

