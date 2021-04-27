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
typedef vector<int> vi;
#define deb if(0)
const int N = 1e5, NT = N + 2;
const int M = 1e6, MT = M + 2;

list<pii> Graf[NT];
vi Cykl[MT], Euler, Wierz;
bitset<MT> Exist;

int n, m, ile_krawedzi, ile_cykli;

struct Edge {
    int a, b;
    list<pii>::iterator ita, itb;
} Kraw[MT];

void AddEdge(int a, int b) {
    ++ile_krawedzi;
    Graf[a].push_front({b, ile_krawedzi});
    Graf[b].push_front({a, ile_krawedzi});
    Kraw[ile_krawedzi] = {a, b, Graf[a].begin(), Graf[b].begin()};
}

void RemoveEdge(int nr) {
    auto [a, b, ita, itb] = Kraw[nr];
    Graf[a].erase(ita);
    Graf[b].erase(itb);
}

void Dfs(int v) {
    while(SZ(Graf[v]) > 0) {
        auto [u, nr] = (*Graf[v].begin());
        deb cout<<u<<" "<<nr<<"\n";
        RemoveEdge(nr);
        Dfs(u);
    }
    Euler.pb(v);
}

bool Check() {
    FOR(v, 1, n) if(SZ(Graf[v]) & 1) return false;
	return true;
}

void FindEuler(int v) {
    Exist.reset(); Euler.clear(); Wierz.clear();
    Dfs(v);
    TRAV(u, Euler) {
        if(Exist[u]) {
            ++ile_cykli;
            Cykl[ile_cykli].pb(u);
            while(Wierz.back() != u) {
                Exist[Wierz.back()] = false;
                Cykl[ile_cykli].pb(Wierz.back());
                Wierz.pop_back();
            }
            Cykl[ile_cykli].pb(u);
        }
        else {
            Exist[u] = true;
            Wierz.pb(u);
        }
    }
}

void PrintCycles() {
    cout<<ile_cykli<<"\n";
    FOR(i, 1, ile_cykli) {
        cout<<SZ(Cykl[i]) - 1<<" ";
        TRAV(v, Cykl[i]) cout<<v<<" ";
        cout<<"\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int a, b;
    bool c, d;
    cin>>n>>m;
    FOR(i, 1, m) {
        cin>>a>>b>>c>>d;
        if(c != d) AddEdge(a, b);
    }
    if(!Check()) {
        cout<<"NIE\n";
		return 0;
    }
    FOR(v, 1, n) if(SZ(Graf[v]) > 0) FindEuler(v);
    PrintCycles();
    return 0;
}