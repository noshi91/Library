#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"

#include "data_structure/parametric_heap.hpp"

#include <iostream>

int main() {
#include "other/fast_ios.cpp"

  using i64 = long long;

  int n, q;
  std::cin >> n >> q;
  parametric_heap<__int128_t> heap;

  for (int i = 0; i != n; ++i) {
    i64 a, b;
    std::cin >> a >> b;
    heap.insert(a, b);
  }

  for (int i = 0; i != q; ++i) {
    int t;
    std::cin >> t;
    switch (t) {
    case 0: {
      i64 a, b;
      std::cin >> a >> b;
      heap.insert(a, b);
    } break;
    case 1: {
      i64 p;
      std::cin >> p;
      const auto &line = heap.top(p);
      std::cout << i64(line.first * p + line.second) << "\n";
    } break;
    }
  }
}
