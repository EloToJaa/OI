#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (b); i >= (a); --i)
#define TRAV(x,T) for(auto& x: (T))
#define ALL(T) T.begin(), T.end()
#define TAB(T,a,b) (T)+a, (T)+((b)+1)
#define VAR(x) #x<<" = "<<x<<" " 
#define SZ(x) (int)(x).size()
#define Nwd __gcd
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
const int M = 2e2, MT = M + 2;
const int N = 1e5 + M, NT = N + 2;
const ll INF = (ll)1e18 + 2;

int P[NT];
string S[MT];

struct Macierz {
    vector<vector<ll>> Matrix;
    int n;

	void operator=(const Macierz &b) {
        FOR(i, 1, n)
            FOR(j, 1, n)
                Matrix[i][j] = b.Matrix[i][j];
	}

	void operator*=(const Macierz &b) {
		vector<vector<ll>> Temp(n + 1);
		FOR(i, 1, n) Temp[i].resize(n + 1, INF);
        FOR(i, 1, n)
            FOR(j, 1, n) {
				ll d = INF;
                FOR(k, 1, n) d = min(d, Matrix[i][k] + b.Matrix[k][j]);
				Temp[i][j] = d;
			}
        FOR(i, 1, n)
			FOR(j, 1, n)
				Matrix[i][j] = Temp[i][j];
	}
    
	void Init(int len) {
        n = len;
		Matrix.resize(n + 1);
		FOR(i, 1, n) Matrix[i].resize(n + 1, INF);
	}
} Graf1, Graf2;

int Kmp(string s) {
    int n = SZ(s);
    s = "#" + s;
    FOR(i, 1, n) P[i] = 0;
    FOR(i, 2, n) {
        int pref = P[i - 1];
        while(pref > 0 and s[pref + 1] != s[i])
            pref = P[pref];
        if(s[pref + 1] == s[i]) pref++;
        P[i] = pref;
    }
    return P[n];
}

void Solve(int n, int m) {
    ll ans = INF;
    if(m == 1) {
        FOR(i, 1, n) ans = min(ans, (ll)SZ(S[i]));
        cout<<ans<<"\n";
        return;
    }
    m -= 2;
    FOR(k, 0, 30) {
        if((1<<k) & m) Graf1 *= Graf2;
        Graf2 *= Graf2;
    }
    FOR(i, 1, n)
        FOR(j, 1, n)
            ans = min(ans, Graf1.Matrix[i][j] + SZ(S[i]));
    cout<<ans<<"\n";
}

ll Count(string a, string b) {
    if(a == b) return SZ(a) - Kmp(a);
    string s = a + "#" + b;
    return SZ(b) - Kmp(s);
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin>>n>>m;
    FOR(i, 1, n) cin>>S[i];
    Graf1.Init(n); Graf2.Init(n);
    FOR(i, 1, n)
        FOR(j, 1, n)
            Graf1.Matrix[i][j] = Count(S[i], S[j]);
    Graf2 = Graf1;
    Solve(n, m);
    return 0;
}