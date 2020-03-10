#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include "data_structure/union_find.cpp"

#include <iostream>

int main() {
#include "other/fast_ios.cpp"

  int n, q;
  std::cin >> n >> q;
  union_find uf(n);
  for (int i = 0; i != q; i += 1) {
    int t, u, v;
    std::cin >> t >> u >> v;
    switch (t) {
    case 0: {
      uf.unite(u, v);
    } break;
    case 1: {
      std::cout << uf.same(u, v) << "\n";
    } break;
    }
  }
}
