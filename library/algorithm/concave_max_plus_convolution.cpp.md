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


# :heavy_check_mark: Concave Max Plus Convlution <small>(algorithm/concave_max_plus_convolution.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed469618898d75b149e5c7c4b6a1c415">algorithm</a>
* <a href="{{ site.github.repository_url }}/blob/master/algorithm/concave_max_plus_convolution.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-03 23:12:43+09:00




## 入力
長さ $N$ の列 $A$  
長さ $M$ の列 $B$
-   $B$ は上に凸

## 出力
$C_i \mathrel := \max \limits _ j \lbrace A _ {i - j} + B _ j \rbrace$

で定義される長さ $N + M - 1$ の列 $C$

## 計算量
-   時間計算量 $\Theta ( N + M )$
-   空間計算量 $\Theta ( N + M )$

## 説明
$( N + M ) \times M$ 行列 $X$ を以下のように定義する。

$X _ {i , j} \mathrel := A _ {i - j} + B _ j$

ただし $i \lt j$ あるいは $M \le j$ の場合は $- \infty$ とする。(詳細略、実装を参照)  
目的は $C _ i = \max \limits _ j X _ {i , j}$ を計算することである。  
$B$ が上に凸であることから $X$ は monge であり、すなわち totally monotone。よって[SMAWK Algorithm](https://noshi91.github.io/Library/library/algorithm/smawk.cpp.html) を用いると $\Theta ( N + M )$ で計算可能。

## 文献
-   [Capacitated Dynamic Programming: Faster Knapsack and Graph Algorithms](https://arxiv.org/abs/1802.06440)  
    [Axiotis-Tzamos Knapsack](https://noshi91.github.io/Library/library/algorithm/axiotis_tzamos_knapsack.cpp.html) で使用されている


## Depends on

* :heavy_check_mark: <a href="smawk.cpp.html">SMAWK Algorithm <small>(algorithm/smawk.cpp)</small></a>
* :heavy_check_mark: <a href="../other/int_alias.cpp.html">other/int_alias.cpp</a>


## Required by

* :heavy_check_mark: <a href="axiotis_tzamos_knapsack.cpp.html">Axiotis-Tzamos Knapsack <small>(algorithm/axiotis_tzamos_knapsack.cpp)</small></a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/axiotis_tzamos_knapsack.test.cpp.html">test/axiotis_tzamos_knapsack.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "algorithm/smawk.cpp"
#include "other/int_alias.cpp"

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
 * @docs docs/concave_max_plus_convolution.md
 */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
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
 * @docs docs/concave_max_plus_convolution.md
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

