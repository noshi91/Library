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


# :heavy_check_mark: Union Find <small>(data_structure/union_find.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/union_find.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-11 22:58:19+09:00


* see: <a href="https://scrapbox.io/data-structures/Union_Find">https://scrapbox.io/data-structures/Union_Find</a>


## Depends on

* :heavy_check_mark: <a href="../other/int_alias.cpp.html">other/int_alias.cpp</a>


## Required by

* :heavy_check_mark: <a href="incremental_bridge_connectivity.cpp.html">Incremental Bridge-Connectivity <small>(data_structure/incremental_bridge_connectivity.cpp)</small></a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/incremental_bridge_connectivity.test.cpp.html">test/incremental_bridge_connectivity.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/union_find.test.cpp.html">test/union_find.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "other/int_alias.cpp"

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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
