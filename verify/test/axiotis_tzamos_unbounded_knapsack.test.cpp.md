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


# :heavy_check_mark: test/axiotis_tzamos_unbounded_knapsack.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/axiotis_tzamos_unbounded_knapsack.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-11 00:35:25+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_C&lang=ja">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_C&lang=ja</a>


## Depends on

* :heavy_check_mark: <a href="../../library/algorithm/axiotis_tzamos_unbounded_knapsack.cpp.html">Axiotis-Tzamos Unbounded Knapsack <small>(algorithm/axiotis_tzamos_unbounded_knapsack.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/algorithm/max_plus_convolution.cpp.html">Max Plus Convolution <small>(algorithm/max_plus_convolution.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/other/bit_width.cpp.html">other/bit_width.cpp</a>
* :heavy_check_mark: <a href="../../library/other/countl_zero.cpp.html">other/countl_zero.cpp</a>
* :heavy_check_mark: <a href="../../library/other/countr_zero.cpp.html">other/countr_zero.cpp</a>
* :heavy_check_mark: <a href="../../library/other/fast_ios.cpp.html">other/fast_ios.cpp</a>
* :heavy_check_mark: <a href="../../library/other/int_alias.cpp.html">other/int_alias.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_C&lang=ja"

#include "algorithm/axiotis_tzamos_unbounded_knapsack.cpp"
#include "other/int_alias.cpp"

#include <iostream>
#include <vector>

int main() {
#include "other/fast_ios.cpp"

  usize n, w;
  std::cin >> n >> w;
  struct item_t {
    i64 v, w;
  };
  std::vector<item_t> is(n);
  for (auto &e : is) {
    std::cin >> e.v >> e.w;
  }
  std::cout << axiotis_tzamos_unbounded_knapsack(w, is) << "\n";
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/axiotis_tzamos_unbounded_knapsack.test.cpp"
#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_C&lang=ja"

#line 2 "other/int_alias.cpp"

#include <cstddef>
#include <cstdint>

using i32 = std::int32_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using isize = std::ptrdiff_t;
using usize = std::size_t;
#line 2 "algorithm/max_plus_convolution.cpp"

#include <algorithm>
#include <vector>

template <class T>
std::vector<T> max_plus_convolution(const std::vector<T> &a,
                                    const std::vector<T> &b) {
  const usize n = a.size();
  const usize m = b.size();
  std::vector<T> c(n + m - 1, std::numeric_limits<T>::lowest());
  for (usize i = 0; i != n; i += 1) {
    for (usize j = 0; j != m; j += 1)
      c[i + j] = std::max(c[i + j], a[i] + b[j]);
  }
  return c;
}

/**
 * @brief Max Plus Convolution
 */
#line 2 "other/bit_width.cpp"

#line 2 "other/countl_zero.cpp"

#line 2 "other/countr_zero.cpp"

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
#line 4 "algorithm/axiotis_tzamos_unbounded_knapsack.cpp"

#line 6 "algorithm/axiotis_tzamos_unbounded_knapsack.cpp"
#include <cassert>
#line 8 "algorithm/axiotis_tzamos_unbounded_knapsack.cpp"

template <class I>
u64 axiotis_tzamos_unbounded_knapsack(const u64 t, const std::vector<I> &item) {
  assert(!item.empty());

  constexpr i64 minf = std::numeric_limits<i64>::lowest() / 2;

  usize m = 0;
  for (const I &e : item) {
    assert(e.w > 0);
    assert(e.v >= 0);

    m = std::max<usize>(m, e.w);
  }
  std::vector<i64> dp(m + 1, minf);
  dp[0] = 0;
  for (const I &e : item)
    dp[e.w] = std::max(dp[e.w], e.v);
  for (usize z = 1; z < m; z *= 2) {
    dp = max_plus_convolution(dp, dp);
    dp.resize(m + 1);
  }
  {
    const std::vector<i64> temp(m, minf);
    dp.insert(dp.begin(), temp.begin(), temp.end());
  }

  for (usize i = bit_width(t); i != 0; i -= 1) {
    dp = max_plus_convolution(dp, dp);
    auto itr = dp.begin() + 2 * m;
    if ((t >> i - 1) % 2 == 1)
      itr += 1;
    dp = std::vector<i64>(itr - m, itr + m + 1);
  }
  return *std::max_element(dp.begin(), dp.begin() + m + 1);
}

/**
 * @brief Axiotis-Tzamos Unbounded Knapsack
 * @see https://arxiv.org/abs/1802.06440
 */
#line 6 "test/axiotis_tzamos_unbounded_knapsack.test.cpp"

#include <iostream>
#line 9 "test/axiotis_tzamos_unbounded_knapsack.test.cpp"

int main() {
#line 1 "other/fast_ios.cpp"
std::ios::sync_with_stdio(false);
std::cin.tie(nullptr);
#line 12 "test/axiotis_tzamos_unbounded_knapsack.test.cpp"

  usize n, w;
  std::cin >> n >> w;
  struct item_t {
    i64 v, w;
  };
  std::vector<item_t> is(n);
  for (auto &e : is) {
    std::cin >> e.v >> e.w;
  }
  std::cout << axiotis_tzamos_unbounded_knapsack(w, is) << "\n";
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

