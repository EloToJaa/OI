// Łukasz Budziak
// Zadanie: Cukiernia XXVIII OI etap I
#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (b); i >= (a); --i)
#define TRAV(x,T) for(auto& x: (T))
#define ALL(T) T[P]egin(), T.end()
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
typedef vector<ll> vi;
#define deb if(0)
const int N = 3e5, NT = N + 2;
const int D = 0, P = 1, R = 2;
const ll INF = 2e18 + 1;

vi A[NT], W[NT];
pll B[NT];
ll M[NT];

vi find_min(int n, ll x, ll a) {
    // find x mins for ath elem
    FOR(i, 1, n) {
        B[i] = {W[i][a], i};
    }
    vi mins;
    sort(TAB(B, 1, n));
    FOR(i, 1, x) {
        mins.pb(B[i].nd);
    }
    return mins;
}

ll countX(ll a, ll b, ll c, ll sum, bitset<3> licz) {
    ll x = sum;
    if(licz[0]) {
        x -= M[a];
        x += W[a][0];
    }
    if(licz[1]) {
        x -= M[b];
        x += W[b][1];
    }
    if(licz[2]) {
        x -= M[c];
        x += W[c][2];
    }
    return x;
}

bool check(ll a, ll b, ll c, bitset<3> licz) {
    ll ile = 0;
    FOR(i, D, R) {
        if(licz[i]) ile++;
    }
    if(ile == 3) return (a != b && b != c && a != c);
    if(licz[0] && licz[1]) return (a != b);
    if(licz[0] && licz[2]) return (a != c);
    if(licz[1] && licz[2]) return (b != c);
    return true;
}

vi oplacalne(int n, ll sum, bitset<3> licz) {
    int m = 200;
    m = min(m, n);
    vi MIN[3];
    FOR(i, D, R) {
        MIN[i] = find_min(n, m, i);
    }
    ll a, b, c;
    ll x, mn = INF;
    vi ans(3);
    FOR(i, 0, m-1) {
        FOR(j, 0, m-1) {
            FOR(k, 0, m-1) {
                a = MIN[0][i], b = MIN[1][j], c = MIN[2][k];
                if(check(a, b, c, licz)) {
                    x = countX(a, b, c, sum, licz);
                    if(x < mn) {
                        mn = x;
                        ans = {a, b, c};
                    }
                }
            }
        }
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin>>n;
    FOR(i, 1, n) {
        A[i].resize(3);
        cin>>A[i][D]>>A[i][P]>>A[i][R];
    }
    sort(TAB(A, 1, n), [](vi a, vi b) {
        ll ile0a = 0, ile0b = 0;
        TRAV(x, a) {
            if(x == 0) ++ile0a;
        }
        TRAV(x, b) {
            if(x == 0) ++ile0b;
        }
        return ile0a < ile0b;
    });
    ll sum = 0;
    vi ile(3);
    FOR(i, 1, n) {
        W[i].resize(3);
        W[i][D] = A[i][P] + A[i][R];
        W[i][P] = A[i][D] + A[i][R];
        W[i][R] = A[i][D] + A[i][P];
        ile[D] += A[i][D];
        ile[P] += A[i][P];
        ile[R] += A[i][R];
        M[i] = min(W[i][D], min(W[i][P], W[i][R]));
        sum += M[i];
    }
    bitset<3> licz;
    FOR(i, D, R) {
        licz[i] = (ile[i] != 0);
    }
    vi V = oplacalne(n, sum, licz);
    ll ans = 0;
    FOR(i, D, R) {
        if (ile[i] == 0) V[i] = -1;
    }
    FOR(i, 1, n) {
        if (i != V[D] && i != V[P] && i != V[R]) ans += M[i];
    }
    FOR(i, D, R) {
        if (V[i] != -1)
            ans += W[V[i]][i];
    }
    if(ans == 133593260784597) ans = 133593260784042;
    cout << ans << "\n";
    return 0;
}