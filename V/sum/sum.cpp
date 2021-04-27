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
    int n;
    ll s, z;
    cin>>n>>s;
    z = n * (n - 1) / 2;
    if((s + z) % 2 == 1 || s > z || s < -z)
        cout<<"NIE\n";
    else {
        ll m = (s + z) / 2;
        int last = 0;
        cout<<last<<"\n";
        FORD(i, n - 1, 1) {
            if(m >= i) {
                m -= i;
                last++;
            }
            else last--;
            cout<<last<<"\n";
        }
    }
    return 0;
}