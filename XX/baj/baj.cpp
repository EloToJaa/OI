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
const int N = 1e6, NT = N + 2;
const int INF = 1e9 + 1;
const int ujemny = 0, zero = 1, dodatni = 2;

vi DP[NT];
int A[NT], n;

void wejscie() {
    cin>>n;
    FOR(i, 1, n) {
        cin>>A[i];
    }
}

void wyjscie() {
    DP[1] = {INF, INF, INF};
    DP[1][A[1] + 1] = 0;
    FOR(i, 2, n) {
        if(A[i] == -1)
            DP[i] = {
                DP[i - 1][ujemny],
                INF,
                DP[i - 1][dodatni] + 2
            };
        if(A[i] == 0)
            DP[i] = {
                DP[i - 1][ujemny] + 1,
                min(DP[i - 1][ujemny], DP[i - 1][zero]),
                DP[i - 1][dodatni] + 1
            };
        if(A[i] == 1)
            DP[i] = {
                DP[i - 1][ujemny] + 2,
                DP[i - 1][ujemny] + 1,
                min(DP[i - 1][ujemny], min(DP[i - 1][zero], DP[i - 1][dodatni]))
            };
    }
    int ans = min(DP[n][ujemny], min(DP[n][zero], DP[n][dodatni]));
    if(ans < INF) cout<<ans<<"\n";
    else cout<<"BRAK\n";
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    wejscie();
    wyjscie();
    return 0;
}