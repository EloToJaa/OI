#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (b); i >= (a); --i)
#define TRAV(x,T) for(auto& x: (T))
#define ALL(T) T.begin(), T.end()
#define TAB(T,a,b) (T)+a, (T)+((b)+1)
#define VAR(x) #x<<" = "<<x<<" " 
#define SZ(x) (int)(x).size()
#define nwd __gcd
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
typedef pair<int, bool> pib;
typedef vector<int> vi;
#define deb if(0)
const int N = 55e5, NT = N + 2;
const int M = 1e5, MT = M + 2;
const int INF = 1e9 + 2;

queue<pii> Q[2];
vector<pib> V[NT];
int START[MT], END[MT], DIST[NT];

void AddEdge(int &v, const bool &w) {
    ++v;
    V[v].pb({v - 1, w});
}

void LinkUp(const int &k, const int &a, int &v, const bool &idx) {
    if(k == 1) return;
    // dodawanie krawedzi do gory
    int u;
    while(!Q[k%2].empty() and Q[k%2].front().nd < a) {
        u = Q[k%2].front().st;
        Q[k%2].pop();
        V[v].pb({u, 0});
        V[u + 1].pb({v, 1});
    }
}

deque<int> K;
void Bfs(const int &n, const int &m) {
    // 0-1 BFS
    FOR(i, 1, m) DIST[i] = INF;
    FOR(i, 1, n) {
        K.push_back(END[i]);
        deb cout<<START[i]<<" "<<END[i]<<"\n";
        DIST[END[i]] = 0;
    }
    while(!K.empty()) {
        int v = K.front();
        K.pop_front();
        TRAV(x, V[v]) {
            auto [u, c] = x;
            if(DIST[v] + c < DIST[u]) {
                DIST[u] = DIST[v] + c;
                if(c == 0) K.push_front(u);
                else K.push_back(u);
            }
        }
    }
    FOR(i, 1, m) deb cout<<DIST[i]<<" ";
    deb cout<<"\n";
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, q, k, a, v = 0;
    bool idx;
    cin>>n>>m>>q;
    FOR(i, 1, n) {
        cin>>k;
        ++v;
        START[i] = v;
        idx = i%2;
        FOR(j, 1, k) {
            cin>>a;
            LinkUp(i, a, v, idx);
            AddEdge(v, 0);
            Q[!idx].push({v, a});
            AddEdge(v, 1);
        }
        LinkUp(i, m, v, idx);
        AddEdge(v, 0);
        END[i] = v;
        while(!Q[i%2].empty()) Q[i%2].pop();
    }
    Bfs(n, v);
    FOR(i, 1, q) {
        cin>>a;
        cout<<DIST[START[a]]<<"\n";
    }
    return 0;
}