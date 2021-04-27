#include<bits/stdc++.h>
#include "poslib.h"
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
#define deb if(1)
#define run if(0)
const int N = 1e6, NT = N + 2;

int DP[NT];

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, a, b;
    inicjuj(&n, &a, &b);
    if(n == 1) odpowiedz(1);

    // Liczenie DP
    FOR(i, 0, max(a, b) - 1) DP[i] = 1;
    FOR(i, max(a, b), N) {
        DP[i] = DP[i - a] + DP[i + b];
        DP[i] = min(DP[i], n + 1);
    }

    // Ustawianie aktualnego
    int akt = N;
    while(DP[akt] >= n) --akt;
    ++akt;
    
    // Wyszukiwanie ,,binarne"
    int l = 1, r = n;
    while(l < r) {
        int pos = DP[akt - b];
        if(pytaj('W', l + pos - 1)) l = l + pos;
        else r = l + pos - 1;
        while(akt >= 0 and DP[akt] >= r - l + 1) --akt;
        ++akt;
    }
    odpowiedz(l);
    return 0;
}