#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (a); i >= (b); --i)
#define TRAV(x,T) for(auto& (x): (T))
#define ALL(x) x.begin(), x.end()
#define TAB(x,n) (x)+1, (x)+((n)+1)
#define sz(x) (int)(x).size()
#define nwd __gcd
#define pb push_back
#define pf push_front
#define st first
#define nd second
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
const int N = 5e3 + 2;
const int INF = 1e9 + 2;

vi V[N];

void addEdge(int a, int b) {
    V[a].pb(b);
}

int depth[N], D[N];
bitset<N> vis;

void dfs(int v, int p) {
    vis[v] = true;
    depth[v] = depth[p] + 1;
    D[depth[v]]++;
    TRAV(u, V[v]) {
        if(!vis[u]) dfs(u, v);
    }
}

int solve(int n) {
    int ans = INF;
    FOR(i, 1, *max_element(TAB(depth, n)) - 1)
        ans = min(ans, D[i]);
        //cout<<D[i]<<" ";
    //cout<<"\n";
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, a;
    cin>>n;
    FOR(i, 1, n - 1) {
        cin>>m;
        FOR(j, 1, m) {
            cin>>a;
            addEdge(i, a);
        }
    }
    depth[1] = -1;
    dfs(1, 1);
    cout<<solve(n)<<"\n";
    return 0;
}