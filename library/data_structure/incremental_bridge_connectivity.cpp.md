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


# :heavy_check_mark: Incremental Bridge-Connectivity <small>(data_structure/incremental_bridge_connectivity.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/incremental_bridge_connectivity.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-11 22:58:19+09:00


* see: <a href="https://scrapbox.io/data-structures/Incremental_Bridge-Connectivity">https://scrapbox.io/data-structures/Incremental_Bridge-Connectivity</a>


## Depends on

* :heavy_check_mark: <a href="union_find.cpp.html">Union Find <small>(data_structure/union_find.cpp)</small></a>
* :heavy_check_mark: <a href="../other/int_alias.cpp.html">other/int_alias.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/incremental_bridge_connectivity.test.cpp.html">test/incremental_bridge_connectivity.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "data_structure/union_find.cpp"
#include "other/int_alias.cpp"

#include <cassert>
#include <cstddef>
#include <unordered_set>
#include <utility>
#include <vector>

class incremental_bridge_connectivity {
  union_find cc;
  union_find bcc;
  std::vector<usize> bbf;

  usize size() const { return bbf.size(); }

  usize nil() const { return size(); }

  usize parent(const usize v) {
    if (bbf[v] == nil())
      return nil();
    else
      return bcc.find(bbf[v]);
  }

  usize lca(usize u, usize v) {
    std::unordered_set<usize> reached;
    while (true) {
      if (u != nil()) {
        if (!reached.insert(u).second)
          return u;
        u = parent(u);
      }
      std::swap(u, v);
    }
  }

  void condense_path(usize u, const usize v) {
    while (!bcc.same(u, v)) {
      const usize next = parent(u);
      bbf[u] = bbf[v];
      bcc.unite(u, v);
      u = next;
    }
  }

  void link(const usize x, const usize y) {
    usize v = x, prev = y;
    while (v != nil()) {
      const usize next = bbf[v];
      bbf[v] = prev;
      prev = v;
      v = next;
    }
  }

public:
  incremental_bridge_connectivity() = default;

  explicit incremental_bridge_connectivity(const usize n)
      : cc(n), bcc(n), bbf(n, n) {}

  bool bridge_connected(const usize u, const usize v) {
    assert(u < size());
    assert(v < size());
    return bcc.same(u, v);
  }

  void insert_edge(usize u, usize v) {
    assert(u < size());
    assert(v < size());
    u = bcc.find(u);
    v = bcc.find(v);
    if (cc.same(u, v)) {
      const usize w = lca(u, v);
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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "other/int_alias.cpp"

#include <cstddef>
#include <cstdint>

using i32 = std::int32_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using isize = std::ptrdiff_t;
using usize = std::size_t;
#line 2 "data_structure/union_find.cpp"

#include <cassert>
#include <utility>
#include <vector>

class union_find {
private:
  class node_type {
    friend union_find;

    usize parent;
    usize size;

    node_type(const usize parent, const usize size)
        : parent(parent), size(size) {}
  };

  std::vector<node_type> tree;

public:
  union_find() = default;

  explicit union_find(const usize n) : tree(n, node_type(n, 1)) {}

  usize size() const { return tree.size(); }

  usize find(const usize x) {
    assert(x < size());
    if (tree[x].parent == size())
      return x;
    else
      return tree[x].parent = find(tree[x].parent);
  }

  bool same(const usize x, const usize y) {
    assert(x < size());
    assert(y < size());
    return find(x) == find(y);
  }

  usize size(const usize x) {
    assert(x < size());
    return tree[find(x)].size;
  }

  void unite(usize x, usize y) {
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
#line 3 "data_structure/incremental_bridge_connectivity.cpp"

#line 6 "data_structure/incremental_bridge_connectivity.cpp"
#include <unordered_set>
#line 9 "data_structure/incremental_bridge_connectivity.cpp"

class incremental_bridge_connectivity {
  union_find cc;
  union_find bcc;
  std::vector<usize> bbf;

  usize size() const { return bbf.size(); }

  usize nil() const { return size(); }

  usize parent(const usize v) {
    if (bbf[v] == nil())
      return nil();
    else
      return bcc.find(bbf[v]);
  }

  usize lca(usize u, usize v) {
    std::unordered_set<usize> reached;
    while (true) {
      if (u != nil()) {
        if (!reached.insert(u).second)
          return u;
        u = parent(u);
      }
      std::swap(u, v);
    }
  }

  void condense_path(usize u, const usize v) {
    while (!bcc.same(u, v)) {
      const usize next = parent(u);
      bbf[u] = bbf[v];
      bcc.unite(u, v);
      u = next;
    }
  }

  void link(const usize x, const usize y) {
    usize v = x, prev = y;
    while (v != nil()) {
      const usize next = bbf[v];
      bbf[v] = prev;
      prev = v;
      v = next;
    }
  }

public:
  incremental_bridge_connectivity() = default;

  explicit incremental_bridge_connectivity(const usize n)
      : cc(n), bcc(n), bbf(n, n) {}

  bool bridge_connected(const usize u, const usize v) {
    assert(u < size());
    assert(v < size());
    return bcc.same(u, v);
  }

  void insert_edge(usize u, usize v) {
    assert(u < size());
    assert(v < size());
    u = bcc.find(u);
    v = bcc.find(v);
    if (cc.same(u, v)) {
      const usize w = lca(u, v);
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

