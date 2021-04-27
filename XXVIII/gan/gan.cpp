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
const int M = 15e4, MT = M + 2;
const int ROOT = 316;

vector<pair<int, pii>> V[NT];
int GLE[NT], PRE[NT], POST[NT], PAR[NT], BIC[NT], idx;
int COUNT[ROOT + 2][MT], DUZE[ROOT + 2], ANS[ROOT + 2];
int K[NT], C[MT], D[NT], m;
vi UPDATES;

void Copy(const int &k) {
    int ans = 0;
    FOR(i, 1, m) {
        COUNT[k][i] = C[i];
        if(C[i] > 0) ++ans;
    }
    ANS[k] = ans;
}

void Init(int v, int p, int bic, int dist) {
    idx++;
    PRE[v] = idx;
    GLE[v] = dist;
    PAR[v] = p;
    if(v != 1) BIC[v] = bic;
    int u, w, k;
    TRAV(x, V[v]) {
        u = x.st, w = x.nd.st, k = x.nd.nd;
        if(u != p) {
            D[k] = u;
            Init(u, v, w, dist + 1);
        }
    }
    POST[v] = idx;
}

void Dfs(int v, int p) {
    if(v != 1) {
        C[BIC[v]]++;
        if(K[v] != -1) Copy(K[v]);
    }
    int u;
    TRAV(x, V[v]) {
        u = x.st;
        if(u != p) Dfs(u, v);
    }
    if(v != 1) C[BIC[v]]--;
}

bool Przodek(const int &a, const int &b) { // czy a jest przodkiem b
    return PRE[a] <= PRE[b] and PRE[b] <= POST[a];
}

void Pytanie(int v, const int &n, const int &ile_duzych) {
    while(K[v] == -1) {
        UPDATES.pb({BIC[v]});
        v = PAR[v];
    }
    int k = K[v];
    int ans = ANS[k];
    TRAV(bic, UPDATES) {
        if(COUNT[k][bic] == 0) ++ans;
        COUNT[k][bic]++;
    }
    TRAV(bic, UPDATES) COUNT[k][bic]--;
    UPDATES.clear();
    cout<<ans<<"\n";
}

void Aktualizacja(const int &d, const int &biciak, const int &n, const int &ile_duzych) {
    int v = D[d];
    int new_val = biciak, old_val = BIC[v];
    BIC[v] = new_val;
    FOR(i, 1, ile_duzych) {
        if(Przodek(v, DUZE[i])) {
            COUNT[i][old_val]--;
            if(COUNT[i][old_val] == 0) ANS[i]--;
            if(COUNT[i][new_val] == 0) ANS[i]++;
            COUNT[i][new_val]++;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q, a, b, c, duze = 0;
    cin>>n>>m>>q;
    int root = sqrt(n);
    FOR(i, 1, n - 1) {
        cin>>a>>b>>c;
        V[a].pb({b, {c, i}});
        V[b].pb({a, {c, i}});
    }
    FOR(i, 1, n) K[i] = -1;
    Init(1, 1, -1, 1);
    FOR(v, 1, n) {
        if(GLE[v] % root == 0 and POST[v] - PRE[v] >= root) {
            ++duze;
            DUZE[duze] = v;
        }
    }
    sort(TAB(DUZE, 1, duze), [](const int &ka, const int &kb) {
        return GLE[ka] < GLE[kb];
    });
    FOR(i, 1, duze) K[DUZE[i]] = i;
    Dfs(1, 1);
    K[1] = 0;
    DUZE[0] = 1;
    char z;
    FOR(i, 1, q) {
        cin>>z>>a;
        if(z == 'Z') Pytanie(a, n, duze);
        if(z == 'B') {
            cin>>b;
            Aktualizacja(a, b, n, duze);
        }
    }
    return 0;
}