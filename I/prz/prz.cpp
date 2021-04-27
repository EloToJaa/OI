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
const int N = 1e5, NT = N + 2;

class Solution {
    vi V[NT], R[NT], order;
    int T[NT], IN[NT], OUT[NT];
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
        TRAV(u, R[v]) {
            if(!vis[u]) dfs2(u);
        }
    }
    public:
    void addEdge(int a, int b) {
        V[a].pb(b);
        R[b].pb(a);
    }
    void addNode(int k, int val) {
        T[k] = val;
    }
    bool cykl(int n) {
        FOR(v, 1, n) {
            if(!vis[v]) dfs1(v);
        }
        reverse(ALL(order));
        vis.reset();
        int m = 0;
        TRAV(v, order) {
            if(!vis[v]) {
                ++m;
                dfs2(v);
            }
        }
        vis.reset();
        return (n != m);
    }
    int solve(int n) {
        TRAV(v, order) {
            TRAV(u, R[v]) {
                IN[v] = max(IN[v], IN[u]);
            }
            IN[v] += T[v];
        }
        reverse(ALL(order));
        TRAV(v, order) {
            TRAV(u, V[v]) {
                OUT[v] = max(OUT[v], OUT[u]);
            }
            OUT[v] += T[v];
        }
        int ans = 0;
        FOR(i, 1, n) {
            ans = max(ans, IN[i] + OUT[i] - T[i]);
        }
        return ans;
    }
    bool add(int k, int t, int val) {
        return (IN[k] + OUT[k] - T[k] + t > val);
    }
};

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q, t, k, a;
    Solution solution;
    cin>>n;
    FOR(i, 1, n) {
        cin>>t>>k;
        solution.addNode(i, t);
        FOR(j, 1, k) {
            cin>>a;
            solution.addEdge(a, i);
        }
    }
    if(solution.cykl(n)) {
        cout<<"CYKL\n";
        return 0;
    }
    cin>>q;
    int ans = solution.solve(n);
    cout<<ans<<"\n";
    FOR(i, 1, q) {
        cin>>k>>t;
        cout<<(solution.add(k, t, ans) ? "TAK" : "NIE")<<"\n";
    }
    return 0;
}