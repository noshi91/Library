#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_F&lang=ja"

#include "data_structure/lazy_segment_tree.cpp"
#include "other/less_equal_ordered_set.cpp"
#include "other/min_assign_action.cpp"

#include <iostream>

int main() {
  int n, q;
  std::cin >> n >> q;
  lazy_segment_tree<min_assign_action<less_equal_ordered_set<int>>> lst(n);
  lst.update_range(0, n, 2147483647);
  for (int i = 0; i != q; i += 1) {
    int c;
    std::cin >> c;
    switch (c) {
    case 0: {
      int s, t, x;
      std::cin >> s >> t >> x;
      t += 1;
      lst.update_range(s, t, x);
    } break;
    case 1: {
      int s, t;
      std::cin >> s >> t;
      t += 1;
      std::cout << lst.fold(s, t).value() << std::endl;
    } break;
    }
  }
}