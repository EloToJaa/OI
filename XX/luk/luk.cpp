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
const int N = 3e5, NT = N + 2;

vi Graf[NT];
int DP[NT];

void Dfs(int v, int p, int ile_pracownikow) {
    int sum = 0;
    TRAV(u, Graf[v]) {
        if(u != p) {
            Dfs(u, v, ile_pracownikow);
            sum += DP[u] + 1;
        }
    }
    if(sum == 0) DP[v] = 0;
    else DP[v] = max(0, sum - ile_pracownikow);
}

bool Check(int ile_pracownikow) {
    Dfs(1, 1, ile_pracownikow);
    if(DP[1] == 0) return true;
    return false;
}

int Search(int l, int r) {
    int x;
    while(l < r) {
        x = l + ((r - l)>>1);
        if(Check(x)) r = x;
        else l = x + 1;
    }
    return l;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, a, b;
    cin>>n;
    FOR(i, 1, n - 1) {
        cin>>a>>b;
        Graf[a].pb(b);
        Graf[b].pb(a);
    }
    cout<<Search(0, n)<<"\n";
    return 0;
}