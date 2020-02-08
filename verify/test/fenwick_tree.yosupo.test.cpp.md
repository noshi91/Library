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


# :heavy_check_mark: test/fenwick_tree.yosupo.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/fenwick_tree.yosupo.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-09 00:25:15+09:00


* see: <a href="https://judge.yosupo.jp/problem/point_add_range_sum">https://judge.yosupo.jp/problem/point_add_range_sum</a>


## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/fenwick_tree.cpp.html">data_structure/fenwick_tree.cpp</a>
* :heavy_check_mark: <a href="../../library/other/plus_monoid.cpp.html">other/plus_monoid.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include "data_structure/fenwick_tree.cpp"
#include "other/plus_monoid.cpp"

#include <iostream>

int main() {
  using i64 = long long;

  int n, q;
  std::cin >> n >> q;
  fenwick_tree<plus_monoid<i64>> ft(n);
  for (int i = 0; i != n; i += 1) {
    i64 a;
    std::cin >> a;
    ft.add(i, a);
  }
  for (int i = 0; i != q; i += 1) {
    int t;
    std::cin >> t;
    switch (t) {
    case 0: {
      int p;
      i64 x;
      std::cin >> p >> x;
      ft.add(p, x);
    } break;
    case 1: {
      int l, r;
      std::cin >> l >> r;
      std::cout << -ft.fold_prefix(l) + ft.fold_prefix(r) << std::endl;
    } break;
    }
  }
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/fenwick_tree.yosupo.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#line 1 "data_structure/fenwick_tree.cpp"
#include <cassert>
#include <cstddef>
#include <vector>

template <class M> class fenwick_tree {
  using size_t = std::size_t;

public:
  using T = typename M::value_type;

private:
  std::vector<T> tree;

public:
  fenwick_tree() = default;
  explicit fenwick_tree(const size_t size) : tree(size + 1, M::identity) {}

  bool empty() const { return size() == 0; }
  size_t size() const { return tree.size() - 1; }

  T fold_prefix(size_t last) const {
    assert(last <= size());
    T ret = M::identity;
    while (last != 0) {
      ret = M::operation(tree[last], ret);
      last &= last - 1;
    }
    return ret;
  }

  void add(size_t index, const T value) {
    assert(index < size());
    index += 1;
    while (index < tree.size()) {
      tree[index] = M::operation(tree[index], value);
      index += index & ~index + 1;
    }
  }
};
#line 1 "other/plus_monoid.cpp"
template <class T> class plus_monoid {
public:
  using value_type = T;
  static T operation(const T l, const T r) { return l + r; }
  static constexpr T identity = 0;
};
#line 5 "test/fenwick_tree.yosupo.test.cpp"

#include <iostream>

int main() {
  using i64 = long long;

  int n, q;
  std::cin >> n >> q;
  fenwick_tree<plus_monoid<i64>> ft(n);
  for (int i = 0; i != n; i += 1) {
    i64 a;
    std::cin >> a;
    ft.add(i, a);
  }
  for (int i = 0; i != q; i += 1) {
    int t;
    std::cin >> t;
    switch (t) {
    case 0: {
      int p;
      i64 x;
      std::cin >> p >> x;
      ft.add(p, x);
    } break;
    case 1: {
      int l, r;
      std::cin >> l >> r;
      std::cout << -ft.fold_prefix(l) + ft.fold_prefix(r) << std::endl;
    } break;
    }
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

