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


# :heavy_check_mark: test/zeta_transform.aoj.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/zeta_transform.aoj.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-23 00:23:42+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3119">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3119</a>


## Depends on

* :heavy_check_mark: <a href="../../library/algorithm/zeta_transform.cpp.html">algorithm/zeta_transform.cpp</a>
* :heavy_check_mark: <a href="../../library/other/modint.cpp.html">other/modint.cpp</a>
* :heavy_check_mark: <a href="../../library/other/multiplies_monoid.cpp.html">other/multiplies_monoid.cpp</a>
* :heavy_check_mark: <a href="../../library/other/plus_group.cpp.html">other/plus_group.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3119"

#include "algorithm/zeta_transform.cpp"
#include "other/modint.cpp"
#include "other/multiplies_monoid.cpp"
#include "other/plus_group.cpp"

#include <iostream>

int main() {
  using mint = modint<1000000007>;
  constexpr int b = 20;

  int n;
  std::cin >> n;
  std::vector<mint> v(1 << b, 1);
  for (int i = 0; i != n; i += 1) {
    int a;
    std::cin >> a;
    v[a] *= 2;
  }
  superset_zeta_transform<multiplies_monoid<mint>>(v);
  for (mint &e : v)
    e -= 1;
  superset_mobius_transform<plus_group<mint>>(v);
  std::cout << v[0].value() << std::endl;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/zeta_transform.aoj.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3119"

#line 1 "algorithm/zeta_transform.cpp"
#include <cstddef>
#include <vector>

template <class S>
void subset_zeta_transform(std::vector<typename S::value_type> &a) {
  using size_t = std::size_t;

  const size_t n = a.size();
  for (size_t i = 1; i < n; i *= 2) {
    for (size_t j = 0; j != n; j += 1) {
      if ((j & i) != 0)
        a[j] = S::operation(a[j & ~i], a[j]);
    }
  }
}

template <class S>
void superset_zeta_transform(std::vector<typename S::value_type> &a) {
  using size_t = std::size_t;

  const size_t n = a.size();
  for (size_t i = 1; i < n; i *= 2) {
    for (size_t j = 0; j != n; j += 1) {
      if ((j & i) != 0)
        a[j & ~i] = S::operation(a[j & ~i], a[j]);
    }
  }
}

template <class G>
void subset_mobius_transform(std::vector<typename G::value_type> &a) {
  using size_t = std::size_t;

  const size_t n = a.size();
  size_t i = 1;
  while (i < n)
    i *= 2;
  while (i != 1) {
    i /= 2;
    for (size_t j = 0; j != n; j += 1) {
      if ((j & i) != 0)
        a[j] = G::operation(G::inverse(a[j & ~i]), a[j]);
    }
  }
}

template <class G>
void superset_mobius_transform(std::vector<typename G::value_type> &a) {
  using size_t = std::size_t;

  const size_t n = a.size();
  size_t i = 1;
  while (i < n)
    i *= 2;
  while (i != 1) {
    i /= 2;
    for (size_t j = 0; j != n; j += 1) {
      if ((j & i) != 0)
        a[j & ~i] = G::operation(a[j & ~i], G::inverse(a[j]));
    }
  }
}
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
#line 1 "other/multiplies_monoid.cpp"
template <class T> class multiplies_monoid {
public:
  using value_type = T;
  static constexpr T operation(const T &l, const T &r) noexcept {
    return l * r;
  }
  static constexpr T identity = 1;
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
#line 7 "test/zeta_transform.aoj.test.cpp"

#include <iostream>

int main() {
  using mint = modint<1000000007>;
  constexpr int b = 20;

  int n;
  std::cin >> n;
  std::vector<mint> v(1 << b, 1);
  for (int i = 0; i != n; i += 1) {
    int a;
    std::cin >> a;
    v[a] *= 2;
  }
  superset_zeta_transform<multiplies_monoid<mint>>(v);
  for (mint &e : v)
    e -= 1;
  superset_mobius_transform<plus_group<mint>>(v);
  std::cout << v[0].value() << std::endl;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

