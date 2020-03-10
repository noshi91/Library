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


# :heavy_check_mark: test/incremental_bridge_connectivity.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/incremental_bridge_connectivity.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-11 00:35:25+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B&lang=jp">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B&lang=jp</a>


## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/incremental_bridge_connectivity.cpp.html">Incremental Bridge-Connectivity <small>(data_structure/incremental_bridge_connectivity.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/data_structure/union_find.cpp.html">Union Find <small>(data_structure/union_find.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/other/fast_ios.cpp.html">other/fast_ios.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/incremental_bridge_connectivity.test.cpp"
#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B&lang=jp"

#line 1 "data_structure/union_find.cpp"
#include <cassert>
#include <utility>
#include <vector>

class union_find {
private:
  using size_t = std::size_t;

  class node_type {
    friend union_find;

    size_t parent;
    size_t size;

    node_type(const size_t parent, const size_t size)
        : parent(parent), size(size) {}
  };

  std::vector<node_type> tree;

  size_t size() const { return tree.size(); }

public:
  union_find() = default;
  explicit union_find(const size_t n) : tree(n, node_type(n, 1)) {}

  size_t find(const size_t x) {
    assert(x < size());
    if (tree[x].parent == size())
      return x;
    else
      return tree[x].parent = find(tree[x].parent);
  }
  bool same(const size_t x, const size_t y) {
    assert(x < size());
    assert(y < size());
    return find(x) == find(y);
  }
  size_t size(const size_t x) {
    assert(x < size());
    return tree[find(x)].size;
  }

  void unite(size_t x, size_t y) {
    assert(x < size());
    assert(y < size());
    x = find(x);
    y = find(y);
    if (x != y) {
      if (tree[x].size < tree[y].size)
        std::swap(x, y);
      tree[x].size += tree[y].size;
      tree[y].parent = x;
    }
  }
};

/**
 * @brief Union Find
 * @see https://scrapbox.io/data-structures/Union_Find
 */
#line 2 "data_structure/incremental_bridge_connectivity.cpp"

#line 4 "data_structure/incremental_bridge_connectivity.cpp"
#include <cstddef>
#include <unordered_set>
#line 8 "data_structure/incremental_bridge_connectivity.cpp"

class incremental_bridge_connectivity {
  using size_t = std::size_t;

  union_find cc;
  union_find bcc;
  std::vector<size_t> bbf;

  size_t size() const { return bbf.size(); }
  size_t nil() const { return size(); }

  size_t parent(const size_t v) {
    if (bbf[v] == nil())
      return nil();
    else
      return bcc.find(bbf[v]);
  }
  size_t lca(size_t u, size_t v) {
    std::unordered_set<size_t> reached;
    while (true) {
      if (u != nil()) {
        if (!reached.insert(u).second)
          return u;
        u = parent(u);
      }
      std::swap(u, v);
    }
  }
  void condense_path(size_t u, const size_t v) {
    while (!bcc.same(u, v)) {
      const size_t next = parent(u);
      bbf[u] = bbf[v];
      bcc.unite(u, v);
      u = next;
    }
  }
  void link(const size_t x, const size_t y) {
    size_t v = x, prev = y;
    while (v != nil()) {
      const size_t next = bbf[v];
      bbf[v] = prev;
      prev = v;
      v = next;
    }
  }

public:
  incremental_bridge_connectivity() = default;
  explicit incremental_bridge_connectivity(const size_t n)
      : cc(n), bcc(n), bbf(n, n) {}

  bool bridge_connected(const size_t u, const size_t v) {
    assert(u < size());
    assert(v < size());
    return bcc.same(u, v);
  }

  void insert_edge(size_t u, size_t v) {
    assert(u < size());
    assert(v < size());
    u = bcc.find(u);
    v = bcc.find(v);
    if (cc.same(u, v)) {
      const size_t w = lca(u, v);
      condense_path(u, w);
      condense_path(v, w);
    } else {
      if (cc.size(u) > cc.size(v))
        std::swap(u, v);
      link(u, v);
      cc.unite(u, v);
    }
  }
};

/**
 * @brief Incremental Bridge-Connectivity
 * @see https://scrapbox.io/data-structures/Incremental_Bridge-Connectivity
 */
#line 5 "test/incremental_bridge_connectivity.test.cpp"

#include <algorithm>
#include <iostream>
#line 10 "test/incremental_bridge_connectivity.test.cpp"

int main() {
#line 1 "other/fast_ios.cpp"
std::ios::sync_with_stdio(false);
std::cin.tie(nullptr);
#line 13 "test/incremental_bridge_connectivity.test.cpp"

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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

