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
const int N = 3e5, NT = N + 2;
const int INF = 1e9 + 1;

bitset<NT> dynamit;
vi V[NT];
int DP[2][NT], n, m, ile;

void addEdge(int a, int b) {
    V[a].pb(b);
    V[b].pb(a);
}

void dfs(int v, int p, int time) {
    TRAV(u, V[v]) {
        if(u != p) dfs(u, v, time);
    }
    DP[1][v] = INF;
    if(dynamit[v]) DP[0][v] = 0;
    else DP[0][v] = -1;
    TRAV(u, V[v]) {
        if(u != p) {
            if(DP[0][u] != -1) DP[0][v] = max(DP[0][v], DP[0][u] + 1);
            DP[1][v] = min(DP[1][v], DP[1][u] + 1);
        }
    }
    int a = DP[0][v], b = DP[1][v];
    if(a == -1) return;
    if(v == 1) {
        if(a + b > time) ile++;
        return;
    }
    if(a + b <= time) {
        DP[0][v] = -1;
        return;
    }
    if(a == time) {
        DP[0][v] = -1;
        DP[1][v] = 0;
        ile++;
    }
}

bool check(int time) {
    ile = 0;
    dfs(1, 1, time);
    return ile <= m;
}

int wyszukaj(int l, int r) {
    while(l < r) {
        int x = l + ((r - l) >> 1);
        if(check(x)) r = x;
        else l = x + 1;
    }
    return l;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int a, b, sum = 0;
    cin>>n>>m;
    FOR(i, 1, n) {
        cin>>b;
        dynamit[i] = b;
        sum += dynamit[i];
    }
    FOR(i, 1, n - 1) {
        cin>>a>>b;
        addEdge(a, b);
    }
    cout<<wyszukaj(0, n)<<"\n";
    return 0;
}