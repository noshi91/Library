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


# :heavy_check_mark: test/lazy_segment_tree.aoj.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/lazy_segment_tree.aoj.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-14 16:53:57+09:00




## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/lazy_segment_tree.cpp.html">data_structure/lazy_segment_tree.cpp</a>
* :heavy_check_mark: <a href="../../library/other/less_equal_ordered_set.cpp.html">other/less_equal_ordered_set.cpp</a>
* :heavy_check_mark: <a href="../../library/other/min_assign_action.cpp.html">other/min_assign_action.cpp</a>
* :heavy_check_mark: <a href="../../library/other/min_semigroup.cpp.html">other/min_semigroup.cpp</a>
* :heavy_check_mark: <a href="../../library/other/right_zero_semigroup.cpp.html">other/right_zero_semigroup.cpp</a>
* :heavy_check_mark: <a href="../../library/other/semigroup_to_monoid.cpp.html">other/semigroup_to_monoid.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_F&lang=ja"

#include "data_structure/lazy_segment_tree.cpp"
#include "other/less_equal_ordered_set.cpp"
#include "other/min_assign_action.cpp"

#include <iostream>

int main() {
  int n, q;
  std::cin >> n >> q;
  lazy_segment_tree<min_assign_action<less_equal_ordered_set<int>>> lst(n);
  lst.update_range(0, n, 2147483647);
  for (int i = 0; i != q; i += 1) {
    int c;
    std::cin >> c;
    switch (c) {
    case 0: {
      int s, t, x;
      std::cin >> s >> t >> x;
      t += 1;
      lst.update_range(s, t, x);
    } break;
    case 1: {
      int s, t;
      std::cin >> s >> t;
      t += 1;
      std::cout << lst.fold(s, t).value() << std::endl;
    } break;
    }
  }
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/lazy_segment_tree.aoj.test.cpp"
#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_F&lang=ja"

#line 1 "data_structure/lazy_segment_tree.cpp"
#include <cassert>
#include <cstddef>
#include <vector>

template <class A> class lazy_segment_tree {
  using size_t = std::size_t;
  using V = typename A::value_structure;
  using T = typename V::value_type;
  using O = typename A::operator_structure;
  using E = typename O::value_type;

  class node_type {
  public:
    T value;
    E lazy;

    node_type(const T value, const E lazy) : value(value), lazy(lazy) {}
  };

  static size_t lsb(const size_t x) { return __builtin_ctz(x); }
  static size_t msb(const size_t x) { return 31 - __builtin_clz(x); }
  static T get(const node_type &x) { return A::operation(x.value, x.lazy); }
  static void add(E &x, const E y) { x = O::operation(x, y); }

  std::vector<node_type> tree;

  void propagate(const size_t index) {
    add(tree[index * 2].lazy, tree[index].lazy);
    add(tree[index * 2 + 1].lazy, tree[index].lazy);
    tree[index].lazy = O::identity;
  }
  void propagate_bound(const size_t index) {
    if (index == 0)
      return;
    const size_t lsb_ = lsb(index);
    for (size_t h = msb(index); h != lsb_; h -= 1)
      propagate(index >> h);
  }
  void recalc(const size_t index) {
    tree[index].value =
        V::operation(get(tree[index * 2]), get(tree[index * 2 + 1]));
  }
  void recalc_bound(size_t index) {
    if (index == 0)
      return;
    index >>= lsb(index);
    while (index != 1) {
      index /= 2;
      recalc(index);
    }
  }

public:
  lazy_segment_tree() = default;
  explicit lazy_segment_tree(const size_t n)
      : tree(n * 2, node_type(V::identity, O::identity)) {}

  size_t size() const { return tree.size() / 2; }

  T fold(size_t first, size_t last) {
    assert(first <= last);
    assert(last <= size());
    first += size();
    last += size();
    propagate_bound(first);
    recalc_bound(first);
    propagate_bound(last);
    recalc_bound(last);
    T fold_l = V::identity;
    T fold_r = V::identity;
    while (first != last) {
      if (first % 2 != 0) {
        fold_l = V::operation(fold_l, get(tree[first]));
        first += 1;
      }
      first /= 2;
      if (last % 2 != 0) {
        last -= 1;
        fold_r = V::operation(get(tree[last]), fold_r);
      }
      last /= 2;
    }
    return V::operation(fold_l, fold_r);
  }

  void update_range(size_t first, size_t last, const E x) {
    assert(first <= last);
    assert(last <= size());
    first += size();
    last += size();
    propagate_bound(first);
    propagate_bound(last);
    const size_t first_c = first;
    const size_t last_c = last;
    while (first != last) {
      if (first % 2 != 0) {
        add(tree[first].lazy, x);
        first += 1;
      }
      first /= 2;
      if (last % 2 != 0) {
        last -= 1;
        add(tree[last].lazy, x);
      }
      last /= 2;
    }
    recalc_bound(first_c);
    recalc_bound(last_c);
  }

  void update_point(size_t index, const T x) {
    assert(index < size());
    index += size();
    for (size_t h = msb(index); h != 0; h -= 1)
      propagate(index >> h);
    tree[index] = node_type(x, O::identity);
    while (index != 1) {
      index /= 2;
      recalc(index);
    }
  }
};
#line 1 "other/less_equal_ordered_set.cpp"
template <class T> class less_equal_ordered_set {
public:
  using value_type = T;
  static constexpr bool compare(const T &x, const T &y) noexcept {
    return x <= y;
  }
};
#line 1 "other/min_semigroup.cpp"
template <class W> class min_semigroup {
  using T = typename W::value_type;

public:
  using value_type = T;
  static constexpr T operation(const T &l, const T &r) noexcept {
    return W::compare(l, r) ? l : r;
  }
};
#line 1 "other/right_zero_semigroup.cpp"
template <class T> class right_zero_semigroup {
public:
  using value_type = T;
  static constexpr T operation(const T &, const T &r) noexcept { return r; }
};
#line 1 "other/semigroup_to_monoid.cpp"
#include <optional>
#include <utility>

template <class S> class semigroup_to_monoid {
  using T = std::optional<typename S::value_type>;

public:
  using value_type = T;
  static constexpr T operation(const T &l, const T &r) noexcept {
    if (!l)
      return r;
    if (!r)
      return l;
    return T(std::in_place, S::operation(*l, *r));
  }
  static constexpr T identity{std::nullopt};
};
#line 4 "other/min_assign_action.cpp"

#include <optional>

template <class W> class min_assign_action {
  using T = typename W::value_type;
  using U = std::optional<T>;

public:
  using value_structure = semigroup_to_monoid<min_semigroup<W>>;
  using operator_structure = semigroup_to_monoid<right_zero_semigroup<T>>;
  static constexpr U operation(const U &l, const U &r) noexcept {
    return r ? r : l;
  }
};
#line 7 "test/lazy_segment_tree.aoj.test.cpp"

#include <iostream>

int main() {
  int n, q;
  std::cin >> n >> q;
  lazy_segment_tree<min_assign_action<less_equal_ordered_set<int>>> lst(n);
  lst.update_range(0, n, 2147483647);
  for (int i = 0; i != q; i += 1) {
    int c;
    std::cin >> c;
    switch (c) {
    case 0: {
      int s, t, x;
      std::cin >> s >> t >> x;
      t += 1;
      lst.update_range(s, t, x);
    } break;
    case 1: {
      int s, t;
      std::cin >> s >> t;
      t += 1;
      std::cout << lst.fold(s, t).value() << std::endl;
    } break;
    }
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

