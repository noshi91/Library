#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"

#include "data_structure/queue_aggregation.cpp"
#include "other/affine.cpp"
#include "other/modint.cpp"

#include <iostream>

int main() {
  queue_aggregation<affine_composite_monoid<modint<998244353>>> qa;

  int q;
  std::cin >> q;

  for (int i = 0; i != q; i += 1) {
    int t;
    std::cin >> t;
    switch (t) {
    case 0: {
      int a, b;
      std::cin >> a >> b;
      qa.push({a, b});
    } break;
    case 1: {
      qa.pop();
    } break;
    case 2: {
      int x;
      std::cin >> x;
      std::cout << qa.fold_all().evaluate(x).value() << std::endl;
    } break;
    }
  }
}