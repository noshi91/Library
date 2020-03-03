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

* <a href="{{ site.github.repository_url }}/blob/master/test/axiotis_tzamos_unbounded_knapsack.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-03 16:21:51+09:00




## Depends on

* :heavy_check_mark: <a href="../../library/algorithm/axiotis_tzamos_unbounded_knapsack.cpp.html">Axiotis-Tzamos Unbounded Knapsack <small>(algorithm/axiotis_tzamos_unbounded_knapsack.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/algorithm/max_plus_convolution.cpp.html">Max Plus Convolution <small>(algorithm/max_plus_convolution.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/other/countl_zero64.cpp.html">other/countl_zero64.cpp</a>
* :heavy_check_mark: <a href="../../library/other/int_alias.cpp.html">other/int_alias.cpp</a>
* :heavy_check_mark: <a href="../../library/other/log2p164.cpp.html">other/log2p164.cpp</a>


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
  usize n, w;
  std::cin >> n >> w;
  struct item_t {
    i64 v, w;
  };
  std::vector<item_t> is(n);
  for (auto &e : is) {
    std::cin >> e.v >> e.w;
  }
  std::cout << axiotis_tzamos_unbounded_knapsack(w, is) << std::endl;
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
#line 1 "other/countl_zero64.cpp"
#include <array>
#include <cstddef>
#include <cstdint>

std::size_t countl_zero64(std::uint_fast64_t x) {
#ifdef __GNUC__
  return x == 0 ? 64 : __builtin_clzll(x);
#else
  if (x == 0)
    return 64;
  std::size_t ret = 0;
  if ((x & 0xFFFFFFFF00000000) != 0)
    x >>= 32;
  else
    ret += 32;
  if ((x & 0xFFFF0000) != 0)
    x >>= 16;
  else
    ret += 16;
  if ((x & 0xFF00) != 0)
    x >>= 8;
  else
    ret += 8;
  if ((x & 0xF0) != 0)
    x >>= 4;
  else
    ret += 4;
  if ((x & 0xC) != 0)
    x >>= 2;
  else
    ret += 2;
  if ((x & 0x2) != 0)
    x >>= 1;
  else
    ret += 1;
  return ret;
#endif
}
#line 2 "other/log2p164.cpp"

#include <cstddef>
#include <cstdint>

std::size_t log2p164(const std::uint_fast64_t x) {
  return 64 - countl_zero64(x);
}
#line 4 "algorithm/axiotis_tzamos_unbounded_knapsack.cpp"

#include <algorithm>
#include <cassert>
#include <vector>

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

  for (usize i = log2p164(t); i != 0; i -= 1) {
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
#include <vector>

int main() {
  usize n, w;
  std::cin >> n >> w;
  struct item_t {
    i64 v, w;
  };
  std::vector<item_t> is(n);
  for (auto &e : is) {
    std::cin >> e.v >> e.w;
  }
  std::cout << axiotis_tzamos_unbounded_knapsack(w, is) << std::endl;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

