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
#define poczatek first.first
#define koniec first.second
#define indeks second
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
#define deb if(0)
const int N = 1e6, NT = N + 2;

pair<pii, int> A[NT];
pii B[NT];
priority_queue<int> Q1;
priority_queue<pii> Q2;
int n, k;

void wejscie() {
    cin>>n>>k;
    FOR(i, 1, n) {
        cin>>A[i].poczatek>>A[i].koniec;
        A[i].indeks = i;
    }
    sort(TAB(A, 1, n));
}

int dlugosc() {
    int j = 1, dl, ans = 1;
    FOR(i, 1, n) {
        if(sz(Q1) == k and A[i].koniec > -Q1.top()) {
            Q1.pop();
            Q1.push(-A[i].koniec);
        }
        if(sz(Q1) < k) Q1.push(-A[i].koniec);
        if(sz(Q1) == k) {
            dl = -Q1.top() - A[i].poczatek;
            ans = max(ans, dl);
        }
    }
    cout<<ans<<"\n";
    return ans;
}

void wyjscie(int odp) {
    int j = 1, dl, ans = 1;
    FOR(i, 1, n) {
        if(sz(Q2) == k and A[i].koniec > -Q2.top().st) {
            Q2.pop();
            Q2.push({-A[i].koniec, A[i].indeks});
        }
        if(sz(Q2) < k) Q2.push({-A[i].koniec, A[i].indeks});
        if(sz(Q2) == k) {
            dl = -Q2.top().st - A[i].poczatek;
            ans = max(ans, dl);
            if(ans == odp) {
                while(!Q2.empty()) {
                    cout<<Q2.top().nd<<" ";
                    Q2.pop();
                }
                return;
            }
        }
    }
    cout<<ans<<"\n";
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    wejscie();
    wyjscie(dlugosc());
    return 0;
}