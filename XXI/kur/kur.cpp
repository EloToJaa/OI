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
const int NTREE = 524288;

int A[NT], K[NT];
map<pii, int> M;
vi V[NT];

struct node {
    int w, k;
} T[2*NTREE+2];

struct pytanie {
    int l, r, k, idx;
} P[NT];

node licz(node l, node r) {
    if(l.w == 0) return r;
    if(r.w == 0) return l;
    if(l.w == r.w) return {l.w, l.k + r.k};
    if(l.k > r.k) return {l.w, l.k - r.k};
    return {r.w, r.k - l.k};
}

node start(int val) {
    return {val, 1};
}

void build(int v, int tl, int tr) {
    if(tl == tr) {
        T[v] = start(A[tl]);
        return;
    }
    int tm = tl + ((tr - tl) >> 1);
    build(v<<1, tl, tm);
    build(v<<1|1, tm + 1, tr);
    T[v] = licz(T[v<<1], T[v<<1|1]);
}

node query(int v, int tl, int tr, int l, int r) {
    if(l <= tl and r >= tr) return T[v];
    int tm = tl + ((tr - tl) >> 1);
    node a = start(0), b = start(0);
    if(l <= tm) a = query(v<<1, tl, tm, l, r);
    if(r > tm) b = query(v<<1|1, tm+1, tr, l, r);
    return licz(a, b);
}

bool lider(int k, int l, int r) {
    int ile = M[{r, k}] - M[{l - 1, k}];
    int dl = r - l + 1;
    return (ile > dl / 2);
}

void liderzy(int n, int m) {
    // tworzenie drzewa przedzialowego dla kandrydatow
    build(1, 1, n);
    // wyszukiwanie kandydata na przedziale dla kazdego zapytania
    FOR(i, 1, m) {
        P[i].k = query(1, 1, n, P[i].l, P[i].r).w;
        V[P[i].l - 1].pb(P[i].k);
        V[P[i].r].pb(P[i].k);
    }
    // zliczanie ile jest kandydata k na prefiksie (1, i)
    FOR(i, 0, n) {
        K[A[i]]++;
        TRAV(k, V[i]) M[{i, k}] = K[k];
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, a, b;
    cin>>n>>m;
    FOR(i, 1, n) {
        cin>>A[i];
    }
    FOR(i, 1, m) {
        cin>>P[i].l>>P[i].r;
        P[i].idx = i;
    }
    liderzy(n, m);
    FOR(i, 1, m) {
        if(lider(P[i].k, P[i].l, P[i].r)) cout<<P[i].k<<"\n";
        else cout<<"0\n";
    }
    cout<<"\n";
    return 0;
}