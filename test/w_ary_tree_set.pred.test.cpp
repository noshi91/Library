#define PROBLEM "https://judge.yosupo.jp/problem/predecessor_problem"

#include "data_structure/w_ary_tree_set.cpp"

#include "other/int_alias.cpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
#include "other/fast_ios.cpp"

  w_ary_tree_set<10000000> wats;

  usize N, Q;
  std::cin >> N >> Q;
  std::string T;
  std::cin >> T;
  for (usize i = 0; i != N; i += 1) {
    if (T[i] == '1') {
      wats.insert(i);
    }
  }
  for (usize i = 0; i != Q; i += 1) {
    u32 type;
    usize k;
    std::cin >> type >> k;
    if (type == 0) {
      wats.insert(k);
    } else if (type == 1) {
      wats.erase(k);
    } else if (type == 2) {
      std::cout << wats.contains(k) << "\n";
    } else if (type == 3) {
      std::cout << static_cast<isize>(wats.succ(k)) << "\n";
    } else {
      std::cout << static_cast<isize>(wats.pred(k + 1)) << "\n";
    }
  }

  return 0;
}
