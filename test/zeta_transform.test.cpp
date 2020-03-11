#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3119"

#include "algorithm/superset_mobius_transform.cpp"
#include "algorithm/superset_zeta_transform.cpp"
#include "other/modint.cpp"
#include "other/multiplies_monoid.cpp"
#include "other/plus_group.cpp"

#include <iostream>

int main() {
#include "other/fast_ios.cpp"

  using mint = modint<1000000007>;
  constexpr int b = 20;

  int n;
  std::cin >> n;
  std::vector<mint> v(1 << b, 1);
  for (int i = 0; i != n; i += 1) {
    int a;
    std::cin >> a;
    v[a] *= 2;
  }
  superset_zeta_transform<multiplies_monoid<mint>>(v);
  for (mint &e : v)
    e -= 1;
  superset_mobius_transform<plus_group<mint>>(v);
  std::cout << v[0].value() << "\n";
}