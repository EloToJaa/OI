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
const int N = 1e6;

int A[N + 2], B[N + 2];
pii C[N * 2 + 2];

void calc(int l, int r) {
    int sum = B[r] - B[l - 1];
    C[sum] = {l, r};
    while(l < r) {
        if(A[r] == 2) --r;
        else if(A[l] == 2) ++l;
        else ++l, --r;
        sum -= 2;
        C[sum] = {l, r};
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, a, p = -1, k = -1;
    char c;
    cin>>n>>m;
    FOR(i, 1, n) {
        cin>>c;
        A[i] = (c == 'W'? 1: 2);
        if(A[i] == 1) {
            k = i;
            if(p == -1) p = i;
        }
        B[i] = A[i] + B[i - 1];
    }
    calc(1, n);
    if(k != -1) {
        if(B[p] < B[n] - B[k - 1]) calc(p + 1, n);
        else calc(1, k - 1);
    }
    FOR(i, 1, m) {
        cin>>a;
        if(C[a].st != 0 && C[a].nd != 0) cout<<C[a].st<<" "<<C[a].nd<<"\n";
        else cout<<"NIE\n";
    }
    return 0;
}