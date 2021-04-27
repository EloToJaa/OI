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
#define lc (v<<1)
#define rc (v<<1|1)
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
#define deb if(0)
const int N = 6e4, NT = N + 2;
const int NTREE = 65536;

int T[NTREE * 2 + 2], lazy[NTREE * 2 + 2];

void push(int v) {
    T[lc] += lazy[v];
    lazy[lc] += lazy[v];
    T[rc] += lazy[v];
    lazy[rc] += lazy[v];
    lazy[v] = 0;
}

void update(int v, int tl, int tr, int l, int r, int val) {
    if (l <= tl and tr <= r) {
        T[v] += val;
        lazy[v] += val;
        return;
    }
    push(v);
    int tm = (tl + tr) / 2;
    if(l <= tm) update(lc, tl, tm, l, r, val);
    if(r > tm) update(rc, tm+1, tr, l, r, val);
    T[v] = max(T[lc], T[rc]);
}

int query(int v, int tl, int tr, int l, int r) {
    if (l <= tl and tr <= r) return T[v];
    push(v);
    int tm = (tl + tr) / 2, a = 0, b = 0;
    if(l <= tm) a = query(lc, tl, tm, l, r);
    if(r > tm) b = query(rc, tm+1, tr, l, r);
    return max(a, b);
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, q, l, r, k;
    cin>>n>>m>>q;
    FOR(i, 1, q) {
        cin>>l>>r>>k;
        r--;
        if(query(1, 1, n, l, r) + k <= m) {
            cout<<"T\n";
            update(1, 1, n, l, r, k);
        }
        else cout<<"N\n";
    }
    return 0;
}