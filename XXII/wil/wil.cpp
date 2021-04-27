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
typedef pair<ll, int> pli;
typedef pair<int, ll> pil;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
#define deb if(0)
const int N = 2e6, NT = N + 2;

class monqueue {
private:
    int pops = 0, pushes = 0;
public:
    deque<pli> Q;
    void push(ll a) {
        while(!Q.empty() && Q.back().st <= a) Q.pop_back();
        pushes++;
        Q.push_back({a, pushes});
    }
    void pop() {
        pops++;
        if(pops == Q.front().nd) Q.pop_front();
    }
    ll max() {
        if(Q.empty()) return -1;
        return Q.front().st;
    }
};

int A[NT];
ll pref[NT];
monqueue Q;

ll SumaNaPrzedziale(int l, int r) {
    if(r < l) return 0;
    return pref[r] - pref[l - 1];
}

bool Check(int l, int r, const int &pos, const ll &p, const int &d) {
    ll caly_przedzial = SumaNaPrzedziale(l, r);
    ll obecna_deska = SumaNaPrzedziale(pos, pos + d - 1);
    ll najlepsza_deska = max(Q.max(), obecna_deska);
    return (caly_przedzial - najlepsza_deska) <= p;
}

int Solve(const int &n, const ll &p, const int &d) {
    int ans = d, r = d, pos = 1, len;
    Q.push(SumaNaPrzedziale(pos, pos + d - 1));
    ++pos;
    FOR(l, 1, n - d + 1) {
        while(r < n and Check(l, r + 1, pos, p, d)) {
            Q.push(SumaNaPrzedziale(pos, pos + d - 1));
            ++r; ++pos;
        }
        len = r - l + 1;
        ans = max(ans, len);
        if(len == d and l != n - d + 1) {
            Q.push(SumaNaPrzedziale(pos, pos + d - 1));
            ++r; ++pos;
        }
        Q.pop();
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, d;
    ll p;
    cin>>n>>p>>d;
    FOR(i, 1, n) {
        cin>>A[i];
        pref[i] = A[i] + pref[i - 1];
    }
    cout<<Solve(n, p, d)<<"\n";
    return 0;
}