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


# :heavy_check_mark: test/union_find.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/union_find.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-11 22:58:19+09:00


* see: <a href="https://judge.yosupo.jp/problem/unionfind">https://judge.yosupo.jp/problem/unionfind</a>


## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/union_find.cpp.html">Union Find <small>(data_structure/union_find.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/other/fast_ios.cpp.html">other/fast_ios.cpp</a>
* :heavy_check_mark: <a href="../../library/other/int_alias.cpp.html">other/int_alias.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include "data_structure/union_find.cpp"

#include <iostream>

int main() {
#include "other/fast_ios.cpp"

  int n, q;
  std::cin >> n >> q;
  union_find uf(n);
  for (int i = 0; i != q; i += 1) {
    int t, u, v;
    std::cin >> t >> u >> v;
    switch (t) {
    case 0: {
      uf.unite(u, v);
    } break;
    case 1: {
      std::cout << uf.same(u, v) << "\n";
    } break;
    }
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/union_find.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

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
#line 4 "test/union_find.test.cpp"

#include <iostream>

int main() {
#line 1 "other/fast_ios.cpp"
std::ios::sync_with_stdio(false);
std::cin.tie(nullptr);
#line 9 "test/union_find.test.cpp"

  int n, q;
  std::cin >> n >> q;
  union_find uf(n);
  for (int i = 0; i != q; i += 1) {
    int t, u, v;
    std::cin >> t >> u >> v;
    switch (t) {
    case 0: {
      uf.unite(u, v);
    } break;
    case 1: {
      std::cout << uf.same(u, v) << "\n";
    } break;
    }
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
