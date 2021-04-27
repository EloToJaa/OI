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
const int N = 25e4, NT = N + 2;
const int NTREE = 262144;

vi V[NT];
int pre[NT], post[NT], gle[NT], idx, ntree;
bitset<NT> vis;

void dfs(int v, int p) {
    vis[v] = true;
    idx++;
    pre[v] = idx;
    gle[v] = gle[p] + 1;
    TRAV(u, V[v]) {
        if(!vis[u]) dfs(u, v);
    }
    post[v] = idx;
}

void addEdge(int a, int b) {
    V[a].pb(b);
    V[b].pb(a);
}

bool przodek(int a, int b) {
    return pre[a] <= pre[b] and pre[b] <= post[a];
}

int T[NTREE * 2 + 2];

void build(int n) {
    ntree = 1;
    while(ntree < n) ntree <<= 1;
}

int query(int pos) {
    pos += ntree;
	int sum = 0;
	while(pos) {
		sum += T[pos];
		pos >>= 1;
	}
	return sum;
}

void update(int l, int r) {
    l += ntree; r += ntree;
	if(l == r) {
		T[l] ++;
		return;
	}
	T[l]++; T[r]++;
	while(r - l > 1) {
		if(l % 2 == 0) T[l + 1] ++;
		if(r % 2 == 1) T[r - 1] ++;
		l >>= 1; r >>= 1;
	}
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, a, b;
    char c;
    cin>>n;
    FOR(i, 1, n - 1) {
        cin>>a>>b;
        addEdge(a, b);
    }
    build(n);
    gle[1] = -1;
    dfs(1, 1);
    cin>>m;
    FOR(i, 1, n + m - 1) {
        cin>>c>>a;
        if(c == 'W') cout<<gle[a] - query(pre[a])<<"\n";
        else {
            cin>>b;
            if(przodek(a, b)) swap(a, b);
            update(pre[a], post[a]);
        }
    }
    return 0;
}