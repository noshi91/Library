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


# :heavy_check_mark: data_structure/union_find.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/union_find.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-17 00:25:31+09:00




## Required by

* :heavy_check_mark: <a href="incremental_bridge_connectivity.cpp.html">data_structure/incremental_bridge_connectivity.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/incremental_bridge_connectivity.aoj.test.cpp.html">test/incremental_bridge_connectivity.aoj.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/union_find.yosupo.test.cpp.html">test/union_find.yosupo.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

