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
const int N = 2e5, NT = N + 2;
const int M = 1e6, MT = M + 2;
const int NTREE = 262144;
const int INF = 2e9 + 2;

pii A[NT];
int ntree;

struct dane {
    bool xx, xy, yx, yy;
} T[NTREE * 2 + 1];

dane Lacz(int l, int r) {
    if(l >= ntree) {
        // laczenie z liscmi
        l = l - ntree + 1;
        r = l + 1;
        return {
            A[l].st <= A[r].st,
            A[l].st <= A[r].nd,
            A[l].nd <= A[r].st,
            A[l].nd <= A[r].nd,
        };
    }
    // laczenie z reszta
    return {
        
    };
}

void Build(int n) {
    ntree = 1; while(ntree < n) ntree <<= 1;
    FOR(i, n + 1, ntree) A[i] = {INF, INF};
    FORD(v, 1, ntree - 1) T[v] = Lacz(lc, rc);
}

void Update(int v) {
    v += ntree - 1;
    v >>= 1;
    while(v) {
        T[v] = Lacz(lc, rc);
        v >>= 1;
    }
}

void Answer() {
    bool b = T[1].xx or T[1].xy or T[1].yx or T[1].yy;
    cout<<(b? "TAK": "NIE")<<"\n";
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, l, r;
    cin>>n;
    FOR(i, 1, n) cin>>A[i].st>>A[i].nd;
    cin>>m;
    FOR(i, 1, m) {
        cin>>l>>r;
        swap(A[l], A[r]);
        Update(l); Update(r);
        Answer();
    }
    return 0;
}