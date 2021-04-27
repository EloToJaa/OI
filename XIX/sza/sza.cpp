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
const int N = 1e6, NT = N + 5;
const int M = 1e3, MT = M + 5;
const int K = 1e5;
const int INF = 1e9 + 1;

struct przedmiot {
    int c, a, b;
} A[MT];

struct pytanie {
    int m, k, s, idx;
} P[NT];

int DP[NT], n, q;
bitset<NT> ans;

void dodaj(int idx) {
    int val = A[idx].c, t = A[idx].b;
    FORD(i, val, K) {
        DP[i] = max(DP[i], min(DP[i - val], t));
    }
}

void odpowiedz(int idx) {
    if(DP[P[idx].k] > P[idx].m + P[idx].s) ans[P[idx].idx] = true;
    else ans[P[idx].idx] = false;
}

void wejscie() {
    cin>>n;
    FOR(i, 1, n) {
        cin>>A[i].c>>A[i].a>>A[i].b;
    }
    cin>>q;
    FOR(i, 1, q) {
        cin>>P[i].m>>P[i].k>>P[i].s;
        P[i].idx = i;
    }
    sort(TAB(A, 1, n), [](przedmiot a, przedmiot b) {
        return a.a < b.a;
    });
    sort(TAB(P, 1, q), [](pytanie a, pytanie b) {
        return a.m < b.m;
    });
}

void wyjscie() {
    DP[0] = INF;
    int i = 1, j = 1;
    while(i <= n or j <= q) {
        if(j > q) break;
        if(i > n) {
            odpowiedz(j++);
            continue;
        }
        if(A[i].a <= P[j].m) dodaj(i++);
        else odpowiedz(j++);
    }

    FOR(i, 1, q) {
        cout<<(ans[i]? "TAK": "NIE")<<"\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    wejscie();
    wyjscie();
    return 0;
}