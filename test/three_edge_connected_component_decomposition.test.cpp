#define PROBLEM                                                                \
  "https://judge.yosupo.jp/problem/three_edge_connected_components"

#include "algorithm/three_edge_connected_component_decomposition.cpp"
#include "other/int_alias.cpp"

#include <iostream>
#include <vector>

int main() {
#include "other/fast_ios.cpp"

  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<usize>> g(n);
  for (int i = 0; i != m; i += 1) {
    int a, b;
    std::cin >> a >> b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  const auto ans = three_edge_connected_component_decomposition(g);
  std::cout << ans.size() << "\n";
  for (const auto &l : ans) {
    std::cout << l.size();
    for (const usize e : l)
      std::cout << " " << e;
    std::cout << "\n";
  }
}
