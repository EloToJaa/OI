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
typedef pair<int, bool> pib;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
#define deb if(0)
const int N = 1e5, NT = N + 2;

class Segments {
    set<int> W, M;
    vector<int> VAL;
    const int START = 1, END = 2, ONE = 3;
    int n;

    void remove(int k, int val) {
        if(VAL[k] != ONE or val == ONE) {
            W.erase(k);
            M.erase(-k);
            VAL[k] = 0;
        }
        else VAL[k] = val;
    }

    void insert(int k, int val) {
        if(VAL[k] == 0) {
            W.insert(k);
            M.insert(-k);
            VAL[k] = val;
        }
        else VAL[k] = ONE;
    }

    int begin() {
        return *W.begin();
    }

    int end() {
        return -(*M.begin());
    }

    bool exist(int k, int val) {
        if(VAL[k] == val or VAL[k] == ONE) return true;
        return false;
    }

    public:
    Segments(int max_size) {
        n = max_size;
        VAL.resize(n + 2);
    }

    pair<pii, bool> search(int k) {
        int x = -(*M.lower_bound(-k)), y = (*W.lower_bound(k)), wx, wy;
        if(k < begin()) x = 0;
        if(k > end()) y = n + 1;
        if(x == y) {
            if(VAL[x] == START) y = (*W.lower_bound(k + 1));
            if(VAL[x] == END) x = -(*M.lower_bound(-k + 1));
        }
        if(x == 0 and y == n + 1) {
            wx = END;
            wy = START;
        }
        else if(x == 0) {
            wx = END;
            wy = VAL[y];
        }
        else if(y == n + 1) {
            wx = VAL[x];
            wy = START;
        }
        else {
            wx = VAL[x];
            wy = VAL[y];
        }
        bool is_segment = false;
        if(VAL[k] == 3 or (wx == 1 and wy == 2)) is_segment = true;
        return {{x, y}, is_segment};
    }

    void insertIDx(int k) {
        //
        bool ex_start = exist(k + 1, START), ex_end = exist(k - 1, END);
        if(ex_start and ex_end) {
            // polacz lewy i prawy przedzial
            remove(k - 1, START);
            remove(k + 1, END);
        }
        else if(ex_start) {
            // przesun poczatek prawego przedzialu
            remove(k + 1, END);
            insert(k, START);
        }
        else if(ex_end) {
            // przesun koniec lewego przedzialu
            remove(k - 1, START);
            insert(k, END);
        }
        else {
            // dodaj jedno elementowy przedzial
            insert(k, ONE);
        }
    }

    void removeIDx(int k) {
        bool ex_start = exist(k, START), ex_end = exist(k, END);
        if(ex_start and ex_end) {
            // usun jedno elementowy przedzial
            remove(k, ONE);
        }
        else if(ex_start) {
            // przesun poczatek przedzialu
            remove(k, START);
            insert(k + 1, START);
        }
        else if(ex_end) {
            // przesun koniec przedzialu
            remove(k, END);
            insert(k - 1, END);
        }
        else {
            // rozdziel jeden przedzial na dwa
            insert(k - 1, END);
            insert(k + 1, START);
        }
    }
};

int A[NT], B[NT], S[NT];
bool D[NT];
Segments P(N);

void update(int k) {
    S[k] = A[k] + B[k] + D[k];
}

pii addIDx(int k) {
    pair<pii, bool> find = P.search(k - 1);
    if(find.nd) return {find.st.st - 1, find.st.nd + 1};
    return {k - 1, k};
}

void build(int n) {
    // sumowanie liczby
    FOR(i, 1, n) {
        S[i] = A[i] + B[i];
        if(S[i] == 9) P.insertIDx(i);
    }

    // przesuwanie +1
    int x;
    FORD(i, 2, n) {
        if(S[i] > 9) {
            x = addIDx(i).st;
            D[x] = 1;
            update(x);
        }
    }
}

void insert(int k) {
    int old_val = S[k], stat_val = S[k] - D[k];
    pii x;
    update(k);
    int new_val = S[k];
    if(A[k] + B[k] == 9 and stat_val != 9) {
        if(D[k]) {
            x = addIDx(k);
            D[k] = 0;
            update(k);
            D[x.st] = 1;
            update(x.st);
        }
        else {
            x = addIDx(k);
            D[x.st] = 0;
            update(x.st);
        }
        P.insertIDx(k);
    }
    if(A[k] + B[k] != 9 and stat_val == 9) {
        x = addIDx(k);
        if(D[x.st]) {
            if(A[k] + B[k] < 10) {
                D[x.st] = 0;
                update(x.st);
            }
            D[k] = 1;
            update(k);
        }
        if(A[k] + B[k] > 9) {
            x = addIDx(k);
            D[x.st] = 1;
            update(x.st);
        }
        P.removeIDx(k);
    }
    if(A[k] + B[k] > 9 and (old_val < 9 or old_val - D[k] == 8)) {
        x = addIDx(k);
        D[x.st] = 1;
        update(x.st);
    }
    if(A[k] + B[k] < 9 and old_val > 9) {
        x = addIDx(k);
        D[x.st] = 0;
        update(x.st);
    }
}

int query(int k) {
    if(S[k] == 9) {
        pii x = addIDx(k);
        if(D[x.st]) return 0;
    }
    return (S[k] % 10);
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, z;
    cin>>n>>z;
    string s;
    char c;
    auto charToInt = [](char c) {
        return (c-48);
    };
    cin>>s;
    s = "00" + s;
    FOR(i, 2, n) {
        A[i] = charToInt(s[i]);
    }
    cin>>s;
    s = "00" + s;
    FOR(i, 2, n) {
        B[i] = charToInt(s[i]);
    }
    build(n);
    FOR(i, 1, z) {
        int ind, x;
        cin>>c>>ind;
        ind = n - ind + 1;
        if(c=='W') {
            cin>>x;
            A[ind] = x;
            insert(ind);
        }
        else if(c=='Z') {
            cin>>x;
            B[ind] = x;
            insert(ind);
        }
        else cout<<query(ind)<<"\n";
    }
    return 0;
}