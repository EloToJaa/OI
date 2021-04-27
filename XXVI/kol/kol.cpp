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
typedef pair<ll, int> pli;
typedef vector<int> vi;
#define deb if(0)
const int N = 1e5, NT = N + 2;
const ll INF = (ll)1e18 + 2;
const int LOG = 17;

vector<pii> V[NT];
vi P[NT], TYPY[NT];
int ANC[NT][LOG + 1], PRE[NT], POST[NT], idx;
int C[NT];
ll D[NT], DIST[NT], WAR[NT][LOG + 1], ANS[NT];
priority_queue<pli> Q;
bitset<NT> vis;

struct Zapytanie {
    int a, b, t;
} QUERY[NT];

void Ancestors(int v, int p, ll dist) {
    ANC[v][0] = p;
    FOR(k, 1, LOG) {
        ANC[v][k] = ANC[ ANC[v][k - 1] ][k - 1];
    }
    idx++;
    PRE[v] = idx;
    DIST[v] = dist;
    TRAV(x, V[v]) {
        auto [u, c] = x;
        if(u != p) Ancestors(u, v, dist + c);
    }
    POST[v] = idx;
}

bool Przodek(int a, int b) { // czy a jest przodkiem b
    return PRE[a] <= PRE[b] and PRE[b] <= POST[a];
}

int Lca(int a, int b) {
    if(Przodek(a, b)) return a;
    if(Przodek(b, a)) return b;
    FORD(k, 0, LOG) {
        if(!Przodek(ANC[a][k], b))
            a = ANC[a][k];
    }
    return ANC[a][0];
}

ll Skacz(int a, int b) {
    // Skacz z a do b
    ll ans = INF;
    FORD(k, 0, LOG) {
        if(!Przodek(ANC[a][k], b)) {
            ans = min(ans, WAR[a][k]);
            a = ANC[a][k];
        }
    }
    ans = min(ans, WAR[a][0]);
    return ans;
}

ll WykonajSkoki(int a, int b) {
    // szukaj min na drodze z a do b
    ll ans = INF;
    if(a == b) return D[a];
    int lca = Lca(a, b);
    if(a != lca) ans = min(ans, Skacz(a, lca));
    if(b != lca) ans = min(ans, Skacz(b, lca));
    return ans;
}

void Dijkstra(int t, int n) {
    FOR(v, 1, n) D[v] = INF;
    // wrzucamy wszystkie restauracje typu t na kolejke
    TRAV(v, P[t]) {
        D[v] = 0;
        Q.push({0, v});
    }
    while(!Q.empty()) {
        int v = Q.top().nd;
        ll dist = -Q.top().st;
        Q.pop();
        if(dist > D[v])
            continue;
        TRAV(x, V[v]) {
            auto [u, c] = x;
            if(D[v] + c < D[u]) {
                D[u] = D[v] + c;
                Q.push({-D[u], u});
            }
        }
    }
}

ll Dist(int a, int b) {
    // liczy odleglosc pomiedzy a i b w drzewie znajdujac ich lca
    if(a == b) return 0;
    int lca = Lca(a, b);
    return DIST[a] + DIST[b] - 2 * DIST[lca];
}

void Malo(int k) {
    // malo restauracji tego typu
    auto [a, b, t] = QUERY[k];
    ll ans = INF, dist;
    TRAV(v, P[t]) {
        dist = Dist(a, v) + Dist(b, v);
        ans = min(ans, dist);
    }
    ANS[k] = ans;
}

void Duzo(int k, int n) {
    // duzo restauracji tego typu
    if(vis[k]) return;
    int t = QUERY[k].t;
    // wyznaczanie najmniejszych odleglosci od wszystkich restauracji typu t
    Dijkstra(t, n);
    // wyznaczanie minimow na drodze przy uzyciu skokow lca
    FOR(v, 1, n) WAR[v][0] = min(D[v], D[ANC[v][0]]);
    FOR(j, 1, LOG)
		FOR(v, 1, n)
			WAR[v][j] = min(WAR[v][j - 1], WAR[ ANC[v][j - 1] ][j - 1]);
    
    TRAV(i, TYPY[t]) {
        // odpowiadamy na wszystkie zapytania o tego typu restauracje
        vis[i] = true;
        int a = QUERY[i].a, b = QUERY[i].b;
        ANS[i] = Dist(a, b) + 2 * WykonajSkoki(a, b);
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, r, q, t, a, b, c;
    cin>>n>>r;
    FOR(v, 1, n) {
        cin>>t;
        P[t].pb(v);
        C[t]++;
    }
    FOR(i, 1, n - 1) {
        cin>>a>>b>>c;
        V[a].pb({b, c});
        V[b].pb({a, c});
    }
    Ancestors(1, 1, 0);
    cin>>q;
    int root = sqrt(n);
    FOR(i, 1, q) {
        cin>>QUERY[i].a>>QUERY[i].b>>QUERY[i].t;
        TYPY[QUERY[i].t].pb(i);
    }
    FOR(i, 1, q) {
        t = QUERY[i].t;
        if(C[t] == 0) ANS[i] = -1;
        else if(C[t] <= root) Malo(i);
        else Duzo(i, n);
    }
    FOR(i, 1, q) cout<<ANS[i]<<"\n";
    return 0;
}