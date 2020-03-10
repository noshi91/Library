#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include "data_structure/wavelet_matrix.cpp"

#include <iostream>
#include <vector>

int main() {
#include "other/fast_ios.cpp"

  int n, q;
  std::cin >> n >> q;

  const auto wm = [&] {
    std::vector<int> a(n);
    for (int &e : a)
      std::cin >> e;
    return wavelet_matrix<int>(30, a);
  }();

  for (int i = 0; i != q; i += 1) {
    int l, r, k;
    std::cin >> l >> r >> k;
    std::cout << wm.quantile(l, r, k) << "\n";
  }
}
