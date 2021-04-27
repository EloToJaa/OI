#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (b); i >= (a); --i)
#define TRAV(x,T) for(auto& x: (T))
#define ALL(T) T.begin(), T.end()
#define TAB(T,a,b) (T)+a, (T)+((b)+1)
#define VAR(x) #x<<" = "<<x<<" " 
#define sz(x) (int)(x).size()
#define nwd __gcd
#define pb push_back
#define st first
#define nd second
#define lc (v<<1)
#define rc (v<<1|1)
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
#define deb if(0)
const int N = 1e3, NT = N + 2;
const int INF = 1e3 + 1;

bool O[NT][NT];
vector<pii> T[NT][NT];

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    int x, y, mnX = -1, mnY = INF;
    int ilep, ilepm, ilepd, ilewp, ilemp;
    bool c = 0;

    if (n % 2 == 0 && m % 2 == 0)
        c = 1;
    if (k < n + m - 2 || k > n * m - 1 || (m == 2 && k == n && n != 1))
        cout << "NIE\n";
    else {
        mnX = -1, mnY = INF;
        if (k == m * n - 1) {
            cout << "TAK\n";
            FOR(i, 1, m) {
                if (i % 2 == 1) {
                    FOR(j, 2, n)
                        cout << j - 1 << " " << i << " " << j << " " << i << "\n";
                    if (i != m)
                        cout << n << " " << i << " " << n << " " << i + 1 << "\n";
                }
                else {
                    FORD(j, 1, n - 1)
                        cout << j + 1 << " " << i << " " << j << " " << i << "\n";
                    if (i != m)
                        cout << 1 << " " << i << " " << 1 << " " << i + 1 << "\n";
                }
            }
        }
        else if (m == 2) {
            cout << "TAK\n";
            cout << "1 1 1 2\n";
            if (n != 1)
                cout << n << " " << 1 << " " << n << " 2\n";
            FOR(i, 2, n)
                cout << i - 1 << " " << 1 << " " << i << " " << 1 << "\n";
            k -= (n + 2);
            FORD(i, 2, n - 1) {
                if (k >= 0) {
                    cout << i << " " << 2 << " " << i + 1 << " " << 2 << "\n";
                    --k;
                }
                else
                    cout << i << " " << 1 << " " << i << " " << 2 << "\n";
            }
        }
        else if (k == n + m - 2 && m % 2 == 0 && n % 2 == 1) {
            cout << "TAK\n";
            ilep = (n - 1) / 2;
            FOR(j, 1, m)
                FOR(i, 2, n)
                    cout << i - 1 << " " << j << " " << i << " " << j << "\n";
            FOR(i, 2, m)
                cout << ilep + 1 << " " << i - 1 << " " << ilep + 1 << " " << i << "\n";
        }
        else {
            FOR(i, 1, m) {
                y = k - i * (n - 1) - m + 1;
                if (y < 0)
                    break;
                if (y < mnY && y >= 0) {
                    mnX = i;
                    mnY = y;
                }
            }
            x = mnX, y = mnY;
            if (k == n + m - 2 && c && x == 1 && n != 1) {
                cout << "NIE\n";
                return 0;
            }
            else
                cout << "TAK\n";
            bool b = 0;
            if (x == m - 1) {
                --x;
                b = 1;
            }
            ilep = (m - 1) / (x + 1), ilewp = (m - 1) % (x + 1);
            ilemp = (x + 1 - ilewp) / 2;
            ilepm = ilep, ilepd = ilep + 1;
            int ile = 1, s, poz;
            if (b)
                ++ile;
            if (ilemp > 0) {
                ilep = ilepm;
                --ilemp;
            }
            else if (ilewp > 0) {
                ilep = ilepd;
                --ilewp;
            }
            else
                ilep = ilepm;
            poz = ilep + 1;
            FOR(i, 1, n) {
                if (i != 1) {
                    if (b)
                        cout << i - 1 << " " << 1 << " " << i << " " << 1 << "\n";
                    cout << i - 1 << " " << poz << " " << i << " " << poz << "\n";
                }
                if (!b || i == n)
                    FOR(j, 2, poz)
                        cout << i << " " << j - 1 << " " << i << " " << j << "\n";
            }
            --x;
            FOR(k, 1, x) {
                if (ilemp > 0) {
                    ilep = ilepm;
                    --ilemp;
                }
                else if (ilewp > 0) {
                    ilep = ilepd;
                    --ilewp;
                }
                else
                    ilep = ilepm;
                poz += ilep;
                if (ile % 2 == 1)
                    s = n;
                else
                    s = 1;
                ++ile;
                FOR(i, 1, n) {
                    if (i != 1) cout << i - 1 << " " << poz << " " << i << " " << poz << "\n";
                    int z = 1;
                    if (i == s)
                        z = 0;
                    FOR(j, poz - ilep + z + 1, poz)
                        cout << i << " " << j - 1 << " " << i << " " << j << "\n";
                }
            }
            if (ile % 2 == 0) {
                FOR(i, 1, n) {
                    int z = 1;
                    if (i != 1 && i <= y + 1) cout << i - 1 << " " << m << " " << i << " " << m << "\n";
                    else z = 0;
                    FOR(j, poz + 1, m - z)
                        cout << i << " " << j - 1 << " " << i << " " << j << "\n";
                }
            }
            else {
                FORD(i, 1, n) {
                    int z = 1;
                    if (i != n && i >= n - y) cout << i << " " << m << " " << i + 1 << " " << m << "\n";
                    else z = 0;
                    FOR(j, poz + 1, m - z)
                        cout << i << " " << j - 1 << " " << i << " " << j << "\n";
                }
            }
        }
    }
    return 0;
}