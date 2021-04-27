#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (b); i >= (a); --i)
#define TRAV(x,T) for(auto& x: (T))
#define ALL(T) T.begin(), T.end()
#define TAB(T,a,b) (T)+a, (T)+((b)+1)
#define VAR(x) deb cout<<#x<<" = "<<x<<"\n"; 
#define SZ(x) (int)(x).size()
#define nwd __gcd
#define pb push_back
#define st first
#define nd second
#define pref first
#define suff second
#define lc (v<<1)
#define rc (v<<1|1)
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
#define deb if(1)
const int N = 1e6, NT = N + 2;
const int INF = 2e9 + 2;

int A[NT], PREF[NT];
pii MIN[NT];

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, p, q, x, y, a, b, reszta, mn = INF, ans;
    string s;
    cin>>n>>p>>q>>x>>y>>s;
    FOR(i, 0, n - 1) A[i + 1] = (s[i] == '+'? 1: -1);
    FOR(i, 1, n) PREF[i] = A[i] + PREF[i - 1];
    MIN[1].pref = PREF[1];
    FOR(i, 2, n) MIN[i].pref = min(MIN[i - 1].pref, PREF[i]);
    MIN[n].suff = PREF[n];
    FORD(i, 1, n - 1) MIN[i].suff = min(MIN[i + 1].suff, PREF[i]);
    FOR(i, 1, n) {
        a = (PREF[i] - MIN[i].suff) - p;
        if(a < 0) a = 0;
        b = (-MIN[i].pref) + (PREF[i] - PREF[n]) - p;
        if(b < 0) b = 0;
        if(a < b) a = b;
        a += (a&1);
        if(q - p > PREF[n] + a) ans = (q - p - PREF[n]) / 2;
        else ans = a + (PREF[n] - (q - p)) / 2;
        reszta = y * (n - i) + x * ans;
        mn = min(mn, reszta);
    }
    cout<<mn<<"\n";
    return 0;
}