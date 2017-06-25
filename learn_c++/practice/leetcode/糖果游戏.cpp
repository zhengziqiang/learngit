/*==============================================================================
    > File Name: 糖果游戏.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2017年04月07日 星期五 15时07分14秒
 ==========================================================================*/

#include<iostream>
#include<vector>
using namespace std;
int candy(vector<int> &ratings) {

    vector<int> candyCnt(ratings.size()) ;
    //allocate candies, considering the minimal rating on the left
    candyCnt[0] = 1;
    for(int i = 1; i < ratings.size(); i++){
        candyCnt[i] = ratings[i] > ratings[i-1] ? candyCnt[i-1]+1 : 1;
    }
    print(candyCnt); 
    //modify the allocation, considering the minimal rating on the right
    int totalCandy = candyCnt[ratings.size()-1];
    for(int i = ratings.size()-2; i >= 0; i--){
        candyCnt[i] = (ratings[i] > ratings[i+1] && candyCnt[i+1]+1 > candyCnt[i]) ? candyCnt[i+1]+1 : candyCnt[i];
        //count total candies by the way
        totalCandy += candyCnt[i];
    }
    print(candyCnt);
    return totalCandy;
}

void generateRatings(vector<int> &ratings, int n) {
    srand(time(0));
    for (int i=0; i<n; i++) {
        ratings.push_back(rand()%10);
    }
}

void print(vector<int> &v) {
    for(int i=0; i<v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;
}

int main(int argc, char**argv)
{
    int n = 10;
    if (argc>1){
        n = atoi(argv[1]);
    }   
    vector<int> ratings;
    generateRatings(ratings, n);
    print(ratings);

    cout << candy(ratings) << endl;

    cout << "--------------------" << endl;
    int r[] = { 5, 6, 7, 4, 1, 2, 3, 2, 1, 7 };
    vector<int> ra(r, r+sizeof(r)/sizeof(r[0]));
    print(ra);
    cout << candy(ra) << endl;
    return 0;
}
