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
const int N = 5e5, NT = N + 2;

vi V[NT];
bitset<NT> strajk, vis;
int S[NT], P[NT];

void dfs(int v, int p) {
    vis[v] = true;
    P[v] = p;
    S[v] = sz(V[v]) - 1;
    if(v == p) S[v]++;
    TRAV(u, V[v]) {
        if(!vis[u]) dfs(u, v);
    }
}

void addEdge(int a, int b) {
    V[a].pb(b);
    V[b].pb(a);
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, a, b, ans = 1;
    cin>>n;
    FOR(i, 1, n - 1) {
        cin>>a>>b;
        addEdge(a, b);
    }
    dfs(1, 1);
    cin>>m;
    FOR(i, 1, m) {
        cin>>a;
        if(a > 0) {
            strajk[a] = true;
            ans += S[a] - 1;
            if(a != 1) {
                S[P[a]]--;
                if(!strajk[P[a]]) ++ans;
            }
        }
        else {
            a *= -1;
            strajk[a] = false;
            ans -= S[a] - 1;
            if(a != 1) {
                S[P[a]]++;
                if(!strajk[P[a]]) --ans;
            }
        }
        cout<<ans<<"\n";
    }
    return 0;
}