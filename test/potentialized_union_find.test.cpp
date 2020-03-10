#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B&lang=ja"

#include "data_structure/potentialized_union_find.cpp"
#include "other/plus_group.cpp"

#include <iostream>

int main() {
#include "other/fast_ios.cpp"

  int n, q;
  std::cin >> n >> q;
  potentialized_union_find<plus_group<int>> puf(n);
  for (int i = 0; i != q; i += 1) {
    int c;
    std::cin >> c;
    switch (c) {
    case 0: {
      int x, y, z;
      std::cin >> x >> y >> z;
      if (!puf.same(x, y))
        puf.unite(x, y, z);
    } break;
    case 1: {
      int x, y;
      std::cin >> x >> y;
      if (puf.same(x, y))
        std::cout << puf.distance(x, y) << "\n";
      else
        std::cout << "?\n";
    } break;
    }
  }
}