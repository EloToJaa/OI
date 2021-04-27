#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (b); i >= (a); --i)
#define sz(x) (int)(x).size()
#define nwd __gcd
#define pb push_back
#define st first
#define nd second
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
#define deb if(0)
const int N = 1e6, NT = N + 2;
const int NTREE = 1048576;

vi V[NT];
int K[NT];
int A[NT], W[NT], P[NT];
int n, m, ntree;

struct node {
    ll sum, pref, suff, ans;
} T[2*NTREE+1];

node licz(node l, node r) {
    node res;
    res.sum = l.sum + r.sum;
    res.pref = max(l.pref, l.sum + r.pref);
    res.suff = max(r.suff, r.sum + l.suff);
    res.ans = max(max(l.ans, r.ans), l.suff + r.pref);
    return res;
}

node start(ll val) {
    node res;
    res.sum = val;
    res.pref = res.suff = res.ans = max((ll)0, val);
    return res;
}

void build() {
    ntree = 1;
    while(ntree < n) ntree <<= 1;
    FOR(i, 1, n) T[i + ntree - 1] = start(P[i]);
    FORD(v, 1, ntree - 1) T[v] = licz(T[v<<1], T[v<<1|1]);
}

void update(int pos, ll val) {
    pos += ntree - 1;
    T[pos] = start(val);
    pos >>= 1;
    while(pos) {
        T[pos] = licz(T[pos<<1], T[pos<<1|1]);
        pos >>= 1;
    }
}

pii wystapienia(int k) {
    int a = 0, b = 0;
    if(K[k] < sz(V[k])) a = V[k][K[k]];
    if(K[k] + 1 < sz(V[k])) b = V[k][K[k] + 1];
    return {a, b};
}

void wejscie() {
    cin>>n>>m;
    FOR(i, 1, n) {
        cin>>A[i];
    }
    FOR(i, 1, m) {
        cin>>W[i];
    }
    FOR(i, 1, n) {
        V[A[i]].pb(i);
    }
}

ll oblicz() {
    ll mx = 0, sum = 0;
    pii wys;
    FOR(i, 1, n) {
        wys = wystapienia(A[i]); // zwraca dwa ostatnie wystapienia liczby
        if(i == wys.st) P[i] = W[A[i]];
        if(i == wys.nd) P[i] = -W[A[i]];
        sum += P[i];
        mx = max(mx, sum);
    }
    build();
    FOR(i, 1, m) {
        K[i]++;
    }
    return mx;
}

void wyjscie(ll mx) {
    pii wys;
    FOR(i, 1, n) {
        wys = wystapienia(A[i]);
        K[A[i]]++;
        P[i] = 0;
        update(i, P[i]);
        if(wys.st != 0) {
            P[wys.st] = W[A[i]];
            update(wys.st, P[wys.st]);
        }
        if(wys.nd != 0) {
            P[wys.nd] = -W[A[i]];
            update(wys.nd, P[wys.nd]);
        }
        mx = max(mx, T[1].ans);
    }
    cout << mx << "\n";
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    wejscie();
    ll mx = 0;
    mx = oblicz();
    wyjscie(mx);
    return 0;
}