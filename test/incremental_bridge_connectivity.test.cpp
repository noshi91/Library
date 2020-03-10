#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B&lang=jp"

#include "data_structure/incremental_bridge_connectivity.cpp"

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int main() {
#include "other/fast_ios.cpp"

  int n, m;
  std::cin >> n >> m;
  incremental_bridge_connectivity ibc(n);
  std::vector<std::pair<int, int>> es(m);
  for (auto &[u, v] : es) {
    std::cin >> u >> v;
    ibc.insert_edge(u, v);
    if (u > v)
      std::swap(u, v);
  }
  std::sort(es.begin(), es.end());
  for (const auto &[u, v] : es) {
    if (!ibc.bridge_connected(u, v))
      std::cout << u << " " << v << "\n";
  }
}