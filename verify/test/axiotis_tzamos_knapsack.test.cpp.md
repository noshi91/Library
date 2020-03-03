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


# :heavy_check_mark: test/axiotis_tzamos_knapsack.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/axiotis_tzamos_knapsack.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-03 19:32:01+09:00




## Depends on

* :heavy_check_mark: <a href="../../library/algorithm/axiotis_tzamos_knapsack.cpp.html">Axiotis-Tzamos Knapsack <small>(algorithm/axiotis_tzamos_knapsack.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/algorithm/concave_max_plus_convolution.cpp.html">Concave Max Plus Convlution <small>(algorithm/concave_max_plus_convolution.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/algorithm/smawk.cpp.html">SMAWK Algorithm <small>(algorithm/smawk.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/other/ceildiv.cpp.html">other/ceildiv.cpp</a>
* :heavy_check_mark: <a href="../../library/other/int_alias.cpp.html">other/int_alias.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_B&lang=ja"

#include "algorithm/axiotis_tzamos_knapsack.cpp"
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
  std::cout << axiotis_tzamos_knapsack(w, is) << std::endl;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/axiotis_tzamos_knapsack.test.cpp"
#define PROBLEM                                                                \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_B&lang=ja"

#line 2 "other/int_alias.cpp"

#include <cstddef>
#include <cstdint>

using i32 = std::int32_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using isize = std::ptrdiff_t;
using usize = std::size_t;
#line 2 "algorithm/smawk.cpp"

#include <functional>
#include <numeric>
#include <vector>

template <class Select>
std::vector<usize> smawk(const usize row_size, const usize col_size,
                         const Select &select) {
  using vec_zu = std::vector<usize>;

  const std::function<vec_zu(const vec_zu &, const vec_zu &)> solve =
      [&](const vec_zu &row, const vec_zu &col) -> vec_zu {
    const usize n = row.size();
    if (n == 0)
      return {};
    vec_zu c2;
    for (const usize i : col) {
      while (!c2.empty() && select(row[c2.size() - 1], c2.back(), i))
        c2.pop_back();
      if (c2.size() < n)
        c2.push_back(i);
    }
    vec_zu r2;
    for (usize i = 1; i < n; i += 2)
      r2.push_back(row[i]);
    const vec_zu a2 = solve(r2, c2);
    vec_zu ans(n);
    for (usize i = 0; i != a2.size(); i += 1)
      ans[i * 2 + 1] = a2[i];
    usize j = 0;
    for (usize i = 0; i < n; i += 2) {
      ans[i] = c2[j];
      const usize end = i + 1 == n ? c2.back() : ans[i + 1];
      while (c2[j] != end) {
        j += 1;
        if (select(row[i], ans[i], c2[j]))
          ans[i] = c2[j];
      }
    }
    return ans;
  };
  vec_zu row(row_size);
  std::iota(row.begin(), row.end(), 0);
  vec_zu col(col_size);
  std::iota(col.begin(), col.end(), 0);
  return solve(row, col);
}

/**
 * @brief SMAWK Algorithm
 * @docs docs/smawk.md
 * @see https://link.springer.com/article/10.1007/BF01840359
 */
#line 3 "algorithm/concave_max_plus_convolution.cpp"

#include <vector>

template <class T>
std::vector<T> concave_max_plus_convolution(const std::vector<T> &a,
                                            const std::vector<T> &b) {
  const usize n = a.size();
  const usize m = b.size();
  const auto get = [&](const usize i, const usize j) {
    return a[j] + b[i - j];
  };
  const auto select = [&](const usize i, const usize j, const usize k) {
    if (i < k)
      return false;
    if (i - j >= m)
      return true;
    return get(i, j) <= get(i, k);
  };
  const std::vector<usize> amax = smawk(n + m - 1, n, select);
  std::vector<T> c(n + m - 1);
  for (usize i = 0; i != n + m - 1; i += 1)
    c[i] = get(i, amax[i]);
  return c;
}

/**
 * @brief Concave Max Plus Convlution
 * @see https://arxiv.org/abs/1802.06440
 */
#line 1 "other/ceildiv.cpp"
template <class T> T ceildiv(const T &n, const T &d) {
  return n / d + (n % d != 0 ? 1 : 0);
}
#line 4 "algorithm/axiotis_tzamos_knapsack.cpp"

#include <algorithm>
#include <cassert>
#include <functional>
#include <utility>
#include <vector>

template <class I>
u64 axiotis_tzamos_knapsack(const usize t, const std::vector<I> &item) {
  std::vector<std::vector<i64>> bucket(t + 1);
  for (const I &e : item) {
    assert(e.w > 0);
    assert(e.v >= 0);

    if (e.w <= t)
      bucket[e.w].push_back(e.v);
  }

  std::vector<i64> dp(t + 1, std::numeric_limits<i64>::lowest());
  dp[0] = 0;
  for (usize w = 1; w <= t; w += 1) {
    std::vector<i64> &list = bucket[w];
    if (list.empty())
      continue;
    std::sort(list.begin(), list.end(), std::greater<i64>());
    const usize m = std::min(list.size(), t / w);
    std::vector<i64> sum(m + 1);
    sum[0] = 0;
    for (usize i = 0; i != m; i += 1)
      sum[i + 1] = sum[i] + list[i];
    for (usize k = 0; k != w; k += 1) {
      const usize n = (t - k) / w + 1;
      std::vector<i64> v(n);
      for (usize i = 0; i != n; i += 1)
        v[i] = dp[i * w + k];
      const std::vector<i64> res = concave_max_plus_convolution(v, sum);
      for (usize i = 0; i != n; i += 1)
        dp[i * w + k] = res[i];
    }
  }
  return *std::max_element(dp.begin(), dp.end());
}

/**
 * @brief Axiotis-Tzamos Knapsack
 * @see https://arxiv.org/abs/1802.06440
 */
#line 6 "test/axiotis_tzamos_knapsack.test.cpp"

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
  std::cout << axiotis_tzamos_knapsack(w, is) << std::endl;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

