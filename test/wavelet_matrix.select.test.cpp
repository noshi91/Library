#include "data_structure/wavelet_matrix.cpp"
#include "other/random_integer.cpp"

#include <cassert>
#include <iostream>
#include <vector>

int main() {
  const int n = 1 << 18;
  const int b = 10;

  std::vector<int> a(n);
  for (int &e : a)
    e = random_integer(0, (1 << b) - 1);
  const wavelet_matrix<int> wm(b, a);
  std::vector<int> count(1 << b, 0);
  for (int i = 0; i != n; i += 1) {
    const int e = a[i];
    assert(wm.select(e, count[e]) == i);
    count[e] += 1;
  }
}