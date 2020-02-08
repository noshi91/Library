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


# :heavy_check_mark: test/segment_tree.yosupo.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/segment_tree.yosupo.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-09 00:25:15+09:00


* see: <a href="https://judge.yosupo.jp/problem/point_set_range_composite">https://judge.yosupo.jp/problem/point_set_range_composite</a>


## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/segment_tree.cpp.html">data_structure/segment_tree.cpp</a>
* :heavy_check_mark: <a href="../../library/other/affine.cpp.html">other/affine.cpp</a>
* :heavy_check_mark: <a href="../../library/other/modint.cpp.html">other/modint.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include "data_structure/segment_tree.cpp"
#include "other/affine.cpp"
#include "other/modint.cpp"

#include <iostream>

int main() {
  int n, q;
  std::cin >> n >> q;
  segment_tree<affine_composite_monoid<modint<998244353>>> st(n);
  for (int i = 0; i != n; i += 1) {
    int a, b;
    std::cin >> a >> b;
    st.update(i, {a, b});
  }
  for (int i = 0; i != q; i += 1) {
    int t;
    std::cin >> t;
    switch (t) {
    case 0: {
      int p, c, d;
      std::cin >> p >> c >> d;
      st.update(p, {c, d});
    } break;
    case 1: {
      int l, r, x;
      std::cin >> l >> r >> x;
      std::cout << st.fold(l, r).evaluate(x).value() << std::endl;
    } break;
    }
  }
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/segment_tree.yosupo.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#line 1 "data_structure/segment_tree.cpp"
#include <cassert>
#include <cstddef>
#include <vector>

template <class Monoid> class segment_tree {
public:
  using T = typename Monoid::value_type;
  using size_t = std::size_t;

private:
  std::vector<T> tree;

  template <class F>
  size_t search_subtree(size_t index, const F f, T fold_l) const {
    while (index < size()) {
      const T temp = Monoid::operation(fold_l, tree[index * 2]);
      if (!f(temp)) {
        index = index * 2;
      } else {
        fold_l = temp;
        index = index * 2 + 1;
      }
    }
    return index - size();
  }

public:
  segment_tree() = default;
  explicit segment_tree(const size_t n) : tree(n * 2, Monoid::identity) {}

  size_t size() const noexcept { return tree.size() / 2; }

  T fold(size_t first, size_t last) const {
    assert(first <= last);
    assert(last <= size());
    first += size();
    last += size();
    T fold_l = Monoid::identity;
    T fold_r = Monoid::identity;
    while (first != last) {
      if (first % 2 != 0) {
        fold_l = Monoid::operation(fold_l, tree[first]);
        first += 1;
      }
      first /= 2;
      if (last % 2 != 0) {
        last -= 1;
        fold_r = Monoid::operation(tree[last], fold_r);
      }
      last /= 2;
    }
    return Monoid::operation(fold_l, fold_r);
  }
  template <class F> size_t search(size_t first, size_t last, const F f) const {
    assert(first <= last);
    assert(last <= size());
    first += size();
    last += size();
    const size_t last_cp = last;
    size_t shift = 0;
    T fold_l = Monoid::identity;
    while (first != last) {
      if (first % 2 != 0) {
        const T temp = Monoid::operation(fold_l, tree[first]);
        if (!f(temp))
          return search_subtree(first, f, fold_l);
        fold_l = temp;
        first += 1;
      }
      first /= 2;
      last /= 2;
      shift += 1;
    }
    while (shift != 0) {
      shift -= 1;
      last = last_cp >> shift;
      if (last % 2 != 0) {
        last -= 1;
        const T temp = Monoid::operation(fold_l, tree[last]);
        if (!f(temp))
          return search_subtree(last, f, fold_l);
        fold_l = temp;
      }
    }
    return last_cp - size();
  }

  void update(size_t index, const T x) {
    assert(index < size());
    index += size();
    tree[index] = x;
    while (index != 1) {
      index /= 2;
      tree[index] = Monoid::operation(tree[index * 2], tree[index * 2 + 1]);
    }
  }
};
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
#line 6 "test/segment_tree.yosupo.test.cpp"

#include <iostream>

int main() {
  int n, q;
  std::cin >> n >> q;
  segment_tree<affine_composite_monoid<modint<998244353>>> st(n);
  for (int i = 0; i != n; i += 1) {
    int a, b;
    std::cin >> a >> b;
    st.update(i, {a, b});
  }
  for (int i = 0; i != q; i += 1) {
    int t;
    std::cin >> t;
    switch (t) {
    case 0: {
      int p, c, d;
      std::cin >> p >> c >> d;
      st.update(p, {c, d});
    } break;
    case 1: {
      int l, r, x;
      std::cin >> l >> r >> x;
      std::cout << st.fold(l, r).evaluate(x).value() << std::endl;
    } break;
    }
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

