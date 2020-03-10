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


# :heavy_check_mark: test/potentialized_union_find.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/potentialized_union_find.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-11 00:35:25+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B&lang=ja">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B&lang=ja</a>


## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/potentialized_union_find.cpp.html">Potentialized Union Find <small>(data_structure/potentialized_union_find.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/other/fast_ios.cpp.html">other/fast_ios.cpp</a>
* :heavy_check_mark: <a href="../../library/other/int_alias.cpp.html">other/int_alias.cpp</a>
* :heavy_check_mark: <a href="../../library/other/plus_group.cpp.html">other/plus_group.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B&lang=ja"

#include "data_structure/potentialized_union_find.cpp"
#include "other/plus_group.cpp"

#include <iostream>

int main() {
#include "other/fast_ios.cpp"

  int n, q;
  std::cin >> n >> q;
  potentialized_union_find<plus_group<int>> puf(n);
  for (int i = 0; i != q; i += 1) {
    int c;
    std::cin >> c;
    switch (c) {
    case 0: {
      int x, y, z;
      std::cin >> x >> y >> z;
      if (!puf.same(x, y))
        puf.unite(x, y, z);
    } break;
    case 1: {
      int x, y;
      std::cin >> x >> y;
      if (puf.same(x, y))
        std::cout << puf.distance(x, y) << "\n";
      else
        std::cout << "?\n";
    } break;
    }
  }
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/potentialized_union_find.test.cpp"
#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B&lang=ja"

#line 2 "other/int_alias.cpp"

#include <cstddef>
#include <cstdint>

using i32 = std::int32_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using isize = std::ptrdiff_t;
using usize = std::size_t;
#line 2 "data_structure/potentialized_union_find.cpp"

#include <cassert>
#include <vector>
#include<utility>

template <class G> class potentialized_union_find {
  using T = typename G::value_type;
  class node_type {
  public:
    T value;
    usize parent;
    usize size;

    node_type(const T value, const usize parent, const usize size)
        : value(value), parent(parent), size(size) {}
  };

  std::vector<node_type> tree;

  void compress(const usize x) {
    const usize p = tree[x].parent;
    if (p == x)
      return;
    compress(p);
    tree[x].value = G::operation(tree[p].value, tree[x].value);
    tree[x].parent = tree[p].parent;
  }

public:
  potentialized_union_find() = default;

  explicit potentialized_union_find(const usize n)
      : tree(n, node_type(G::identity, 0, 1)) {
    for (usize i = 0; i != n; i += 1)
      tree[i].parent = i;
  }

  usize size() const { return tree.size(); }

  usize find(const usize x) {
    assert(x < size());

    compress(x);
    return tree[x].parent;
  }

  T potential(const usize x) {
    assert(x < size());

    compress(x);
    return tree[x].value;
  }

  bool same(const usize x, const usize y) {
    assert(x < size());

    compress(x);
    return find(x) == find(y);
  }

  T distance(const usize x, const usize y) {
    assert(x < size());
    assert(y < size());

    return G::operation(G::inverse(potential(x)), potential(y));
  }

  usize size(const usize x) {
    assert(x < size());

    return tree[find(x)].size;
  }

  void unite(usize x, usize y, T d) {
    assert(x < size());
    assert(y < size());
    assert(!same(x, y));

    if (size(x) < size(y)) {
      d = G::inverse(d);
      std::swap(x, y);
    }
    d = G::operation(G::operation(potential(x), d), G::inverse(potential(y)));
    x = find(x);
    y = find(y);
    tree[x].size += tree[y].size;
    tree[y].parent = x;
    tree[y].value = d;
  }
};

/**
 * @brief Potentialized Union Find
 */
#line 1 "other/plus_group.cpp"
template <class T> class plus_group {
public:
  using value_type = T;
  static constexpr T operation(const T &l, const T &r) noexcept {
    return l + r;
  }
  static constexpr T identity = 0;
  static constexpr T inverse(const T &x) noexcept { return -x; }
};
#line 6 "test/potentialized_union_find.test.cpp"

#include <iostream>

int main() {
#line 1 "other/fast_ios.cpp"
std::ios::sync_with_stdio(false);
std::cin.tie(nullptr);
#line 11 "test/potentialized_union_find.test.cpp"

  int n, q;
  std::cin >> n >> q;
  potentialized_union_find<plus_group<int>> puf(n);
  for (int i = 0; i != q; i += 1) {
    int c;
    std::cin >> c;
    switch (c) {
    case 0: {
      int x, y, z;
      std::cin >> x >> y >> z;
      if (!puf.same(x, y))
        puf.unite(x, y, z);
    } break;
    case 1: {
      int x, y;
      std::cin >> x >> y;
      if (puf.same(x, y))
        std::cout << puf.distance(x, y) << "\n";
      else
        std::cout << "?\n";
    } break;
    }
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

