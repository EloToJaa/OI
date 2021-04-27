#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (a); i >= (b); --i)
#define TRAV(x,T) for(auto& (x): (T))
#define ALL(x) x.begin(), x.end()
#define TAB(x,n) (x)+1, (x)+((n)+1)
#define sz(x) (int)(x).size()
#define nwd __gcd
#define pb push_back
#define pf push_front
#define st first
#define nd second
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
const int N = 1e6 + 2;



signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, a, b, c;
    bool ans = false;
    cin>>n>>a>>b>>c;
    if(n % 2 == 0 || (b - a == n - 2 || c - b == n - 2 || c - a == 2))
        ans = true;

    FOR(i, 1, n - 3) // wpisz reszte (nie potrzebne)
        cin>>a>>b>>c;
    
    cout<<(ans? "TAK": "NIE")<<"\n";
    return 0;
}