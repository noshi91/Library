#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#include <iostream>
#include "data_structure/union_find.cpp"
using namespace std;

int main() {
    int n, q; cin >> n >> q;
    union_find uft(n);
    while (q --) {
        int t, u, v; cin >> t >> u >> v;
        if (t == 0) {
            uft.unite(u, v);
        } else if (t == 1) {
            cout << uft.same(u, v) << endl;
        }
    }
    return 0;
}
