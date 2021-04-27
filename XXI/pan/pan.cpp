#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (a); i >= (b); --i)
#define TRAV(x,T) for(auto& (x): (T))
#define ALL(x) x.begin(), x.end()
#define TAB(x,n) (x)+1, (x)+((n)+1)
#define sz(x) (int)(x).size()
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

bool in_range(int k, int a, int b) {
    if(k == 0) return false;
    if(a / k != b / k) return true;
    if(a % k == 0) return true;
    return false;
}

void solve() {
    int a, b, c, d;
    cin>>a>>b>>c>>d;
    int m = max(b, d), ans = 1;
    int root = sqrt(m);
    FOR(i, 2, root) {
        if(in_range(i, a, b) && in_range(i, c, d))
            ans = i;
    }
    int K[3];
    FOR(j, 1, root) {
        K[1] = b / j, K[2] = d / j;
        FOR(i, 1, 2)
            if(in_range(K[i], a, b) && in_range(K[i], c, d))
                ans = max(ans, K[i]);
    }
    cout<<ans<<"\n";
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin>>n;
    FOR(i, 1, n)
        solve();
    return 0;
}