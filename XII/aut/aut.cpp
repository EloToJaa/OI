#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (a); i >= (b); --i)
#define pb push_back
#define st first
#define nd second
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
const int N = 1e6 + 2;
const int NTREE = 131072;

struct przyst { int x, y, id; } A[N + 2], B[N + 2];
int T[NTREE * 2 + 2];

int ntree;
void build(int n) {
    ntree = 1;
    while(ntree < n) ntree *= 2;
    //FOR(i, 1, n) T[i + ntree - 1] = A[i].p;
    //FORD(i, ntree - 1, 1) T[i] = max(T[i * 2], T[i * 2 + 1]);
}

void insert(int pos, int val) {
    pos += ntree - 1;
    T[pos] = val;
    pos /= 2;
    while(pos) {
        T[pos] = max(T[pos * 2], T[pos * 2 + 1]);
        pos /= 2;
    }
}

int query(int l, int r) {
    l += ntree - 1; r += ntree - 1;
    int ans = T[l];
    if(r > l) ans = max(ans, T[r]);
    while(l + 1 < r) {
        if(l % 2 == 0) ans = max(ans, T[l + 1]);
        if(r % 2 == 1) ans = max(ans, T[r - 1]);
        l /= 2; r /= 2;
    }
    return ans;
}

bool fx(przyst a, przyst b) {
    if(a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}

bool fy(przyst a, przyst b) {
    if(a.y == b.y) return a.x < b.x;
    return a.y < b.y;
}

void skaluj(int n, int &a, int &b) {
    int kl = 0;
    sort(B + 1, B + (n + 1), fx);
    FOR(i, 1, n) {
        if(B[i - 1].x != B[i].x) ++kl;
        A[B[i].id].x = kl;
    }
    a = kl;

    kl = 0;
    sort(B + 1, B + (n + 1), fy);
    FOR(i, 1, n) {
        if(B[i - 1].y != B[i].y) ++kl;
        A[B[i].id].y = kl;
    }
    b = kl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k;
    cin>>n>>m>>k;
    FOR(i, 1, k) {
        cin>>A[i].x>>A[i].y>>A[i].id;
        B[i].id = i;
        B[i].x = A[i].x;
        B[i].y = A[i].y;
    }

    skaluj(k, n, m);

    sort(A + 1, A + (k + 1), fy);
    build(k);
    FOR(i, 1, k) insert(A[i].x, query(1, A[i].x) + A[i].id);
    int ans = 0;
    FOR(i, ntree, ntree * 2 - 1) ans = max(ans, T[i]);
    cout<<ans<<"\n";
    return 0;
}