/*==============================================================================
    > File Name: dijkstra.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月08日 星期二 22时21分34秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
void dijkstra(int s)   //s是起点
{
    memset(visit, false, sizeof(visit));    
visit[s] = true;
    for(int i = 0; i < n; i ++){
        dist[i] = graph[s][i];
    }
     
    int index;
    for(int i = 1; i < n; i ++){
        int mincost = INF;
        for(int j = 0; j < n; j ++){
            if(!visit[j] && dist[j] < mincost){
                mincost = dist[j];
                index = j;    
            }    
        }
        visit[index] = true;
        for(int j = 0; j < n; j ++){
            if(!visit[j] && dist[j] > dist[index] + graph[index][j]){
                dist[j] = dist[index] + graph[index][j];
            }    
        }    
    }
}
