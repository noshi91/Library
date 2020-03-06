#include "data_structure/union_enumerate.cpp"
#include "other/int_alias.cpp"

#include <algorithm>
#include <functional>
#include <utility>
#include <vector>

std::vector<std::vector<usize>> three_edge_connected_component_decomposition(
    const std::vector<std::vector<usize>> g) {
  const usize n = g.size();
  std::vector<usize> in(n);
  std::vector<usize> out(n);
  std::vector<usize> low(n, n);
  std::vector<usize> deg(n, 0);
  std::vector<usize> path(n, n);
  std::vector<bool> visited(n, false);
  union_enumerate tcc(n);

  const auto absorb = [&](const usize v, const usize w) -> void {
    tcc.unite(v, w);
    deg[v] += deg[w];
  };

  usize count = 0;

  const std::function<void(usize, usize)> dfs = [&](const usize v,
                                                    usize p) -> void {
    visited[v] = true;
    in[v] = count;
    count += 1;

    for (usize w : g[v]) {
      if (w == v)
        continue;
      if (w == p) {
        p = n;
        continue;
      }
      if (visited[w]) {
        if (in[w] < in[v]) {
          deg[v] += 1;
          low[v] = std::min(low[v], in[w]);
        } else {
          deg[v] -= 1;
          usize u = path[v];
          while (u != n && in[u] <= in[w] && in[w] < out[u]) {
            absorb(v, u);
            u = path[u];
          }
          path[v] = u;
        }
        continue;
      }
      dfs(w, v);
      if (path[w] == n && deg[w] <= 1) {
        deg[v] += deg[w];
        low[v] = std::min(low[v], low[w]);
        continue;
      } else if (deg[w] == 0) {
        w = path[w];
      }
      if (low[w] < low[v]) {
        low[v] = low[w];
        std::swap(w, path[v]);
      }
      while (w != n) {
        absorb(v, w);
        w = path[w];
      }
    }

    out[v] = count;
  };

  for (usize i = 0; i != n; i += 1) {
    if (!visited[i])
      dfs(i);
  }

  return tcc.get_list();
}
