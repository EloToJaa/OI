#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (b); i >= (a); --i)
#define TRAV(x,T) for(auto& (x): (T))
#define ALL(T) T.begin(), T.end()
#define TAB(T,a,b) (T)+a, (T)+((b)+1)
#define VAR(x) #x<<" = "<<x<<" " 
#define sz(x) (int)(x).size()
#define nwd __gcd
#define pb push_back
#define st first
#define nd second
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
#define deb if(0)
const int N = 5e4, NT = N + 2;

class Solution {
    vi V[NT], R[NT], D[NT], order;
    int nr[NT], val[NT], ans[NT], m;
    bitset<NT> vis;
    void dfs1(int v) {
        vis[v] = true;
        TRAV(u, V[v]) {
            if(!vis[u]) dfs1(u);
        }
        order.pb(v);
    }
    void dfs2(int v) {
        vis[v] = true;
        nr[v] = m;
        TRAV(u, R[v]) {
            if(!vis[u]) dfs2(u);
        }
    }
    void dfs3(int v) {
        vis[v] = true;
        TRAV(u, D[v]) {
            if(!vis[u]) dfs3(u);
        }
        order.pb(v);
    }
    void createDAG(int n) {
        // sortowanie topologiczne
        FOR(v, 1, n) {
            if(!vis[v]) dfs1(v);
        }
        vis.reset();
        reverse(ALL(order));
        // tworzenie silnie spojnych
        TRAV(v, order) {
            if(!vis[v]) {
                ++m;
                dfs2(v);
            }
        }
        vis.reset();
        order.clear();
        // liczenie wartosci dla DAGow
        FOR(v, 1, n) {
            val[nr[v]]++;
        }
        FOR(i, 1, m) {
            val[i]--;
        }
        // tworzenie krawedzi DAGa
        FOR(v, 1, n) {
            TRAV(u, V[v]) {
                if(nr[v] != nr[u]) D[nr[v]].pb(nr[u]);
            }
        }
        // sortowanie post-order DAGa
        FOR(v, 1, m) {
            if(!vis[v]) dfs3(v);
        }
    }
    public:
    void addEdge(int a, int b) {
        V[a].pb(b);
        R[b].pb(a);
    }
    void solve(int n) {
        createDAG(n);
        int u = 1;
        TRAV(v, order) {
            if(sz(D[v]) == 0) ans[v] = val[v];
            else {
                ans[v] = val[v];
                TRAV(u, D[v]) {
                    ans[v] += ans[u] + 1;
                }
            }
            u = v;
        }
        FOR(i, 1, n) {
            cout<<ans[nr[i]]<<"\n";
        }
    }
};

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, a, b;
    cin>>n>>m;
    Solution solution;
    FOR(i, 1, m) {
        cin>>a>>b;
        solution.addEdge(a, b);
    }
    solution.solve(n);
    return 0;
}