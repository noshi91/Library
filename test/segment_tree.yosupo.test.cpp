#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include "data_structure/segment_tree.cpp"
#include "other/affine.cpp"
#include "other/modint.cpp"

#include <iostream>

int main() {
  int n, q;
  std::cin >> n >> q;
  segment_tree<affine_composite_monoid<modint<998244353>>> st(n);
  for (int i = 0; i != n; i += 1) {
    int a, b;
    std::cin >> a >> b;
    st.update(i, {a, b});
  }
  for (int i = 0; i != q; i += 1) {
    int t;
    std::cin >> t;
    switch (t) {
    case 0: {
      int p, c, d;
      std::cin >> p >> c >> d;
      st.update(p, {c, d});
    } break;
    case 1: {
      int l, r, x;
      std::cin >> l >> r >> x;
      std::cout << st.fold(l, r).evaluate(x).value() << std::endl;
    } break;
    }
  }
}