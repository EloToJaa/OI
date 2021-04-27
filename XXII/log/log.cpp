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
const int N = 1e6, NT = N + 2;
const int NTREE = 1048576;

struct queries {
    char c;
    int a, b;
} QUERY[NT];
int C[NT], U[NT], m;
pli T[NTREE * 2 + 1];

pli operator+ (const pli &a, const pli &b) {
    return {a.st + b.st, a.nd + b.nd};
}

int search(int s) {
    int x, l = 1, r = m;
    while(l < r) {
        x = l + ((r - l)>>1);
        if(C[x] >= s) r = x;
        else l = x + 1;
    }
    return l;
}

void update(int v, pli val) {
    v += NTREE - 1;
    T[v] = T[v] + val;
    v >>= 1;
    while(v) {
        T[v] = T[lc] + T[rc];
        v >>= 1;
    }
}

pli query(int l, int r) {
    l += NTREE - 1; r += NTREE - 1;
    pli ans = T[l];
    if(r > l) ans = ans + T[r];
    while(r - l > 1) {
        if(!(l&1)) ans = ans + T[l + 1];
        if(r&1) ans = ans + T[r - 1];
        l >>= 1; r >>= 1;
    }
    return ans;
}

void solve1(int kierowca, int km) { // update
    int uprawnienia = U[kierowca];
    if(uprawnienia) update(search(uprawnienia), {-uprawnienia, -1});
    U[kierowca] = km, uprawnienia = km;
    update(search(uprawnienia), {uprawnienia, 1});
}

void solve2(int ciezarowki, int km) { // zapytanie
    pli ans = query(0, search(km));
    ll mozliwosc = ans.st + (T[1].nd - ans.nd) * km;
    ll potrzeba = ciezarowki * km;
    cout<<(mozliwosc >= potrzeba? "TAK": "NIE")<<"\n";
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, a, b;
    char c;
    cin>>n>>m;
    FOR(i, 1, m) {
        cin>>c>>a>>b;
        C[i] = b;
        QUERY[i] = {c, a, b};
    }
    sort(TAB(C, 1, m));
    FOR(i, 1, m) {
        if(QUERY[i].c == 'U') solve1(QUERY[i].a, QUERY[i].b);
        if(QUERY[i].c == 'Z') solve2(QUERY[i].a, QUERY[i].b);
    }
    return 0;
}