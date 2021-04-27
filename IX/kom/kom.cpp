#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (b); i >= (a); --i)
#define TRAV(x,T) for(auto& x: (T))
#define ALL(T) T.begin(), T.end()
#define TAB(T,a,b) (T)+a, (T)+((b)+1)
#define VAR(x) #x<<" = "<<x<<" " 
#define sz(x) (int)(x).size()
#define nwd __gcd
#define pb push_back
#define st first
#define nd second
#define lc (v<<1)
#define rc (v<<1|1)
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
#define deb if(0)
const int N = 3e4, NT = N + 2;
const int LOG = 15; // log n

int anc[NT][LOG + 1], pre[NT], post[NT], gle[NT], idx;
vi V[NT];

void ancestors(int v, int p) {
    anc[v][0] = p;
    FOR(k, 1, LOG)
        anc[v][k] = anc[ anc[v][k - 1] ][k - 1];
    idx++;
    pre[v] = idx;
    TRAV(u, V[v]) {
        if(u != p) {
            gle[u] = gle[v] + 1;
            ancestors(u, v);
        }
    }
    post[v] = idx;
}

bool przodek(int a, int b) { // czy a jest przodkiem b
    return pre[a] <= pre[b] and pre[b] <= post[a];
}

int LCA(int a, int b) {
    if(przodek(a, b)) return a;
    if(przodek(b, a)) return b;
    FORD(k, 0, LOG) {
        if(!przodek(anc[a][k], b))
            a = anc[a][k];
    }
    return anc[a][0];
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, a, b, ans = 0;
    cin>>n;
    FOR(i, 1, n-1) {
        cin>>a>>b;
        V[a].pb(b);
        V[b].pb(a);
    }
    ancestors(1, 1);
    int curr, prev = 1, lca;
    cin>>m;
    FOR(i, 1, m) {
        cin>>curr;
        lca = LCA(prev, curr);
        ans += (gle[curr] - gle[lca]) + (gle[prev] - gle[lca]);
        prev = curr;
    }
    cout<<ans<<"\n";
    return 0;
}