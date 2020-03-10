#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2426&lang=ja"

#include "data_structure/wavelet_matrix.cpp"

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int main() {
#include "other/fast_ios.cpp"

  constexpr int offset = 1000000000;

  int n, m;
  std::cin >> n >> m;
  std::vector<std::pair<int, int>> ps(n);
  for (auto &[x, y] : ps)
    std::cin >> x >> y;
  std::sort(ps.begin(), ps.end());
  const auto wm = [&] {
    std::vector<int> ys(n);
    std::transform(ps.cbegin(), ps.cend(), ys.begin(),
                   [](const auto &p) { return offset + p.second; });
    return wavelet_matrix<int>(31, ys);
  }();
  const auto idx = [&](const int xt) -> int {
    return std::partition_point(ps.cbegin(), ps.cend(),
                                [&](const auto &p) { return p.first < xt; }) -
           ps.cbegin();
  };
  for (int i = 0; i != m; i += 1) {
    int x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    x2 += 1;
    y2 += 1;
    std::cout << wm.rangefreq(idx(x1), idx(x2), offset + y1, offset + y2)
              << "\n";
  }
}
