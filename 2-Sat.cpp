/*
 * Author:  DreamHigh
 * Created Time:  2014/4/12 21:08:29
 * File Name: 2-Sat.cpp (HDU_4421_2Sat)
 * solve: 2-Sat.cpp
 */
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<string>
#include<map>
#include<stack>
#include<set>
#include<iostream>
#include<vector>
#include<queue>
//ios_base::sync_with_stdio(false);
//#pragma comment(linker, "/STACK:1024000000,1024000000")

using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define repf(i, a, b) for (int i = (a); i <= (b); ++i)
#define repd(i, a, b) for (int i = (a); i >= (b); --i)
#define clr(x) memset(x,0,sizeof(x))
#define sqr(x) ((x) * (x))
typedef long long LL;

const int INF = 1000000000;
const double eps = 1e-8;
const int maxn = 2*(500+10);
const int mod = 1000000000 + 7;
int n;
vector<int> g[maxn];
int pre[maxn], lowlink[maxn], sccno[maxn], dfs_clock, scc_cnt;
stack<int> S;
void dfs(int u) {
    pre[u] = lowlink[u] = ++dfs_clock;
    S.push(u);
    for(int i = 0; i < g[u].size(); i++)
    {
        int v = g[u][i];
        if(!pre[v]) 
        {
            dfs(v);
            lowlink[u] = min(lowlink[u], lowlink[v]);
        } else if(!sccno[v]) 
        {
            lowlink[u] = min(lowlink[u], pre[v]);
        }
    }
    if(lowlink[u] == pre[u]) {
        scc_cnt++;
        for(;;) {
            int x = S.top(); 
            S.pop();
            sccno[x] = scc_cnt;
            if(x == u) break;
        }
    }
}
void find_scc(int n){
    dfs_clock = scc_cnt = 0;
    memset(sccno, 0, sizeof(sccno));
    memset(pre, 0, sizeof(pre));
    for(int i = 0; i < 2*n; i++)
        if(!pre[i]) 
            dfs(i);
}
void init(int n){
    rep(i,0,2*n)  g[i].clear();
}
bool test(){
    rep(i,0,n)if(sccno[2*i] == sccno[2*i+1]) return false;
    return true;
}
int b[maxn][maxn];
int main() 
{
    //freopen("in.txt","r",stdin);
    while(scanf("%d",&n) == 1){
        init(maxn);
        rep(i,0,n) rep(j,0,n) scanf("%d",&b[i][j]);
        int flag = 1;
        rep(k,0,32){//枚举32位
            init(maxn);
            rep(i,0,n)
                rep(j,i+1,n){
                    if(i%2 == 0 && j%2 == 0){
                        if(b[i][j]&(1<<k)){//做与运算的结果为真
                            g[2*i].push_back(2*i+1);
                            g[2*j].push_back(2*j+1);
                        }else{//做与运算的结果为false
                            g[2*i+1].push_back(2*j);
                            g[2*j+1].push_back(2*i);
                        }
                    }else if(i%2 == 1 && j%2 == 1){
                        if(b[i][j] & (1<<k)){//做|运算的结果为真
                            g[2*i].push_back(2*j+1);
                            g[2*j].push_back(2*i+1);
                        }else{//做|运算的结果为false
                            g[2*i].push_back(2*j);
                            g[2*j].push_back(2*i);
                        }
                    }else{
                        if(b[i][j] &(1<<k)){//做^运算的结果为真
                            g[2*i].push_back(2*j+1);
                            g[2*j+1].push_back(2*i);
                            g[2*j].push_back(2*i+1);
                            g[2*i+1].push_back(2*j);
                        }else{//做^运算的结果为false
                            g[2*i].push_back(2*j);
                            g[2*j].push_back(2*i);
                            g[2*i+1].push_back(2*j+1);
                            g[2*j+1].push_back(2*i+1);
                        }
                    }
                }
            find_scc(n);
            flag = test();
            if(!flag){
                break;
            }
        }
        if(flag)cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
    return 0;
}
