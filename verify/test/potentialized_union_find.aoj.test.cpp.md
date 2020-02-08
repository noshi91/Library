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


# :heavy_check_mark: test/potentialized_union_find.aoj.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/potentialized_union_find.aoj.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-09 00:38:19+09:00




## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/potentialized_union_find.cpp.html">data_structure/potentialized_union_find.cpp</a>
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
      puf.unite(x, y, z);
    } break;
    case 1: {
      int x, y;
      std::cin >> x >> y;
      if (puf.same(x, y))
        std::cout << puf.distance(x, y) << std::endl;
      else
        std::cout << "?" << std::endl;
    } break;
    }
  }
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/potentialized_union_find.aoj.test.cpp"
#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B&lang=ja"

#line 1 "data_structure/potentialized_union_find.cpp"
#include <cassert>
#include <vector>

template <class Group> class potentialized_union_find {
public:
  using T = typename Group::value_type;

private:
  using size_t = std::size_t;
  class node_type {
    friend potentialized_union_find;

    T value;
    size_t parent;
    size_t size;

    node_type(const T value, const size_t parent, const size_t size)
        : value(value), parent(parent), size(size) {}
  };

  std::vector<node_type> tree;

  size_t size() const { return tree.size(); }
  void compress(const size_t x) {
    const size_t p = tree[x].parent;
    if (p == x)
      return;
    compress(p);
    tree[x].value = Group::operation(tree[p].value, tree[x].value);
    tree[x].parent = tree[p].parent;
  }

public:
  potentialized_union_find() = default;
  explicit potentialized_union_find(const size_t n)
      : tree(n, node_type(Group::identity, 0, 1)) {
    for (size_t i = 0; i != n; i += 1)
      tree[i].parent = i;
  }

  size_t find(const size_t x) {
    assert(x < size());
    compress(x);
    return tree[x].parent;
  }
  T potential(const size_t x) {
    assert(x < size());
    compress(x);
    return tree[x].value;
  }
  bool same(const size_t x, const size_t y) {
    assert(x < size());
    compress(x);
    return find(x) == find(y);
  }
  T distance(const size_t x, const size_t y) {
    assert(x < size());
    assert(y < size());
    return Group::operation(Group::inverse(potential(x)), potential(y));
  }
  size_t size(const size_t x) {
    assert(x < size());
    return tree[find(x)].size;
  }

  void unite(size_t x, size_t y, T d) {
    if (same(x, y))
      return;
    if (size(x) < size(y)) {
      d = Group::inverse(d);
      std::swap(x, y);
    }
    d = Group::operation(Group::operation(potential(x), d),
                         Group::inverse(potential(y)));
    x = find(x);
    y = find(y);
    tree[x].size += tree[y].size;
    tree[y].parent = x;
    tree[y].value = d;
  }
};
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
#line 6 "test/potentialized_union_find.aoj.test.cpp"

#include <iostream>

int main() {
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
      puf.unite(x, y, z);
    } break;
    case 1: {
      int x, y;
      std::cin >> x >> y;
      if (puf.same(x, y))
        std::cout << puf.distance(x, y) << std::endl;
      else
        std::cout << "?" << std::endl;
    } break;
    }
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

