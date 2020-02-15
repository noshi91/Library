#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja"

#include "data_structure/radix_heap.cpp"

#include <iostream>
#include <limits>
#include <utility>
#include <vector>

int main() {
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
  radix_heap<int> heap;
  int size = 0;
  heap.push({0, r});
  size += 1;
  while (size != 0) {
    const auto [c_, v] = heap.pop();
    const int c = c_;
    size -= 1;
    if (dist[v] < c)
      continue;
    for (const auto &[d, u] : g[v]) {
      if (c + d < dist[u]) {
        dist[u] = c + d;
        heap.push({dist[u], u});
        size += 1;
      }
    }
  }
  for (int i = 0; i != n; i += 1) {
    if (dist[i] < Inf)
      std::cout << dist[i];
    else
      std::cout << "INF";
    std::cout << std::endl;
  }
}