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
const int N = 5e5 + 2;
const ll INF = 1e18 + 2;

ll A[N];

void sortElements(int n, ll x) {
    ll mn = INF, mnI = 0;
    FOR(i, 1, n) {
        if(A[i] - x >= 0 && A[i] - x < mn) {
            mn = A[i] - x;
            mnI = i;
        }
    }
    mn = A[mnI];
    A[mnI] = -INF;
    sort(TAB(A, n), greater<ll>());
    A[n] = mn;
}

int getAns(int ans, ll pos, ll m, ll d, int n) {
    bool b = false;
    if(pos < d) {
        b = true;
        ll dist = d - pos;
        pos += A[n] - dist;
    }
    if(pos < d) return 0;
    if(pos >= m && !b) return ans;
    return ans + 1;
}

int solve(int n, ll m, ll d) {
    int ans = 0;
    ll pos = 0, dist;
    FOR(i, 1, n - 1) {
        if(pos < d) {
            dist = d - pos;
            if(A[i] - dist > 0) {
                pos += A[i] - dist;
                ans++;
            }
        }
        else return getAns(ans, pos, m, d, n);
    }
    return getAns(ans, pos, m, d, n);
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    ll m, d;
    cin>>m>>d>>n;
    FOR(i, 1, n)
        cin>>A[i];
    
    sortElements(n, m - d);
    
    cout<<solve(n, m, d)<<"\n";

    return 0;
}