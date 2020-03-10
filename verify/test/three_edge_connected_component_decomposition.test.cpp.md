---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: test/three_edge_connected_component_decomposition.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/three_edge_connected_component_decomposition.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-10 16:21:51+09:00




## Depends on

* :heavy_check_mark: <a href="../../library/algorithm/three_edge_connected_component_decomposition.cpp.html">3-Edge-Connected Component Decomposition <small>(algorithm/three_edge_connected_component_decomposition.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/data_structure/union_enumerate.cpp.html">Union Enumerate <small>(data_structure/union_enumerate.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/other/int_alias.cpp.html">other/int_alias.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM                                                                \
  "https://judge.yosupo.jp/problem/three_edge_connected_components"

#include "algorithm/three_edge_connected_component_decomposition.cpp"
#include "other/int_alias.cpp"

#include <iostream>
#include <vector>

int main() {
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
  std::cout << ans.size() << std::endl;
  for (const auto &l : ans) {
    std::cout << l.size();
    for (const usize e : l)
      std::cout << " " << e;
    std::cout << std::endl;
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/three_edge_connected_component_decomposition.test.cpp"
#define PROBLEM                                                                \
  "https://judge.yosupo.jp/problem/three_edge_connected_components"

#line 2 "other/int_alias.cpp"

#include <cstddef>
#include <cstdint>

using i32 = std::int32_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using isize = std::ptrdiff_t;
using usize = std::size_t;
#line 2 "data_structure/union_enumerate.cpp"

#include <cassert>
#include <cstddef>
#include <numeric>
#include <utility>
#include <vector>

class union_enumerate {
  std::vector<usize> next;

public:
  union_enumerate() = default;
  union_enumerate(const usize size) : next(size) {
    std::iota(next.begin(), next.end(), static_cast<usize>(0));
  }

  usize size() const { return next.size(); }

  std::vector<usize> enumerate(const usize x) const {
    assert(x < size());

    std::vector<usize> ret;
    usize y = x;
    do {
      ret.push_back(y);
      y = next[y];
    } while (y != x);
    return ret;
  }

  std::vector<std::vector<usize>> get_all() const {
    const usize n = size();
    std::vector<std::vector<usize>> res;
    std::vector<bool> visited(n, false);
    for (usize i = 0; i != n; i += 1) {
      if (!visited[i]) {
        const std::vector<usize> list = enumerate(i);
        for (const usize j : list)
          visited[j] = true;
        res.push_back(list);
      }
    }
    return res;
  }

  void unite(const usize x, const usize y) {
    assert(x < size());
    assert(y < size());

    std::swap(next[x], next[y]);
  }
};

/**
 * @brief Union Enumerate
 * @see http://noshi91.hatenablog.com/entry/2019/07/19/180606
 */
#line 3 "algorithm/three_edge_connected_component_decomposition.cpp"

#include <algorithm>
#include <functional>
#include <utility>
#include <vector>

std::vector<std::vector<usize>> three_edge_connected_component_decomposition(
    const std::vector<std::vector<usize>> &g) {
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
      dfs(i, n);
  }

  return tcc.get_all();
}

/**
 * @brief 3-Edge-Connected Component Decomposition
 * @see https://www.sciencedirect.com/science/article/abs/pii/S0020019013002470
 */
#line 6 "test/three_edge_connected_component_decomposition.test.cpp"

#include <iostream>
#include <vector>

int main() {
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
  std::cout << ans.size() << std::endl;
  for (const auto &l : ans) {
    std::cout << l.size();
    for (const usize e : l)
      std::cout << " " << e;
    std::cout << std::endl;
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

