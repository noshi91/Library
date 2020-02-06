#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B&lang=jp"

#include "data_structure/incremental_bridge_connected_components.cpp"

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int main() {
  int n, m;
  std::cin >> n >> m;
  incremental_bridge_connected_components ibcc(n);
  std::vector<std::pair<int, int>> v(m);
  for (auto &e : v) {
    std::cin >> e.first >> e.second;
    ibcc.insert_edge(e.first, e.second);
    e = std::minmax({e.first, e.second});
  }
  std::sort(v.begin(), v.end());
  for (const auto &e : v) {
    if (ibcc.find_block(e.first) != ibcc.find_block(e.second))
      std::cout << e.first << " " << e.second << std::endl;
  }
}