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
const int N = 3e5, NT = N + 2;
const int NTREE = 524288 * 2 + 2;
const int M = 5e5, MT = M + 2;

struct dane {
    int l, r, s, a; // lewa granica przedzialu, srodek, prawa granica, sila w srodku, roznica ciagu arytmetycznego
} maszt[MT];
ll T[NTREE];
pll lazy[NTREE];

ll ciag(ll first, ll last, ll len) { // zwraca sume ciagu dla pierwszego elementu first, ostatniego elementu last i dlugosci ciagu len
    return (first + last) * len / 2;
}

void push(int v, ll len) { // first = lazy[v].st, last = lazy[v].nd
    ll diff = (lazy[v].nd - lazy[v].st) / (len - 1);
    ll mid = lazy[v].st + (len/2-1) * diff;
    T[lc] += ciag(lazy[v].st, mid, len/2);
    T[rc] += ciag(mid + diff, lazy[v].nd, len/2);
    lazy[lc].st += lazy[v].st; lazy[lc].nd += mid;
    lazy[rc].st += mid + diff; lazy[rc].nd += lazy[v].nd;
    lazy[v] = {0, 0};
}

ll query(int v, int tl, int tr, int l, int r) { // dlugosc obecnego przedzialu = tr-tl+1
    if (l <= tl and tr <= r) return T[v];
    int tm = (tl + tr) / 2;
    push(v, tr-tl+1); // spychanie lazy[v] do synow
    ll a = 0, b = 0;
    if(l <= tm) a = query(lc, tl, tm, l, r);
    if(r > tm) b = query(rc, tm+1, tr, l, r);
    T[v] = T[lc] + T[rc] + ciag(lazy[v].st, lazy[v].nd, tr-tl+1); // update wierzcholka
    return a + b;
}

ll diff;
void update(int v, int tl, int tr, int l, int r, ll first, ll last) {
    if (l <= tl and tr <= r) {
        T[v] += ciag(first, last, tr-tl+1);
        lazy[v].st += first; lazy[v].nd += last;
        return;
    }
    int tm = (tl + tr) / 2;
    push(v, tr-tl+1); // spychanie lazy[v] do synow
    if(l <= tm and r > tm) { // dzielenie ciagu i przedzialu odpowiedzi
        ll mid = first + (tm-l) * diff;
        update(lc, tl, tm, l, tm, first, mid);
        update(rc, tm + 1, tr, tm+1, r, mid + diff, last);
        T[v] = T[lc] + T[rc] + ciag(lazy[v].st, lazy[v].nd, tr-tl+1);
        return;
    }
    if(l <= tm) update(lc, tl, tm, l, r, first, last);
    if(r > tm) update(rc, tm + 1, tr, l, r, first, last);
    T[v] = T[lc] + T[rc] + ciag(lazy[v].st, lazy[v].nd, tr-tl+1); // update wierzcholka
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, ntree = 1, m, l, r, x, s, a, len, l_len, r_len;
    char c;
    cin>>n>>m;
    while(ntree < n) ntree *= 2;
    FOR(i, 1, m) {
        cin>>c;
        if(c == 'P') {
            cin>>x>>s>>a;
            len = s / a - (s % a == 0);
            l = max(x - len, 1), r = min(x + len, n);
            maszt[x] = {l, r, s, a}; // dodanie masztu na pozycji x
            l_len = x - l, r_len = r - x;
            diff = a;
            update(1, 1, ntree, l, x, s - l_len * a, s); // dodanie ciagu arytmetycznego na pozycjach (l, x) i o wartościach (s-l_len*a, s)
            diff = -a;
            if(r_len > 0) update(1, 1, ntree, x + 1, r, s - a, s - r_len * a); // dodanie ciagu arytmetycznego na pozycjach (x+1, r) i o wartościach (s-a, s-r_len*a)
        }
        if(c == 'U') {
            cin>>x;
            l = maszt[x].l, r = maszt[x].r, s = maszt[x].s, a = maszt[x].a;
            len = s / a - 1;
            maszt[x] = {0, 0, 0, 0}; // usuniecie masztu z pozycji x
            l_len = x - l, r_len = r - x;
            diff = -a;
            update(1, 1, ntree, l, x, -(s - l_len * a), -s); // odjecie ciagu arytmetycznego na pozycjach (l, x) i o wartościach (s-l_len*a, s)
            diff = a;
            if(r_len > 0) update(1, 1, ntree, x + 1, r, -(s - a), -(s - r_len * a)); // odjecie ciagu arytmetycznego na pozycjach (x+1, r) i o wartościach (s-a, s-r_len*a)
        }
        if(c == 'Z') {
            cin>>l>>r;
            cout<<query(1, 1, ntree, l, r) / (r-l+1)<<"\n"; // dzielenie sumy na przedziale przez dlugosc
        }
    }
    return 0;
}