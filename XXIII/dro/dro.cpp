#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (b); i >= (a); --i)
#define TRAV(x,T) for(auto& x: (T))
#define ALL(T) T.begin(), T.end()
#define TAB(T,a,b) (T)+a, (T)+((b)+1)
#define VAR(x) #x<<" = "<<x<<" " 
#define SZ(x) (int)(x).size()
#define Nwd __gcd
#define pb push_back
#define st first
#define nd second
#define lc (v<<1)
#define rc (v<<1|1)
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
#define deb if(1)
const int N = 5e5, NT = N + 2;
const int M = 1e6, MT = M + 2;

int Spojna[NT], Size[NT], DP1[NT], DP2[NT];
vi Graf[NT], Odw[NT], Graf1[NT], Graf2[NT], Order, Ans;
bitset<NT> Vis;

void Dag1(int v) {
    Vis[v] = true;
    TRAV(u, Graf[v]) if(!Vis[u]) Dag1(u);
    Order.pb(v);
}

void Dag2(int v, int nr) {
    Vis[v] = true;
    Spojna[v] = nr;
    TRAV(u, Odw[v]) if(!Vis[u]) Dag2(u, nr);
}

int CreateDag(int n) {
    FOR(v, 1, n) if(!Vis[v]) Dag1(v);
    Vis.reset();
    reverse(ALL(Order));
    int nr = 0;
    TRAV(v, Order) if(!Vis[v]) {
        ++nr;
        Dag2(v, nr);
    }
    FOR(v, 1, n) {
        Odw[v].clear();
        TRAV(u, Graf[v]) if(Spojna[v] != Spojna[u]) {
            Graf1[Spojna[v]].pb(Spojna[u]);
            Graf2[Spojna[u]].pb(Spojna[v]);
        }
        Graf[v].clear();
        Size[Spojna[v]]++;
    }
    Vis.reset();
    Order.clear();
    return nr;
}

void TopS1(int v) {
    Vis[v] = true;
    TRAV(u, Graf1[v]) if(!Vis[u]) TopS1(u);
    Order.pb(v);
}

void TopSort1(int n) {
    FOR(v, 1, n) if(!Vis[v]) TopS1(v);
    //reverse(ALL(Order));
    Vis.reset();
}

void TopS2(int v) {
    Vis[v] = true;
    TRAV(u, Graf2[v]) if(!Vis[u]) TopS2(u);
    Order.pb(v);
}

void TopSort2(int n) {
    FOR(v, 1, n) if(!Vis[v]) TopS2(v);
    //reverse(ALL(Order));
    Vis.reset();
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, a, b;
    cin>>n>>m;
    FOR(i, 1, m) {
        cin>>a>>b;
        Graf[a].pb(b);
        Odw[b].pb(a);
    }
    int dag_size = CreateDag(n);
    FOR(v, 1, n) {
        DP1[v] = Size[v];
        DP2[v] = Size[v];
    }
    TopSort1(dag_size);
    TRAV(v, Order) TRAV(u, Graf2[v]) {
        cout<<v<<" "<<u<<"\n";
        DP1[u] += DP1[v];
    }
    deb {
        FOR(v, 1, n) cout<<DP1[Spojna[v]]<<" ";
        cout<<"\n\n";

        FOR(v, 1, n) cout<<Spojna[v]<<" ";
        cout<<"\n\n";
    }
    Order.clear();
    TopSort2(dag_size);
    TRAV(v, Order) TRAV(u, Graf1[v]) {
        cout<<v<<" "<<u<<"\n";
        DP2[u] += DP2[v];
    }
    deb {
        FOR(v, 1, n) cout<<DP2[Spojna[v]]<<" ";
        cout<<"\n\n";
    }
    FOR(v, 1, n) if(DP1[Spojna[v]] + DP2[Spojna[v]] - Size[Spojna[v]] >= n) Ans.pb(v);
    cout<<SZ(Ans)<<"\n";
    TRAV(v, Ans) cout<<v<<" ";
    cout<<"\n";
    return 0;
}