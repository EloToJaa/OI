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
const int N = 5e5, NT = N + 10;
const int INF = 2e9 + 2;

int A[NT], Skoki[NT], Zamiana[NT];
vi Ans, Stos;
int n, m, s;
ll ans;

int GetPos() {
    FOR(i, 2, n) if(A[i] != A[1]) return i - 1;
    return n;
}

void Input() {
    int l, r;
    cin>>n>>s;
    --n;
    FOR(i, 1, n) {
        cin>>l>>r;
        if(l < r) {
            A[i] = -1;
            ans += l;
        }
        else {
            A[i] = 1;
            ans += r;
        }
        Zamiana[i] = abs(l - r);
    }
}

void Init() {
    // Liczenie wartosci do corner case'a
    int pos = GetPos(), mn = INF, k;
    // Wyliczamy ile mozemy maksymalnie uzyc teleportow w lewo lub prawo
    int ile_lewo = s, ile_prawo = n - s + 2;
    if(A[1] < 0) pos = min(pos, ile_lewo);
    else pos = min(pos, ile_prawo);
    // Szukamy najmniejsza mozliwa zmiane
    FOR(i, 1, pos) if(Zamiana[i] < mn) {
        mn = Zamiana[i];
        k = i;
    }
    // Corner case
    int granica = s + A[1] * pos;
    if(granica < 1 or granica > n + 1) { // ??
        A[k] *= -1;
        ans += mn;
    }
    // Zliczanie teleportow
    int ile = 1;
    FOR(i, 2, n) {
        if(A[i - 1] != A[i]) {
            ++m;
            Skoki[m] = A[i - 1] * ile;
            ile = 1;
        }
        else ++ile;
    }
    ++m;
    Skoki[m] = A[n] * ile;
}

void Solve() {
    int l = 0, r = n + 2;
    Ans.pb(s);
    FOR(i, 1, m) {
        // Przesuwanie wskaznikow
        while(Skoki[i] < 0) {
            ++l; ++Skoki[i];
            if(l == s) ++l;
            Stos.pb(l);
        }
        while(Skoki[i] > 0) {
            --r; --Skoki[i];
            if(r == s) --r;
            Stos.pb(r);
        }
        // Kopiowanie
        int gwiazda;
        while(!Stos.empty()) {
            gwiazda = Stos.back();
            Stos.pop_back();
            Ans.pb(gwiazda);
        }
    }
    // Wypisanie odpowiedzi
    cout<<ans<<"\n";
    TRAV(gwiazda, Ans) cout<<gwiazda<<" ";
    cout<<"\n";
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    Input();
    Init();
    Solve();
    return 0;
}