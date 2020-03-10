#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja"

#include "data_structure/erasable_heap.cpp"
#include "data_structure/pairing_heap.cpp"
#include "other/less_equal_ordered_set.cpp"

#include <iostream>
#include <limits>
#include <utility>
#include <vector>

int main() {
#include "other/fast_ios.cpp"

  int n, m, r;
  std::cin >> n >> m >> r;
  std::vector<std::vector<std::pair<int, int>>> g(n);
  for (int i = 0; i != m; i += 1) {
    int s, t, d;
    std::cin >> s >> t >> d;
    g[s].emplace_back(d, t);
  }
  constexpr int Inf = std::numeric_limits<int>::max();
  std::vector<int> dist(n, Inf);
  dist[r] = 0;
  erasable_heap<pairing_heap<less_equal_ordered_set<std::pair<int, int>>>> heap;
  heap.push({0, r});
  while (!heap.empty()) {
    const auto [c, v] = heap.top();
    heap.pop();
    for (const auto &[d, u] : g[v]) {
      if (c + d < dist[u]) {
        if (dist[u] != Inf)
          heap.erase({dist[u], u});
        dist[u] = c + d;
        heap.push({dist[u], u});
      }
    }
  }
  for (int i = 0; i != n; i += 1) {
    if (dist[i] < Inf)
      std::cout << dist[i];
    else
      std::cout << "INF";
    std::cout << "\n";
  }
}