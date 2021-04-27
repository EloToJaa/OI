#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (b); i >= (a); --i)
#define TRAV(x,T) for(auto& x: (T))
#define ALL(T) T.begin(), T.end()
#define TAB(T,a,b) (T)+a, (T)+((b)+1)
#define VAR(x) #x<<" = "<<x<<" " 
#define SZ(x) (int)(x).size()
#define nwd __gcd
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
#define deb if(0)
const int N = 1e6, NT = N + 2;
const int INF = 1e9 + 2;

int D[NT], DP[NT];

class monqueue {
public:
    deque<int> Q;
    void push(const int &pos) {
        while(!Q.empty() and D[Q.back()] <= D[pos]) Q.pop_back();
        Q.push_back(pos);
    }
    void pop(const int &pos) {
        if(!Q.empty() and pos == Q.front()) Q.pop_front();
    }
    int max() {
        if(Q.empty()) return -INF;
        return Q.front();
    }
    int size() {
        return SZ(Q);
    }
    void clear() {
        Q.clear();
    }
};

monqueue Q1, Q2;

void Move() {
    while(!Q2.Q.empty()) {
        Q1.Q.push_back(Q2.Q.front());
        Q2.Q.pop_front();
    }
}

void Solve(const int &k, const int &n) {
    Q1.clear();
    Q2.clear();
    int j;
    Q1.push(1);
    DP[1] = 0;
    FOR(i, 2, n) {
        if(SZ(Q1) == 0) Move(); 
        j = Q1.max();
        if(j == -INF) j = i - 1;
        if(D[i] >= D[j]) {
            Q2.push(i);
            DP[i] = DP[j] + 1;
        }
        else {
            Q1.push(i);
            DP[i] = DP[j];
        }
        if(i > k) {
            Q1.pop(i - k);
            Q2.pop(i - k);
        }
    }
    cout<<DP[n]<<"\n";
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q, k;
    cin>>n;
    FOR(i, 1, n) cin>>D[i];
    cin>>q;
    FOR(i, 1, q) {
        cin>>k;
        Solve(k, n);
    }
    return 0;
}