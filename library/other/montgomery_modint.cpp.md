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


# :warning: other/montgomery_modint.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#795f3202b17cb6bc3d4b771d8c6c9eaf">other</a>
* <a href="{{ site.github.repository_url }}/blob/master/other/montgomery_modint.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-06 19:32:54+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/*
reference: https://min-25.hatenablog.com/entry/2017/08/20/171214
*/

#include <cassert>
#include <cstdint>
#include <limits>
#include <utility>

class montgomery_modint {
  using Self = montgomery_modint;

  using u64 = std::uint64_t;
  using u32 = std::uint32_t;
  using i32 = std::int32_t;

  static u32 mod;
  static u32 inv;
  static u32 r2;

  static u32 reduce(const u64 x) noexcept {
    const u32 y = u32(x >> 32) - u32(u64(u32(x) * inv) * mod >> 32);
    return i32(y) < 0 ? y + mod : y;
  }

  u32 v;

public:
  montgomery_modint(const u32 x = 0) noexcept : v(reduce(u64(x) * r2)) {}

  u32 value() const noexcept { return reduce(v); }

  Self operator+(const Self r) const noexcept { return Self(*this) += r; }
  Self operator-(const Self r) const noexcept { return Self(*this) -= r; }
  Self operator*(const Self r) const noexcept { return Self(*this) *= r; }
  Self operator/(const Self r) const noexcept { return Self(*this) /= r; }

  Self &operator+=(const Self r) noexcept {
    v += r.v;
    if (v >= mod)
      v -= mod;
    return *this;
  }
  Self &operator-=(const Self r) noexcept {
    if (v < r.v)
      v += mod;
    v -= r.v;
    return *this;
  }
  Self &operator*=(const Self r) noexcept {
    v = reduce(u64(v) * r.v);
    return *this;
  }
  Self &operator/=(const Self r) noexcept {
    u32 a = mod;
    u32 b = reduce(reduce(r.v));
    u32 s = 0;
    u32 t = 1;
    while (b != 1) {
      const u32 q = a / b;
      std::swap(a -= q * b, b);
      std::swap(s -= q * t, t);
    }
    if (i32(t) < 0)
      t += mod;
    v = reduce(u64(v) * t);
    return *this;
  }

  static void set_mod(const u32 m) noexcept {
    assert(m < u32(1) << 31);
    assert(m % 2 == 1);
    mod = m;
    inv = m;
    for (u32 i = 0; i != 4; i += 1)
      inv *= u32(2) - inv * m;
    r2 = -u64(m) % m;
  }
  static u32 get_mod() noexcept { return mod; }
};
typename montgomery_modint::u32 montgomery_modint::mod;
typename montgomery_modint::u32 montgomery_modint::inv;
typename montgomery_modint::u32 montgomery_modint::r2;
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "other/montgomery_modint.cpp"
/*
reference: https://min-25.hatenablog.com/entry/2017/08/20/171214
*/

#include <cassert>
#include <cstdint>
#include <limits>
#include <utility>

class montgomery_modint {
  using Self = montgomery_modint;

  using u64 = std::uint64_t;
  using u32 = std::uint32_t;
  using i32 = std::int32_t;

  static u32 mod;
  static u32 inv;
  static u32 r2;

  static u32 reduce(const u64 x) noexcept {
    const u32 y = u32(x >> 32) - u32(u64(u32(x) * inv) * mod >> 32);
    return i32(y) < 0 ? y + mod : y;
  }

  u32 v;

public:
  montgomery_modint(const u32 x = 0) noexcept : v(reduce(u64(x) * r2)) {}

  u32 value() const noexcept { return reduce(v); }

  Self operator+(const Self r) const noexcept { return Self(*this) += r; }
  Self operator-(const Self r) const noexcept { return Self(*this) -= r; }
  Self operator*(const Self r) const noexcept { return Self(*this) *= r; }
  Self operator/(const Self r) const noexcept { return Self(*this) /= r; }

  Self &operator+=(const Self r) noexcept {
    v += r.v;
    if (v >= mod)
      v -= mod;
    return *this;
  }
  Self &operator-=(const Self r) noexcept {
    if (v < r.v)
      v += mod;
    v -= r.v;
    return *this;
  }
  Self &operator*=(const Self r) noexcept {
    v = reduce(u64(v) * r.v);
    return *this;
  }
  Self &operator/=(const Self r) noexcept {
    u32 a = mod;
    u32 b = reduce(reduce(r.v));
    u32 s = 0;
    u32 t = 1;
    while (b != 1) {
      const u32 q = a / b;
      std::swap(a -= q * b, b);
      std::swap(s -= q * t, t);
    }
    if (i32(t) < 0)
      t += mod;
    v = reduce(u64(v) * t);
    return *this;
  }

  static void set_mod(const u32 m) noexcept {
    assert(m < u32(1) << 31);
    assert(m % 2 == 1);
    mod = m;
    inv = m;
    for (u32 i = 0; i != 4; i += 1)
      inv *= u32(2) - inv * m;
    r2 = -u64(m) % m;
  }
  static u32 get_mod() noexcept { return mod; }
};
typename montgomery_modint::u32 montgomery_modint::mod;
typename montgomery_modint::u32 montgomery_modint::inv;
typename montgomery_modint::u32 montgomery_modint::r2;

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

