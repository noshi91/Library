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


# :heavy_check_mark: Radix Heap <small>(data_structure/radix_heap.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#c8f6850ec2ec3fb32f203c1f4e3c2fd2">data_structure</a>
* <a href="{{ site.github.repository_url }}/blob/master/data_structure/radix_heap.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-11 00:35:25+09:00


* see: <a href="https://yosupo.hatenablog.com/entry/2015/04/03/224649">https://yosupo.hatenablog.com/entry/2015/04/03/224649</a>


## Depends on

* :heavy_check_mark: <a href="../other/bit_width.cpp.html">other/bit_width.cpp</a>
* :heavy_check_mark: <a href="../other/countl_zero.cpp.html">other/countl_zero.cpp</a>
* :heavy_check_mark: <a href="../other/countr_zero.cpp.html">other/countr_zero.cpp</a>
* :heavy_check_mark: <a href="../other/int_alias.cpp.html">other/int_alias.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/radix_heap.test.cpp.html">test/radix_heap.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "other/bit_width.cpp"
#include "other/int_alias.cpp"

#include <algorithm>
#include <cassert>
#include <limits>
#include <utility>
#include <vector>

template <class T> class radix_heap {
  using V = std::pair<u64, T>;

public:
  using key_type = u64;
  using mapped_type = T;
  using value_type = V;

private:
  std::vector<std::vector<V>> u;
  u64 last;

public:
  radix_heap() : u(), last(0) {}

  void push(V x) {
    assert(last <= x.first);

    const usize i = bit_width(x.first ^ last);
    if (u.size() <= i)
      u.resize(i + 1);
    u[i].push_back(std::move(x));
  }

  V pop() {
    if (u[0].empty()) {
      usize i = 1;
      while (u[i].empty())
        i += 1;
      last = std::numeric_limits<u64>::max();
      for (const V &e : u[i])
        last = std::min(last, e.first);
      for (V &e : u[i]) {
        const usize j = bit_width(e.first ^ last);
        u[j].push_back(std::move(e));
      }
      u[i].clear();
    }
    V ret = std::move(u[0].back());
    u[0].pop_back();
    return ret;
  }
};

/**
 * @brief Radix Heap
 * @see https://yosupo.hatenablog.com/entry/2015/04/03/224649
 */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
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
#line 3 "data_structure/radix_heap.cpp"

#include <algorithm>
#include <cassert>
#include <limits>
#include <utility>
#include <vector>

template <class T> class radix_heap {
  using V = std::pair<u64, T>;

public:
  using key_type = u64;
  using mapped_type = T;
  using value_type = V;

private:
  std::vector<std::vector<V>> u;
  u64 last;

public:
  radix_heap() : u(), last(0) {}

  void push(V x) {
    assert(last <= x.first);

    const usize i = bit_width(x.first ^ last);
    if (u.size() <= i)
      u.resize(i + 1);
    u[i].push_back(std::move(x));
  }

  V pop() {
    if (u[0].empty()) {
      usize i = 1;
      while (u[i].empty())
        i += 1;
      last = std::numeric_limits<u64>::max();
      for (const V &e : u[i])
        last = std::min(last, e.first);
      for (V &e : u[i]) {
        const usize j = bit_width(e.first ^ last);
        u[j].push_back(std::move(e));
      }
      u[i].clear();
    }
    V ret = std::move(u[0].back());
    u[0].pop_back();
    return ret;
  }
};

/**
 * @brief Radix Heap
 * @see https://yosupo.hatenablog.com/entry/2015/04/03/224649
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

