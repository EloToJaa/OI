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
#define lc (v<<1)
#define rc (v<<1|1)
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<int, ll> pil;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
#define NDEBUG if(0)
#define deb if(0)
const int N = 2e5, NT = N + 2;
const int NTREE = 262144 * 2 + 2;
const ll INF = (ll)1e18 + 2;
const int grupy = 0, male = 1, duze = 2;

ll X[NT], N1, N2, P[3][NT];
int H[NT], H1, H2; // H1 < H2 < H[i]
pil G[NT]; // ile jest w grupie i dlugosc pustej dziury pomiedzy nimi

ll pref(int k, int l, int r) {
    assert(l <= r);
    return P[k][r] - P[k][l - 1];
}

ll get(int k, int p) {
    return P[k][p] - P[k][p - 1];
}

ll Tsum[NTREE], Tile[NTREE];
int ntree;

void odwroc(int n) {
    ll mx = 0;
    FOR(i, 1, n) mx = max(mx, X[i]);
    FOR(i, 1, n) {
        X[i] *= -1;
        X[i] += mx;
    }
    reverse(TAB(X, 1, n));
    reverse(TAB(H, 1, n));
    FOR(i, 1, ntree * 2) {
        Tsum[i] = 0;
        Tile[i] = 0;
    }
}

int pogrupuj(int n) {
    ll zasieg = -1;
    int indeks_grupy = 0, ile_w_grupie = 0;
    FOR(i, 1, n) {
        if(X[i] > zasieg) { // dodajemy nowa grupe
            G[indeks_grupy] = {ile_w_grupie, X[i] - zasieg};
            ++indeks_grupy;
            ile_w_grupie = 0;
        }
        zasieg = max(zasieg, X[i] + H[i]); // aktualizujemy zasieg grupy
        ++ile_w_grupie;
    }
    G[indeks_grupy] = {ile_w_grupie, INF};
    return indeks_grupy;
}

void init(int n) {
    FOR(i, 1, n) {
        //pref[i].grupy = G[i].st + pref[i - 1].grupy,
        P[grupy][i] = G[i].st + P[grupy][i - 1];
        //pref[i].duze = G[i].nd / H2 + pref[i - 1].duze;
        P[duze][i] = G[i].nd / H2 + P[duze][i - 1];
        G[i].nd %= H2;
        //pref[i].male = G[i].nd / H1 + (G[i].nd % H1 != 0);
        P[male][i] = G[i].nd / H1 + (G[i].nd % H1 != 0) + P[male][i - 1];
    }
}

void update(int val, int add) {
    int v = val + ntree;
    val *= add;
    while(v > 0) {
        Tsum[v] += val;
        Tile[v] += add;
        v >>= 1;
    }
}

ll query(int v, int k) {
    if(Tile[v] == 0 or k == 0) return 0;
    if(Tile[v] == k) return Tsum[v];
    if(v >= ntree) return Tsum[v] / Tile[v] * k;
    if(k > Tile[rc]) return query(lc, k - Tile[rc]) + query(rc, Tile[rc]);
    return query(rc, k);
}

bool check(int l, int r) {
    int ile = H2 / H1;
    ll dod = N2 - pref(duze, l, r);
    ll ile_malych = N1;
    if(dod < 0) {
        ile_malych += ile * dod;
        if(ile_malych < 0) return false;
        dod = 0;
    }
    update(get(male, r), 1);
    ll potrzeba = pref(male, l, r) - query(1, dod);
    if(ile_malych < potrzeba) {
        update(get(male, r), -1);
        return false;
    }
    return true;
}

ll solve(int n) {
    // gasienica
    int r = 0;
    ll ans = 0;
    FOR(i, 1, n) ans = max(ans, get(grupy, i));
    deb cout<<ans<<"\n";
    n--;
    FOR(l, 1, n) {
        while(check(l, r + 1) and r < n) ++r;
        ans = max(ans, pref(grupy, l, r + 1));
        if(r + 1 == l) {
            ++r;
            update(get(male, r), 1);
        }
        update(get(male, l), -1);
    }
    deb cout<<ans<<"\n";
    ans += N1 + N2;
    deb cout<<ans<<"\n\n";
    return ans;
}

ll wywroc(int n) {
    // tworzenie grup
    int m = pogrupuj(n);
    deb {
        FOR(i, 1, m) cout<<G[i].st<<" "<<G[i].nd<<"\n";
        cout<<"\n";
    }
    init(m);
    ntree = 1;
    while(ntree < n) ntree <<= 1;
    ll ans = solve(m);
    odwroc(n);
    m = pogrupuj(n);
    deb {
        FOR(i, 1, m) cout<<G[i].st<<" "<<G[i].nd<<"\n";
        cout<<"\n";
    }
    init(m);
    ans = max(ans, solve(m));
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin>>n;
    FOR(i, 1, n) cin>>X[i]>>H[i];
    cin>>N1>>H1>>N2>>H2;
    if(H2 < H1) {
        swap(H1, H2);
        swap(N1, N2);
    }
    cout<<wywroc(n)<<"\n";
    return 0;
}