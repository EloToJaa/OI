#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (b); i >= (a); --i)
#define TRAV(x,T) for(auto& x: (T))
#define ALL(T) T.begin(), T.end()
#define TAB(T,a,b) (T)+a, (T)+((b)+1)
#define VAR(x) #x<<" = "<<x<<" " 
#define SZ(x) (int)(x).size()
#define Nwd __gcd
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
const int N = 1e5, NT = N + 2;
const int M = 1e4, MT = M + 2;

int A[NT], Zap[MT], Ile[18];
map<int, int> Map[18];

int GetHash(int l, int len) {
    int r = l + len - 1, pot = 0, ans = 0;
    FORD(i, l, r) {
        ans += A[i] * (1<<pot);
        ++pot;
    }
    return ans;
}

void Answer() {
    FOR(len, 1, 17) if(SZ(Map[len]) < Ile[len]) {
        cout<<len<<"\n";
        return;
    }
    cout<<"18\n";
}

void Add(int pos, int n) {
    FOR(len, 1, min(17, n)) {
        int l = max(1, pos - len + 1);
        int hash = GetHash(l, len);
        FOR(i, l, min(pos, n - len + 1)) {
            Map[len][hash]++;
            hash <<= 1;
            hash += A[i + len];
            if(hash & Ile[len]) hash -= Ile[len];
        }
    }
}

void Remove(int pos, int n) {
    FOR(len, 1, min(17, n)) {
        int l = max(1, pos - len + 1);
        int hash = GetHash(l, len);
        FOR(i, l, min(pos, n - len + 1)) {
            Map[len][hash]--;
            if(Map[len][hash] == 0) Map[len].erase(hash);
            hash <<= 1;
            hash += A[i + len];
            if(hash & Ile[len]) hash -= Ile[len];
        }
    }
}

void Solve(int pos, int n) {
    Remove(pos, n);
    A[pos] ^= 1;
    Add(pos, n);
    Answer();
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    char c;
    cin>>n>>m;
    FOR(i, 1, n) {
        cin>>c;
        A[i] = c - '0';
    }
    FOR(i, 1, m) cin>>Zap[i];
    //
    FOR(len, 1, 17) Ile[len] = (1<<len);
    FOR(len, 1, min(17, n))
        FOR(i, 1, n - len + 1)
            Map[len][GetHash(i, len)]++;
    //
    Answer();
    FOR(i, 1, m) Solve(Zap[i], n);
    return 0;
}