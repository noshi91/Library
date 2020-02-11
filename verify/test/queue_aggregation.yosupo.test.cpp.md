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


# :heavy_check_mark: test/queue_aggregation.yosupo.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/queue_aggregation.yosupo.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-11 11:45:48+09:00


* see: <a href="https://judge.yosupo.jp/problem/queue_operate_all_composite">https://judge.yosupo.jp/problem/queue_operate_all_composite</a>


## Depends on

* :heavy_check_mark: <a href="../../library/data_structure/queue_aggregation.cpp.html">data_structure/queue_aggregation.cpp</a>
* :heavy_check_mark: <a href="../../library/data_structure/stack_aggregation.cpp.html">data_structure/stack_aggregation.cpp</a>
* :heavy_check_mark: <a href="../../library/other/affine.cpp.html">other/affine.cpp</a>
* :heavy_check_mark: <a href="../../library/other/modint.cpp.html">other/modint.cpp</a>
* :heavy_check_mark: <a href="../../library/other/opposite_monoid.cpp.html">other/opposite_monoid.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"

#include "data_structure/queue_aggregation.cpp"
#include "other/affine.cpp"
#include "other/modint.cpp"

#include <iostream>

int main() {
  queue_aggregation<affine_composite_monoid<modint<998244353>>> qa;

  int q;
  std::cin >> q;

  for (int i = 0; i != q; i += 1) {
    int t;
    std::cin >> t;
    switch (t) {
    case 0: {
      int a, b;
      std::cin >> a >> b;
      qa.push({a, b});
    } break;
    case 1: {
      qa.pop();
    } break;
    case 2: {
      int x;
      std::cin >> x;
      std::cout << qa.fold().evaluate(x).value() << std::endl;
    } break;
    }
  }
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/queue_aggregation.yosupo.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"

#line 1 "data_structure/stack_aggregation.cpp"
#include <cassert>
#include <stack>

template <class M> class stack_aggregation {
  using T = typename M::value_type;

  class node_type {
  public:
    T value;
    T fold;

    node_type(const T value, const T fold) : value(value), fold(fold) {}
  };

  std::stack<node_type> st;

public:
  stack_aggregation() = default;

  bool empty() const { return st.empty(); }
  T top() const {
    assert(!empty());
    return st.top().value;
  }
  T fold() const { return st.empty() ? M::identity : st.top().fold; }

  void push(const T x) { st.push(node_type(x, M::operation(fold(), x))); }
  void pop() {
    assert(!empty());
    st.pop();
  }
};
#line 1 "other/opposite_monoid.cpp"
template <class M> class opposite_monoid {
  using T = typename M::value_type;

public:
  using value_type = T;
  static constexpr T operation(const T &l, const T &r) noexcept {
    return M::operation(r, l);
  }
  static constexpr T identity = M::identity;
};
#line 3 "data_structure/queue_aggregation.cpp"

template <class M> class queue_aggregation {
  using T = typename M::value_type;

  stack_aggregation<opposite_monoid<M>> front_st;
  stack_aggregation<M> back_st;

public:
  queue_aggregation() = default;

  bool empty() const { return front_st.empty(); }
  T fold() const { return M::operation(front_st.fold(), back_st.fold()); }

  void push(const T x) {
    if (empty())
      front_st.push(x);
    else
      back_st.push(x);
  }
  void pop() {
    assert(!empty());
    front_st.pop();
    if (front_st.empty()) {
      while (!back_st.empty()) {
        front_st.push(back_st.top());
        back_st.pop();
      }
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
#line 6 "test/queue_aggregation.yosupo.test.cpp"

#include <iostream>

int main() {
  queue_aggregation<affine_composite_monoid<modint<998244353>>> qa;

  int q;
  std::cin >> q;

  for (int i = 0; i != q; i += 1) {
    int t;
    std::cin >> t;
    switch (t) {
    case 0: {
      int a, b;
      std::cin >> a >> b;
      qa.push({a, b});
    } break;
    case 1: {
      qa.pop();
    } break;
    case 2: {
      int x;
      std::cin >> x;
      std::cout << qa.fold().evaluate(x).value() << std::endl;
    } break;
    }
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

