#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (b); i >= (a); --i)
#define TRAV(x,T) for(auto& x: (T))
#define ALL(T) T.begin(), T.end()
#define TAB(T,a,b) (T)+a, (T)+((b)+1)
#define VAR(x) #x<<" = "<<x<<" " 
#define SZ(x) (int)(x).size()
#define nwd __gcd
#define pb push_back
#define st first
#define nd second
#define pref first
#define suff second
#define lc (v<<1)
#define rc (v<<1|1)
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
#define deb if(0)
const int N = 5e5, NT = N + 2;
const int M = 1e6, MT = M + 2;
const int NTREE = 524288;
const int INF = 2e9 + 2;

vi Graf[NT], Order;
vector<pii> Kraw;
int Pos[NT], Dist[NT], End[NT], Start[NT], ntree;
pii Max[NT];
bitset<NT> Vis;
int T[NTREE * 2 + 1];

int Query(int v) {
    v += ntree - 1;
    int ans = 0;
    while(v > 0) {
        ans = max(ans, T[v]);
        v >>= 1;
    }
    return ans;
}

void Update(int l, int r, int val) {
    if(l > r) return;
    l += ntree - 1; r += ntree - 1;
    T[l] = max(T[l], val); T[r] = max(T[r], val);
    while(r - l > 1) {
        if(!(l&1)) T[l + 1] = max(T[l + 1], val);
        if(r&1) T[r - 1] = max(T[r - 1], val);
        l >>= 1; r >>= 1;
    }
}

void TopSort(int v) {
    Vis[v] = true;
    TRAV(u, Graf[v]) if(!Vis[u]) TopSort(u);
    Order.pb(v);
}

void Init(int n) {
    // Sortowanie topologiczne
    FOR(v, 1, n) if(!Vis[v]) TopSort(v);
    reverse(ALL(Order));
    int pos = 1;
    TRAV(v, Order) Pos[v] = pos++;
    // Sciezki startujace i wychodzace z wierzcholka
    int v;
    FOR(i, 1, n) {
        v = Order[i - 1];
        TRAV(u, Graf[v]) End[u] = max(End[u], End[v] + 1);
    }
    FORD(i, 1, n) {
        v = Order[i - 1];
        TRAV(u, Graf[v]) Start[v] = max(Start[v], Start[u] + 1);
    }
    FOR(i, 1, n) {
        v = Order[i - 1];
        Max[i].pref = max(Max[i - 1].pref, End[i]);
    }
    FORD(i, 1, n) {
        v = Order[i - 1];
        Max[i].suff = max(Max[i + 1].suff, Start[i]);
    }
    // Drzewo przedzialowe
    ntree = 1; while(ntree < n) ntree <<= 1;
    int u, dist;
    TRAV(kraw, Kraw) {
        v = kraw.st, u = kraw.nd;
        dist = End[v] + Start[u] + 1;
        Update(Pos[v] + 1, Pos[u] - 1, dist);
    }
}

void Solve(int n) {
    pii ans = {INF, -1}, val = {0, 0};
    FOR(i, 1, n) {
        val = {max(max(Max[Pos[i] - 1].pref, Max[Pos[i] + 1].suff), Query(Pos[i])), i};
        ans = min(ans, val);
    }
    cout<<ans.nd<<" "<<ans.st<<"\n";
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, a, b;
    cin>>n>>m;
    FOR(i, 1, m) {
        cin>>a>>b;
        Graf[a].pb(b);
        Kraw.pb({a, b});
    }
    Init(n);
    Solve(n);
    return 0;
}