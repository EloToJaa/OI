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

int P[N], S[N];
void Kmp(string s, int n) {
    s = "#" + s;
    FOR(i, 2, n) {
        int pref = P[i - 1];
        while(pref > 0 && s[pref + 1] != s[i])
            pref = P[pref];
        if(s[pref + 1] == s[i]) pref++;
        P[i] = pref;
    }

    FOR(i, 1, n) {
        if(P[i] == 0) S[i] = i;
        else S[i] = S[P[i]];
    }
}

ll Solve(int n) {
    ll ans = 0;
    FOR(i, 1, n)
        if(S[i] <= i / 2)
            ans += (i - S[i]);
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    string s;
    cin>>n>>s;
    Kmp(s, n);   
    cout<<Solve(n)<<"\n";
    return 0;
}