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
const int N = 3e6 + 2;
const int INF = 2e9 + 2;

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

monqueue Qmax, Qmin;
int t[N];

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, T;
    cin>>T>>n;
    FOR(i, 1, n) cin>>t[i];
    int j = 1, wyn = 1;
    FOR(i, 1, n) {
        while(j <= n && (max(t[j], Qmax.max()) - min(t[j], -Qmin.max())) <= T) {
            Qmax.push(t[j]);
            Qmin.push(-t[j]);
            ++j;
        }
        Qmax.pop();
        Qmin.pop();
        wyn = max(wyn, j - i);
    }
    cout<<wyn<<"\n";
    return 0;
}