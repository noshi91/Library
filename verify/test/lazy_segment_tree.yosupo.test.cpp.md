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


# :heavy_check_mark: test/lazy_segment_tree.yosupo.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/lazy_segment_tree.yosupo.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-14 17:46:13+09:00


* see: <a href="https://judge.yosupo.jp/problem/range_affine_range_sum">https://judge.yosupo.jp/problem/range_affine_range_sum</a>


## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/lazy_segment_tree.cpp.html">data_structure/lazy_segment_tree.cpp</a>
* :heavy_check_mark: <a href="../../library/other/affine.cpp.html">other/affine.cpp</a>
* :heavy_check_mark: <a href="../../library/other/cartesian_product_monoid.cpp.html">other/cartesian_product_monoid.cpp</a>
* :heavy_check_mark: <a href="../../library/other/modint.cpp.html">other/modint.cpp</a>
* :heavy_check_mark: <a href="../../library/other/plus_monoid.cpp.html">other/plus_monoid.cpp</a>
* :heavy_check_mark: <a href="../../library/other/sum_affine_action.cpp.html">other/sum_affine_action.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include "data_structure/lazy_segment_tree.cpp"
#include "other/modint.cpp"
#include "other/sum_affine_action.cpp"

#include <iostream>

int main() {
  using mint = modint<998244353>;

  int n, q;
  std::cin >> n >> q;
  lazy_segment_tree<sum_affine_action<mint>> lst(n);
  for (int i = 0; i != n; i += 1) {
    int a;
    std::cin >> a;
    lst.update_point(i, {a, 1});
  }
  for (int i = 0; i != q; i += 1) {
    int t;
    std::cin >> t;
    switch (t) {
    case 0: {
      int l, r, b, c;
      std::cin >> l >> r >> b >> c;
      lst.update_range(l, r, {b, c});
    } break;
    case 1: {
      int l, r;
      std::cin >> l >> r;
      std::cout << lst.fold(l, r).first.value() << std::endl;
    } break;
    }
  }
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/lazy_segment_tree.yosupo.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

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
#line 1 "other/modint.cpp"
#include <cstdint>

template <std::uint_fast64_t Modulus> class modint {
  using u64 = std::uint_fast64_t;

public:
  using value_type = u64;

  static constexpr u64 mod = Modulus;

private:
  static_assert(mod < static_cast<u64>(1) << 32,
                "Modulus must be less than 2**32");

  u64 v;

  constexpr modint &negate() noexcept {
    if (v != 0)
      v = mod - v;
    return *this;
  }

public:
  constexpr modint(const u64 x = 0) noexcept : v(x % mod) {}
  constexpr u64 &value() noexcept { return v; }
  constexpr const u64 &value() const noexcept { return v; }
  constexpr modint operator+() const noexcept { return modint(*this); }
  constexpr modint operator-() const noexcept { return modint(*this).negate(); }
  constexpr modint operator+(const modint rhs) const noexcept {
    return modint(*this) += rhs;
  }
  constexpr modint operator-(const modint rhs) const noexcept {
    return modint(*this) -= rhs;
  }
  constexpr modint operator*(const modint rhs) const noexcept {
    return modint(*this) *= rhs;
  }
  constexpr modint operator/(const modint rhs) const noexcept {
    return modint(*this) /= rhs;
  }
  constexpr modint &operator+=(const modint rhs) noexcept {
    v += rhs.v;
    if (v >= mod)
      v -= mod;
    return *this;
  }
  constexpr modint &operator-=(const modint rhs) noexcept {
    if (v < rhs.v)
      v += mod;
    v -= rhs.v;
    return *this;
  }
  constexpr modint &operator*=(const modint rhs) noexcept {
    v = v * rhs.v % mod;
    return *this;
  }
  constexpr modint &operator/=(modint rhs) noexcept {
    u64 exp = mod - 2;
    while (exp != 0) {
      if (exp % 2 != 0)
        *this *= rhs;
      rhs *= rhs;
      exp /= 2;
    }
    return *this;
  }
};
template <std::uint_fast64_t Modulus>
constexpr typename modint<Modulus>::u64 modint<Modulus>::mod;
#line 1 "other/affine.cpp"
template <class T> class affine {
public:
  T a;
  T b;

  constexpr affine(const T &a = 1, const T &b = 0) noexcept : a(a), b(b) {}

  constexpr T evaluate(const T &x) const noexcept { return x * a + b; }
  friend constexpr affine operator+(const affine &l, const affine &r) noexcept {
    return affine(l.a + r.a, l.b + r.b);
  }
  constexpr affine composite(const affine &r) const noexcept {
    return affine(a * r.a, b * r.a + r.b);
  }
};

template <class T> class affine_composite_monoid {
public:
  using value_type = affine<T>;
  static constexpr value_type operation(const value_type &l,
                                        const value_type &r) noexcept {
    return l.composite(r);
  }
  static constexpr value_type identity{};
};
#line 1 "other/cartesian_product_monoid.cpp"
#include <utility>

template <class M, class N> class cartesian_product_monoid {
  using T = std::pair<typename M::value_type, typename N::value_type>;

public:
  using value_type = T;
  static constexpr T operation(const T &l, const T &r) noexcept {
    return T(M::operation(l.first, r.first), N::operation(l.second, r.second));
  }
  static constexpr T identity{M::identity, N::identity};
};
#line 1 "other/plus_monoid.cpp"
template <class T> class plus_monoid {
public:
  using value_type = T;
  static T operation(const T l, const T r) { return l + r; }
  static constexpr T identity = 0;
};
#line 4 "other/sum_affine_action.cpp"

template <class T> class sum_affine_action {
public:
  using value_structure =
      cartesian_product_monoid<plus_monoid<T>, plus_monoid<T>>;
  using operator_structure = affine_composite_monoid<T>;

private:
  using U = typename value_structure::value_type;
  using E = typename operator_structure::value_type;

public:
  static constexpr U operation(const U &l, const E &r) {
    return U(l.first * r.a + l.second * r.b, l.second);
  }
};
#line 6 "test/lazy_segment_tree.yosupo.test.cpp"

#include <iostream>

int main() {
  using mint = modint<998244353>;

  int n, q;
  std::cin >> n >> q;
  lazy_segment_tree<sum_affine_action<mint>> lst(n);
  for (int i = 0; i != n; i += 1) {
    int a;
    std::cin >> a;
    lst.update_point(i, {a, 1});
  }
  for (int i = 0; i != q; i += 1) {
    int t;
    std::cin >> t;
    switch (t) {
    case 0: {
      int l, r, b, c;
      std::cin >> l >> r >> b >> c;
      lst.update_range(l, r, {b, c});
    } break;
    case 1: {
      int l, r;
      std::cin >> l >> r;
      std::cout << lst.fold(l, r).first.value() << std::endl;
    } break;
    }
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

