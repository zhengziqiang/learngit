
/*==============================================================================
    > File Name: floyd.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com
    > Created Time: 2016年11月08日 星期二 22时20分35秒
 ==========================================================================*/

#include<iostream>
#include<vector>
#include<string>
#include<stdlib.h>
#include<fstream>
#include<sstream>
using namespace std;
void floyd(int n,vector <vector <int> > &dist)
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
int get_dist(int m,int n,vector <vector <int> > dist){
    return dist[m-1][n-1];
}
int main(){
    int n=7;
    cout<<"请输入地点个数:"<<endl;
//    cin>>n;
    vector <vector <int> > dist(n,vector <int>(n));
    ifstream ifile("/home/zzq/homework/matrix");
    string line;
    int cnt=0;
    while(getline(ifile,line)){
        istringstream sin(line);
        vector <string> ans;
        string field;
        while(getline(sin,field,',')){
            ans.push_back(field);
        }
        for(int i=0;i<ans.size();i++){
            if(ans[i]=="INF"){
                dist[cnt][i]=99999;
            }else{
                dist[cnt][i]=atoi(ans[i].c_str());
            }
        }
        ans.clear();
        cnt++;
    }
    ifile.close();
    floyd(n,dist);
    cout<<get_dist(1,3,dist)<<endl;
    return 0;
}
