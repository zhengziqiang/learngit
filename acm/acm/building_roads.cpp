/*==============================================================================
    > File Name: building_roads.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月12日 星期一 15时43分26秒
 ==========================================================================*/
//There is a magic planet in the space. There is a magical country on the planet. There are N cities in the country. The country is magical because there are exactly N-1 magic roads between the N cities, and from each city, it is possible to visit any other city. But after the huge expansion of the country, the road system seems to be messy. The moderator decided to rebuild the road system.
//
//As a worker, I cannot do too much things. I could just move one road to another position connecting arbitrary 2 cities using my magic, keeping its length unchanged. Of course, afterwards all the N cities have to be still connected. I wonder how to move in order to make the farthest distance between any two cities minimum. Could you solve it for me? 
#include<iostream>
#include<stdio.h>
#include<map>
#include<vector>
using namespace std;
int main(){
	int T;
	cin>>T;
	int *test;
	test=new int [T];
	int num_city=0;
	int a, b;
	char key[10];
	vector <map<string,int> > net;
	for(int i=0;i<T;i++){
		cin>>num_city;
		int *distance;
		distance=new int[num_city];
		map <string,int> ma;
		for(int j=0;j<num_city-1;j++){
			cin>>a>>b>>distance[j];
			key[0]='\0';
			sprintf(key,"%d%d",a,b);
			ma[key]=distance[j];
		}
		net.push_back(ma);
		ma.clear();
	}
	
	return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <iostream>
#include <sstream>
 
using namespace std;
 
const int maxn = 2505;
 
struct Graph {
    int hed[maxn], pnt[maxn*2], val[maxn*2], nxt[maxn*2], cnt;
 
    void init(int n) {
        cnt = 0;
        memset(hed, -1, 4 * n);
    }
    void addedge(int x, int y, int v) {
        pnt[cnt] = y; val[cnt] = v; nxt[cnt] = hed[x]; hed[x] = cnt++;
        pnt[cnt] = x; val[cnt] = v; nxt[cnt] = hed[y]; hed[y] = cnt++;
    }
} g;
 
queue<int> Q;
int n;
int banx, bany;
int par[maxn], dis[maxn];
int xx, yy;
 
int bfs(int x) {
    int ret = x;
    dis[x] = 0;
    Q.push(x);
    while (!Q.empty()) {
        int a = Q.front();
        Q.pop();
        for (int p = g.hed[a]; p != -1; p = g.nxt[p]) {
            int b = g.pnt[p];
            if (dis[b] != -1) continue;
            if (a == banx && b == bany || a == bany && b == banx) continue;
            par[b] = a;
            dis[b] = dis[a] + g.val[p];
            Q.push(b);
            if (dis[b] > dis[ret]) ret = b;
        }
    }
    return ret;
}
 
void FindRoad(int x) {
    memset(par, -1, 4 * n);
    memset(dis, -1, 4 * n);
    yy = bfs(x);
    memset(par, -1, 4 * n);
    memset(dis, -1, 4 * n);
    xx = bfs(yy);
}
 
int ans;
vector<int> v, d;
 
void Solve() {
    int t, disx, disy, disedge, dxx, dyy;
    banx = bany = -1;
    FindRoad(0);
    v.clear(); d.clear();
    t = xx;
    while (true) {
        v.push_back(t);
        t = par[t];
        if (t == -1) break;
        d.push_back(dis[v.back()] - dis[t]);
    }
    ans = dis[xx];
    for (int i = 1; i < v.size(); i++) {
        banx = v[i-1]; bany = v[i];
        disedge = d[i-1];
        FindRoad(banx);
        dxx = disx = dis[xx];
        for (t = xx; t != -1; t = par[t])
            disx = min(disx, max(dis[xx] - dis[t], dis[t]));
        FindRoad(bany);
        dyy = disy = dis[xx];
        for (t = xx; t != -1; t = par[t])
            disy = min(disy, max(dis[xx] - dis[t], dis[t]));
        ans = min(ans, max(max(disx + disy + disedge, dxx), dyy));
    }
}
 
int main() {
    int t, x, y, v, i, cas = 1;
    for (scanf("%d", &t); t--; ) {
        scanf("%d", &n);
        g.init(n);
        for (i = 1; i < n; i++) {
            scanf("%d %d %d", &x, &y, &v);
            g.addedge(x, y, v);
        }
        Solve();
        printf("Case %d: %d\n", cas++, ans);
    }
    return 0;
}
