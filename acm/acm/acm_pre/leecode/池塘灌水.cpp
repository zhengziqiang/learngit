/*==============================================================================
    > File Name: 池塘灌水.cpp
    > Author: zzq
    > Mail: zhengziqiang1@gmail.com 
    > Created Time: 2016年09月26日 星期一 20时53分40秒
 ==========================================================================*/

#include<iostream>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <stack>
#include <vector>
#include <memory.h>
#include <set>
#include <string.h>
#include <list>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <queue>
#define ll long long
#define forn(i,n) for(int i=0;i<n;++i)
#define rep(i,n) for(int i=1;i<=n;++i)
#define repc(i,l,r) for(int i=l;i<=r;++i)
#define mp(a,b) make_pair(a,b)
#define llf long double
#define pii pair<int,int>
using namespace std; 
int l[200005];
int r[200005];
pii query[200005];//
int dist[200005];
int dsu[100005];
pii stk[200005];//
int merge(int a, int b) {
    if (!a)return b;
    else if (!b)return a;
    if (query[a].first > query[b].first)swap(a, b);
    r[a] = merge(r[a], b);
    if (dist[r[a]] > dist[l[a]])swap(l[a], r[a]);
    if (!r[a]) dist[a] = 0;
    else dist[a] = dist[r[a]] + 1;
    return a;
}
struct Node {
    int qu, h;
    int f, g;
    void get(int hgt) {
        int nw = 0;
        int mx = 0;
        int fmr = -1;
        int tol = 0;
        int nf;
        while (qu&&query[qu].first<hgt) {
            stk[tol++] = query[qu];
            if (query[qu].second == 0) ++nw;
            qu = merge(l[qu], r[qu]);
        }
        nf = nw;
        forn(i, tol) {
            if (stk[i].first != fmr) {
                mx = max(mx, nw);
                fmr = stk[i].first;
            }
            if (stk[i].second)++nw;
            else --nw;
        }
        mx = max(mx, nw);
        f = max(f+nf, g + mx);//not overflow
        g += nw;
        h = hgt;
    }
}nds[100005];

int getgp(int u) {
    return dsu[u] = (dsu[u] != u ? getgp(dsu[u]) : u);
}
void mrg(int u, int v, int h) {
    u = getgp(u);
    v = getgp(v);
    if (nds[u].h < h) {
        nds[u].get(h);
    }
    if (nds[v].h < h) {
        nds[v].get(h);
    }
    dsu[v] = u;
    nds[u].qu = merge(nds[u].qu, nds[v].qu);
    nds[u].f += nds[v].f;
    nds[u].g += nds[v].g;
}
int n, m;
pii board[100005];//
void solve() {
    memset(l, 0, sizeof(l));
    memset(r, 0, sizeof(r));
    memset(dist, 0, sizeof(dist));
    memset(nds, 0, sizeof(nds));
    memset(board, 0, sizeof(board));
    memset(query, 0, sizeof(query));
    cin >> n >> m;
    rep(i, n)dsu[i] = i;
    rep(i, n - 1) {
        scanf("%d", &board[i].first);
        board[i].second = i;
    }
    sort(board + 1, board + n);

    int S = 0;
    rep(i, m) {
        int x;
        scanf("%d%d%d", &x, &query[i].first, &query[i].second);
        if (query[i].second) ++S;
        nds[x].qu = merge(nds[x].qu, i);
    }
    rep(i, n - 1) {
        mrg(board[i].second, board[i].second + 1, board[i].first);
    }
    int rt = getgp(1);
    nds[rt].get(1e9 + 100);
    cout << nds[rt].f << endl;
}
int main(){
    //freopen("abc.txt", "r", stdin);
    int T;
    cin >> T;
    rep(t, T) {
        printf("Case #%d: ", t);
        solve();
    }
    return 0;
}
