#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include "data_structure/lazy_segment_tree.cpp"
#include "other/modint.cpp"
#include "other/sum_affine_action.cpp"

#include <iostream>

int main() {
  using mint = modint<998244353>;

  int n, q;
  std::cin >> n >> q;
  lazy_segment_tree<sum_affine_action<mint>> lst(n);
  for (int i = 0; i != n; i += 1) {
    int a;
    std::cin >> a;
    lst.update_point(i, {a, 1});
  }
  for (int i = 0; i != q; i += 1) {
    int t;
    std::cin >> t;
    switch (t) {
    case 0: {
      int l, r, b, c;
      std::cin >> l >> r >> b >> c;
      lst.update_range(l, r, {b, c});
    } break;
    case 1: {
      int l, r;
      std::cin >> l >> r;
      std::cout << lst.fold(l, r).first.value() << std::endl;
    } break;
    }
  }
}