#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include "data_structure/fenwick_tree.cpp"
#include "other/plus_monoid.cpp"

#include <iostream>

int main() {
  using i64 = long long;

  int n, q;
  std::cin >> n >> q;
  fenwick_tree<plus_monoid<i64>> ft(n);
  for (int i = 0; i != n; i += 1) {
    i64 a;
    std::cin >> a;
    ft.add(i, a);
  }
  for (int i = 0; i != q; i += 1) {
    int t;
    std::cin >> t;
    switch (t) {
    case 0: {
      int p;
      i64 x;
      std::cin >> p >> x;
      ft.add(p, x);
    } break;
    case 1: {
      int l, r;
      std::cin >> l >> r;
      std::cout << -ft.fold_prefix(l) + ft.fold_prefix(r) << std::endl;
    } break;
    }
  }
}