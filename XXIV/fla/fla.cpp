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

struct Data {
    int x, a, b, pnt;
} A[N];

int calc(int x) {
    bool change = (A[x].x - A[x - 1].x) % 2;
    bool odd = A[x - 1].pnt % 2, ans;
    if(change) ans = !odd;
    else ans = odd;
    int a = A[x].a + 1, b = A[x].b - 1;
    odd = a % 2;
    if(odd != ans) a++;
    if(a > b) return -1;
    return a; 
}

bool check(int n) {
    A[0].pnt = 0;
    FOR(i, 1, n) {
        A[i].pnt = calc(i);
        if(A[i].pnt == -1) return false;
    }
    return true;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, x;
    cin>>n>>x;
    FOR(i, 1, n)
        cin>>A[i].x>>A[i].a>>A[i].b;
    if(!check(n)) {
        cout<<"NIE\n";
        return 0;
    }
    int h = A[n].pnt - (x - A[n].x);
    int ans = (x + h) / 2;
    cout<<ans<<"\n";
    return 0;
}