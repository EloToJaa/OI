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
const int INF = 1e9 + 2;

class monqueue {
private:
    int pops = 1, pushes = 1;
public:
    deque<pii> Q;
    void push(int a);
    void pop();
    int max();
};
void monqueue::push(int a) {
    while(!Q.empty() && Q.back().st <= a) Q.pop_back();
    Q.pb({a, pushes});
    pushes++;
}
void monqueue::pop() {
    if(pops == Q.front().nd) Q.pop_front();
    pops++;
}
int monqueue::max() {
    if(Q.empty()) return -INF;
    return Q.front().st;
}

monqueue Q;
int X[N], Y[N];

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin>>n;
    FOR(i, 1, n) cin>>X[i]>>Y[i];
    int wyn = 0, j = 1;
    FOR(i, 1, n) {
        while(j <= n && Q.max() <= Y[j]) {
            Q.push(X[j]);
            ++j;
        }
        wyn = max(wyn, j - i);
        Q.pop();
    }
    cout<<wyn<<"\n";
    return 0;
}