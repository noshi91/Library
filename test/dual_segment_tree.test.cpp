#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D&lang=ja"

#include "data_structure/dual_segment_tree.cpp"
#include "other/right_zero_semigroup.cpp"
#include "other/semigroup_to_monoid.cpp"

#include <iostream>

int main() {
#include "other/fast_ios.cpp"

  int n, q;
  std::cin >> n >> q;
  dual_segment_tree<semigroup_to_monoid<right_zero_semigroup<int>>> dst(n);
  dst.update(0, n, 2147483647);
  for (int i = 0; i != q; i += 1) {
    int c;
    std::cin >> c;
    switch (c) {
    case 0: {
      int s, t, x;
      std::cin >> s >> t >> x;
      dst.update(s, t + 1, x);
    } break;
    case 1: {
      int i;
      std::cin >> i;
      std::cout << dst.fold(i).value() << "\n";
    } break;
    }
  }
}