// Łukasz Budziak
// Zadanie: Tablica binarna XXVIII OI etap I
#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for (int i = (b); i >= (a); --i)
#define TRAV(x, T) for (auto &(x) : (T))
#define ALL(T) T.begin(), T.end()
#define TAB(T, a, b) (T) + a, (T) + ((b) + 1)
#define VAR(x) #x << " = " << x << " "
#define sz(x) (int)(x).size()
#define nwd __gcd
#define pb push_back
#define st first
#define nd second
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
#define deb if (1)
const int N = 1e3, NT = N + 2;
const int M = 1e5, MT = M + 2;

int B[NT][NT];
int ans[MT];

int koszt_ruchu(int a, int b)
{
    if (a == 1 && b == 1)
        return 1;
    if (a == 1 || b == 1)
        return 2;
    return 4;
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, q;
    cin >> n >> m >> q;
    // Podzadania 1-6 O(q)
    int a, b, c, d, x, ile;
    FOR(k, 1, q)
    {
        cin >> a >> b >> c >> d;
        ile = 0;
        x = koszt_ruchu(a, b);
        B[c][d]++;
        if (B[c][d] % 2 == 0)
            ++ile;
        if (x == 4)
        {
            B[c][b - 1]++;
            if (B[c][b - 1] % 2 == 0)
                ++ile;
            B[a - 1][d]++;
            if (B[a - 1][d] % 2 == 0)
                ++ile;
            B[a - 1][b - 1]++;
            if (B[a - 1][b - 1] % 2 == 0)
                ++ile;
        }
        else if (b == 1 and x == 2)
        {
            B[a - 1][d]++;
            if (B[a - 1][d] % 2 == 0)
                ++ile;
        }
        else if (a == 1 and x == 2)
        {
            B[c][b - 1]++;
            if (B[c][b - 1] % 2 == 0)
                ++ile;
        }
        ans[k] = ans[k - 1] + (x - ile * 2);
        cout << ans[k] << "\n";
    }
    return 0;
}