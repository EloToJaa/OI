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
const ll MOD = 1e9 + 7;

int REP[NT], ILE[NT];
ll ANS[NT], X[NT];

void Init(int n) {
    FOR(i, 1, n) {
        REP[i] = i;
        ILE[i] = 1;
        ANS[i] = 1;
    }
}

void Union(int a, int b, int w) {
    if(ILE[a] > ILE[b]) swap(a, b);
    REP[a] = b;
    ILE[b] += ILE[a];
    ll x = (ANS[a] + w - X[a]) % MOD;
    ll y = (ANS[b] + w - X[b]) % MOD;
    ANS[b] = x * y % MOD;
    X[b] = w;
}

int Find(int a) {
    if(REP[a] != a) REP[a] = Find(REP[a]);
    return REP[a];
}

struct Edge {
    int a, b, w;
};
vector<Edge> K;

void Kruskal(int n) {
    Init(n);
    sort(ALL(K), [](const Edge &a, const Edge &b) {
        return a.w < b.w;
    });
    int fa, fb;
    TRAV(kraw, K) {
        auto [a, b, w] = kraw;
        fa = Find(a);
        fb = Find(b);
        if(fa != fb) Union(fa, fb, w);
    }
}

int Conv(int a, int b, int m) {
    return (a - 1) * m + b;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, H, h;
    cin>>n>>m>>H;
    if(m > 1) {
        FOR(i, 1, n) {
            FOR(j, 1, m - 1) {
                cin>>h;
                K.pb({Conv(i, j, m), Conv(i, j + 1, m), h});
            }
        }
    }
    if(n > 1) {
        FOR(i, 1, n - 1) {
            FOR(j, 1, m) {
                cin>>h;
                K.pb({Conv(i, j, m), Conv(i + 1, j, m), h});
            }
        }
    }
    Kruskal(n * m);
    int k = Find(1);
    ll ans = ANS[k] + H - X[k];
    ans %= MOD;
    cout<<ans<<"\n";
    return 0;
}