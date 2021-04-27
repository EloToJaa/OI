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
const int N = 1e6, NT = N + 2;

vi V[NT], R[NT], order;
vector<pii> graf[NT];
int dir[NT], n, m, ans;
pii edge[NT];
bitset<NT> vis;

void addEdge(int a, int b, int k) {
    graf[a].pb({b, k});
    graf[b].pb({a, k});
    edge[k] = {a, b};
}

void dfs(int v) {
    vis[v] = true;
    TRAV(e, graf[v]) {
        int u = e.st, nr = e.nd;
        if(dir[nr] == 0) {
			if(v == edge[nr].st)
				dir[nr] = 1;
			else
				dir[nr] = 2;
			if(vis[u] == 0)
				dfs(u);
		}
    }
}

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

void wejscie() {
    int a, b;
    cin>>n>>m;
    FOR(i, 1, m) {
        cin>>a>>b;
        addEdge(a, b, i);
    }
}

void kierunki() {
    FOR(v, 1, n) {
        if(!vis[v]) dfs(v);
    }
    vis.reset();
}

void spojne() {
    FOR(i, 1, m) {
        int a = edge[i].st, b = edge[i].nd;
        if(dir[i] == 1) {
            V[a].pb(b);
            R[b].pb(a);
        }
        if(dir[i] == 2) {
            V[b].pb(a);
            R[a].pb(b);
        }
    }
    FOR(v, 1, n) {
        if(!vis[v]) dfs1(v);
    }
    reverse(ALL(order));
    vis.reset();
    TRAV(v, order) {
        if(!vis[v]) {
            ans++;
            dfs2(v);
        }
    }
}

void wyjscie() {
    cout<<ans<<"\n";
    FOR(i, 1, m) {
        cout<<(dir[i]==1? ">": "<");
    }
    cout<<"\n";
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    wejscie();
    kierunki();
    spojne();
    wyjscie();
    return 0;
}