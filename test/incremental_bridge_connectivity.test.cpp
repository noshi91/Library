#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"

#include "data_structure/incremental_bridge_connectivity.cpp"

#include <iostream>
#include <vector>

int main() {
#include "other/fast_ios.cpp"

  int n, m;
  std::cin >> n >> m;
  incremental_bridge_connectivity ibc(n);
  for (int i = 0; i != m; i += 1) {
    int a, b;
    std::cin >> a >> b;
    ibc.insert_edge(a, b);
  }

  std::vector<int> id(n, n);
  int k = 0;
  std::vector<std::vector<int>> ans(n);
  for (int i = 0; i != n; i += 1) {
    const int r = ibc.find_block(i);
    if (id[r] == n) {
      id[r] = k;
      k += 1;
    }
    ans[id[r]].push_back(i);
  }

  std::cout << k << "\n";
  for (int i = 0; i != k; i += 1) {
    std::cout << ans[i].size();
    for (const int e : ans[i])
      std::cout << " " << e;
    std::cout << "\n";
  }
}
