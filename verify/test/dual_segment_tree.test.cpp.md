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


# :heavy_check_mark: test/dual_segment_tree.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/dual_segment_tree.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-11 00:35:25+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D&lang=ja">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D&lang=ja</a>


## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/dual_segment_tree.cpp.html">Dual Segment Tree <small>(data_structure/dual_segment_tree.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/other/bit_width.cpp.html">other/bit_width.cpp</a>
* :heavy_check_mark: <a href="../../library/other/countl_zero.cpp.html">other/countl_zero.cpp</a>
* :heavy_check_mark: <a href="../../library/other/countr_zero.cpp.html">other/countr_zero.cpp</a>
* :heavy_check_mark: <a href="../../library/other/fast_ios.cpp.html">other/fast_ios.cpp</a>
* :heavy_check_mark: <a href="../../library/other/int_alias.cpp.html">other/int_alias.cpp</a>
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
#include "other/fast_ios.cpp"

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
      std::cout << dst.fold(i).value() << "\n";
    } break;
    }
  }
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/dual_segment_tree.test.cpp"
#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D&lang=ja"

#line 2 "other/bit_width.cpp"

#line 2 "other/countl_zero.cpp"

#line 2 "other/countr_zero.cpp"

#line 2 "other/int_alias.cpp"

#include <cstddef>
#include <cstdint>

using i32 = std::int32_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using isize = std::ptrdiff_t;
using usize = std::size_t;
#line 4 "other/countr_zero.cpp"

#include <array>

usize countr_zero(u64 x) {
  if (x == 0)
    return 64;
#ifdef __GNUC__
  return __builtin_ctzll(x);
#else
  constexpr std::array<usize, 64> table = {
      0,  1,  2,  7,  3,  13, 8,  27, 4,  33, 14, 36, 9,  49, 28, 19,
      5,  25, 34, 17, 15, 53, 37, 55, 10, 46, 50, 39, 29, 42, 20, 57,
      63, 6,  12, 26, 32, 35, 48, 18, 24, 16, 52, 54, 45, 38, 41, 56,
      62, 11, 31, 47, 23, 51, 44, 40, 61, 30, 22, 43, 60, 21, 59, 58};
  return table[(x & ~x + 1) * 0x218A7A392DD9ABF >> 58 & 0x3F];
#endif
}
#line 5 "other/countl_zero.cpp"

usize countl_zero(u64 x) {
#ifdef __GNUC__
  return x == 0 ? 64 : __builtin_clzll(x);
#else
  x |= x >> 1;
  x |= x >> 2;
  x |= x >> 4;
  x |= x >> 8;
  x |= x >> 16;
  x |= x >> 32;
  return 64 - countr_zero(x + 1);
#endif
}
#line 5 "other/bit_width.cpp"

usize bit_width(const u64 x) { return 64 - countl_zero(x); }
#line 3 "data_structure/dual_segment_tree.cpp"

#include <cassert>
#line 6 "data_structure/dual_segment_tree.cpp"
#include <vector>

template <class M> class dual_segment_tree {
  using size_t = std::size_t;
  using T = typename M::value_type;

public:
  using value_type = T;
  using size_type = size_t;

private:
  static void add(T &x, const T y) { x = M::operation(x, y); }

  std::vector<T> tree;

  void push(const size_t index) {
    add(tree[index * 2], tree[index]);
    add(tree[index * 2 + 1], tree[index]);
    tree[index] = M::identity;
  }
  void propagate(const size_t index) {
    if (index == 0)
      return;
    const size_t crz = countr_zero(index);
    for (size_t h = bit_width(index) - 1; h != crz; h -= 1)
      push(index >> h);
  }

public:
  dual_segment_tree() = default;
  explicit dual_segment_tree(const size_t n) : tree(n * 2, M::identity) {}

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

/**
 * @brief Dual Segment Tree
 * @see https://kimiyuki.net/blog/2019/02/21/dual-segment-tree/
 */
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
#line 7 "test/dual_segment_tree.test.cpp"

#include <iostream>

int main() {
#line 1 "other/fast_ios.cpp"
std::ios::sync_with_stdio(false);
std::cin.tie(nullptr);
#line 12 "test/dual_segment_tree.test.cpp"

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
      std::cout << dst.fold(i).value() << "\n";
    } break;
    }
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

