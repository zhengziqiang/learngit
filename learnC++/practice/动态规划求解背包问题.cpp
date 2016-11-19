/*==============================================================================
    > File Name: 动态规划求解背包问题.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年11月18日 星期五 13时19分52秒
 ==========================================================================*/

/*0、1背包问题
一条鱼@博客园 
http://www.cnblogs.com/yanlingyin/ 
2011-12-25 
*/


#include <iostream>
#include<fstream>
#include<algorithm>
#include<vector>

//存储元素的结构 
typedef struct item
{
    int weight;
    int values;
}item;



using namespace std;
int main()
{
    int weight=10;
    int itemnum=4;
    //int k[10][4];
    
     
    vector<vector<int> > k(11,vector<int>(5));
    item items[4]={{6,30},{3,14},{4,16},{2,9}};

    
    for(int w=0;w<=weight;w++)
    {
        for(int j=0;j<=itemnum;j++)
        {
            k[w][j]=0;    
        }
    
    }

    //输出数组    
    for(int i=0;i<=weight;i++)
    {
        for(int j=0;j<=itemnum;j++)
        {
            cout<<k[i][j];
        }
        cout<<"\n";
    }
    
    
    for(int w=1;w<=weight;w++)
    {
        cout<<"测试\n";  
        for(int j=1;j<=itemnum;j++)
        {
            if(items[j-1].weight>w)        //物品质量大于背包容量，舍去 
            {
                k[w][j]=k[w][j-1];
            }
            else        //对于两种情况选出较大值 
            {
                k[w][j]=max(k[w][j-1],(k[w-items[j-1].weight][j-1]+items[j-1].values));
            }
            cout<<"k["<<w<<"]["<<j<<"]="<<k[w][j]<<"\n";
            
        }
        
    }
    
    cout<<"输出哦了"<<k[weight][itemnum]<<"\n";
    
    for(int i=0;i<=weight;i++)
    {
        for(int j=0;j<=itemnum;j++)
        {
            cout<<k[i][j]<<" ";
        }
        cout<<"\n";
    }
    
}
