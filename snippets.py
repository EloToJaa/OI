s = """
void RandomGraph(int n, int m) {
    assert(m >= n - 1);
    FOR(i, 2, n) {
        if(rand() % 2) cout<<R(1, i - 1)<<\" \"<<i<<\"\\n\";
        else cout<<i<<\" \"<<R(1, i - 1)<<\"\\n\";
    }
    m -= (n - 1);
    FOR(i, 1, m) cout<<R(1, n)<<\" \"<<R(1, n)<<\"\\n\";
}
"""

s = s.replace("    ", "\\t")
s = s.replace("\t", "\\t")
lista = s.split("\n")
del lista[0]
del lista[-1]
snippet = ""

for linia in lista:
    snippet += "\"" + linia + "\",\n"    

print(snippet)
