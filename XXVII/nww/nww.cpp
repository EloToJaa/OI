#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (a); i >= (b); --i)
#define pb push_back
#define st first
#define nd second
#define nwd __gcd
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int N = 1e5;
const ll INF = 1e18 + 1;

map<ll, pii> M;

ll nww(ll a, ll b) {
    if(a == -1) return b; 
    return a / nwd(a, b) * b;
}

ll liczNP(ll n) {
    n = n * 2 - 1;
    return n * (n + 1) * (n + 2);
}

ll liczP(ll n) {
    n = n * 2;
    return n * (n + 1) / 2 * (n + 2);
}

ll szukajNP(int p, int k, ll x) {
    bool f = 0;
    while(p < k) {
        ll sr = (p + k) / 2;
        ll s = liczNP(sr);
        if(x == s) {
            f = 1;
            k = sr;
        }
        else if(x < s)
            k = sr;
        else
            p = sr + 1;
    }
    if(f || liczNP(p) == x) return p * 2 - 1;
    return -1;
}

ll szukajP(int p, int k, ll x) {
    bool f = 0;
    while(p < k) {
        ll sr = (p + k) / 2;
        ll s = liczP(sr);
        if(x == s) {
            f = 1;
            k = sr;
        }
        else if(x < s)
            k = sr;
        else
            p = sr + 1;
    }
    if(f || liczP(p) == x) return p * 2;
    return -1;
}

ll obliczDla2(ll n) {
    ll a, b, c, d;
    a = 4 * n + 1;
    b = sqrt(a);
    c = b - 1;
    d = c / 2;
    if (b * b == a && c % 2 == 0) return d;
    return -1;
}

ll obliczDla3(ll n) {
    ll x, y;
    x = szukajNP(1, 5e5, n);
    y = szukajP(1, 1e6, n);
    return max(x, y);
}

void init() {
    ll wyn;
    FOR(i, 1, N) {
        wyn = nww( nww(i, i + 1), i + 2);
        if(wyn >= INF) continue;
        for(int j = i + 3; j < i + 50 && nww(wyn, j) < INF; ++j) {
            wyn = nww(wyn, j);
            if(M.count(wyn) == 0) M[wyn] = {i, j};
        }
    }
}

void ans(ll n) {
    pll wyn[5];
    ll x;
    FOR(i, 1, 3) wyn[i] = { INF, INF };
    if(M.count(n) != 0) wyn[1] = { M[n].st, M[n].nd };

    x = obliczDla3(n);
    if(x != -1) wyn[2] = { x, x + 2 };

    x = obliczDla2(n);
    if(x != -1) wyn[3] = { x, x + 1 };

    sort(wyn + 1, wyn + 4);
    if(wyn[1].st == INF) cout<<"NIE\n";
    else if(wyn[1].st == 2) cout<<"1 "<<wyn[1].nd<<"\n";
    else cout<<wyn[1].st<<" "<<wyn[1].nd<<"\n";
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int z;
    ll n;
    cin>>z;
    init();
    FOR(i, 1, z) {
        cin>>n;
        ans(n);
    }
    return 0;
}