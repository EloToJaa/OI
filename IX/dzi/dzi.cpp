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
const int N = 2e3, NT = N + 2;

int gl[NT];
stack<pii> S;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, x, y, mx = 0;
    pii p;
    cin>>n;
    FOR(i, 1, n) {
        FOR(j, 1, n) {
            cin>>x;
            if(x==1) gl[j]=0;
            else gl[j]++;
        }
        p = {0, 0}; // glebokosc i wspolrzedna
        S.push(p);
        FOR(j, 1, n + 1) {
            y = j;
            while(gl[j] < S.top().st) {
                p = S.top();
                S.pop();
                mx = max(mx, (p.st * (j - p.nd)));
                y = p.nd;
            }
            if(S.top().st < gl[j]) {
                p.nd = y;
                p.st = gl[j];
                S.push(p);
            }
        }
    }
    cout<<mx<<"\n";
    return 0;
}