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


# :heavy_check_mark: test/dual_segment_tree.aoj.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/dual_segment_tree.aoj.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-09 00:25:15+09:00




## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/dual_segment_tree.cpp.html">data_structure/dual_segment_tree.cpp</a>
* :heavy_check_mark: <a href="../../library/other/right_zero_semigroup.cpp.html">other/right_zero_semigroup.cpp</a>
* :heavy_check_mark: <a href="../../library/other/semigroup_to_monoid.cpp.html">other/semigroup_to_monoid.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D&lang=ja"

#include "data_structure/dual_segment_tree.cpp"
#include "other/right_zero_semigroup.cpp"
#include "other/semigroup_to_monoid.cpp"

#include <iostream>

int main() {
  int n, q;
  std::cin >> n >> q;
  dual_segment_tree<semigroup_to_monoid<right_zero_semigroup<int>>> dst(n);
  dst.update(0, n, 2147483647);
  for (int i = 0; i != q; i += 1) {
    int c;
    std::cin >> c;
    switch (c) {
    case 0: {
      int s, t, x;
      std::cin >> s >> t >> x;
      dst.update(s, t + 1, x);
    } break;
    case 1: {
      int i;
      std::cin >> i;
      std::cout << dst.fold(i).value() << std::endl;
    } break;
    }
  }
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/dual_segment_tree.aoj.test.cpp"
#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D&lang=ja"

#line 1 "data_structure/dual_segment_tree.cpp"
#include <cassert>
#include <cstddef>
#include <vector>

template <class Monoid> class dual_segment_tree {
  using size_t = std::size_t;
  using T = typename Monoid::value_type;

public:
  using value_type = T;
  using size_type = size_t;

private:
  static size_t lsb(const size_t x) { return __builtin_ctz(x); }
  static size_t msb(const size_t x) { return 31 - __builtin_clz(x); }
  static void add(T &x, const T y) { x = Monoid::operation(x, y); }

  std::vector<T> tree;

  void push(const size_t index) {
    add(tree[index * 2], tree[index]);
    add(tree[index * 2 + 1], tree[index]);
    tree[index] = Monoid::identity;
  }
  void propagate(const size_t index) {
    if (index == 0)
      return;
    const size_t lsb_ = lsb(index);
    for (size_t h = msb(index); h != lsb_; h -= 1)
      push(index >> h);
  }

public:
  dual_segment_tree() = default;
  explicit dual_segment_tree(const size_t n) : tree(n * 2, Monoid::identity) {}

  size_t size() const noexcept { return tree.size() / 2; }

  T fold(size_t index) const {
    assert(index < size());
    index += size();
    T ret = tree[index];
    while (index != 1) {
      index /= 2;
      add(ret, tree[index]);
    }
    return ret;
  }

  void update(size_t first, size_t last, const T x) {
    assert(first <= last);
    assert(last <= size());
    first += size();
    last += size();
    propagate(first);
    propagate(last);
    while (first != last) {
      if (first % 2 != 0) {
        add(tree[first], x);
        first += 1;
      }
      first /= 2;
      if (last % 2 != 0) {
        last -= 1;
        add(tree[last], x);
      }
      last /= 2;
    }
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
#line 7 "test/dual_segment_tree.aoj.test.cpp"

#include <iostream>

int main() {
  int n, q;
  std::cin >> n >> q;
  dual_segment_tree<semigroup_to_monoid<right_zero_semigroup<int>>> dst(n);
  dst.update(0, n, 2147483647);
  for (int i = 0; i != q; i += 1) {
    int c;
    std::cin >> c;
    switch (c) {
    case 0: {
      int s, t, x;
      std::cin >> s >> t >> x;
      dst.update(s, t + 1, x);
    } break;
    case 1: {
      int i;
      std::cin >> i;
      std::cout << dst.fold(i).value() << std::endl;
    } break;
    }
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

