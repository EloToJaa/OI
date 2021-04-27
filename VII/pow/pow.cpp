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

struct Modulo {
    ll MOD;
    Modulo(ll mod) {
        MOD = mod;
    }
    ll Moduluj(const ll &a) {
        if(a < MOD) return a;
        return a % MOD;
    }
    ll Power(ll a, ll b) {
        if(b == 0) return 1;
        ll ans = Power(a, b / 2);
        ans = Moduluj(ans * ans);
        if(b & 1) return Moduluj(ans * a);
        return ans;
    }
    ll Dodaj(ll a, ll b) {
        a = Moduluj(a), b = Moduluj(b);
        if(a + b >= MOD) return a + b - MOD;
        else return a + b;
    }
    ll Odejmij(ll a, ll b) {
        a = Moduluj(a), b = Moduluj(b);
        if(a - b < 0) return a - b + MOD;
        else return a - b;
    }
    ll Mnoz(ll a, ll b) {
        a = Moduluj(a), b = Moduluj(b);
        return Moduluj(a * b);
    }
    ll Dziel(ll a, ll b) {
        a = Moduluj(a), b = Moduluj(b);
        return Moduluj(a * Power(b, MOD - 2));
    }
} Mod(1e9 + 7);

struct Hash {
    vector<pll> Hasz, Pot;
    int n, m;
    string s;
    void Build() {
        const pii P = {29, 31};
        const int S = 'a';
        Hasz.resize(n + 1, {0, 0});
        Pot.resize(m + 1, {0, 0});
        Pot[0] = {1, 1};
        FOR(i, 1, m)
            Pot[i] = {
                Mod.Mnoz(Pot[i - 1].st, P.st),
                Mod.Mnoz(Pot[i - 1].nd, P.nd)
            };
        FOR(i, 1, n)
            Hasz[i] = {
                Mod.Dodaj( Hasz[i - 1].st, Mod.Mnoz(Pot[i].st, (s[i] - S + 1)) ),
                Mod.Dodaj( Hasz[i - 1].nd, Mod.Mnoz(Pot[i].nd, (s[i] - S + 1)) )
            };
    }
    void Init(string input_string, int max_size = -1) {
        s = "#" + input_string;
        n = SZ(s) - 1;
        if(max_size == -1) m = n;
        else m = max_size;
        Build();
    }
    pll GetHash(int l = 1, int r = -1) {
        if(r == -1) r = n;
        return {
            Mod.Mnoz( Mod.Odejmij(Hasz[r].st, Hasz[l - 1].st), Pot[m - r].st),
            Mod.Mnoz( Mod.Odejmij(Hasz[r].nd, Hasz[l - 1].nd), Pot[m - r].nd)
        };
    }
    int size() {
        return n;
    }
};

vector<Hash> A;

bool check(int x) {
    map<pll, int> M;
    set<pll> S;
    int n = SZ(A) - 2;
    FOR(j, 1, n) {
        // wrzucamy do seta wszystkie podslowa dlugosci x, unikamy powtarzajacych sie podslow
        S.clear();
        FOR(i, 1, SZ(A[j]) - x + 1)
            S.insert(A[j].GetHash(i, i + x - 1));
        // przerzucamy te podslowa do mapy
        TRAV(a, S)
            M[a]++;
    }
    TRAV(a, M)
        if(a.nd == n) return true;
    return false;
}

int search_last(int l, int r) {
    while(l < r) {
        int mid = (l + r + 1) / 2;
        if(check(mid)) l = mid;
        else r = mid - 1;
    }
    return l;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, mx = 0;
    cin>>n;
    string s;
    vector<string> S;
    A.resize(n + 2);
    // wpisywanie danych wejsciowych
    FOR(i, 1, n) {
        cin>>s;
        mx = max(mx, SZ(s));
        S.pb(s);
    }
    // tworzymy hashe dla kazdego slowa
    FOR(i, 1, n)
        A[i].Init(S[i - 1], mx);
    
    cout<<search_last(0, mx)<<"\n";
    return 0;
}