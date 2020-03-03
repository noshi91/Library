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


# :heavy_check_mark: SMAWK Algorithm <small>(algorithm/smawk.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed469618898d75b149e5c7c4b6a1c415">algorithm</a>
* <a href="{{ site.github.repository_url }}/blob/master/algorithm/smawk.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-03 19:32:01+09:00


* see: <a href="https://link.springer.com/article/10.1007/BF01840359">https://link.springer.com/article/10.1007/BF01840359</a>


## 入力
$N \times M$ 行列 $A$
-   $A$ は totally monotone

## 出力
$0 \le i \lt N$ について $\argmax_{0 \le j \lt M}A_{i,j}$

## 計算量
-   時間計算量 $\Theta(N+M)$
-   空間計算量 $\Theta(N+M)$

## 説明
$N \times M$ 行列 $A$ について、いずれかの行で最大値を取り得る高々 $N$ 個の列を $\Theta(N+M)$ で取り出すアルゴリズムが存在する。(reduce)
$1$ つ飛ばしに $N/2$ 個程度の行を取り出し、reduce することで $N,M$ 共に半分になった問題を解く。
monotone 性から、飛ばした行の $\argmax$ を復元する。(interpolate)

## 定義
$\argmin$ による定義も存在するので注意。

#### monotone
$A$ が monotone であるとは
$\forall i \lt j, \argmax A_{i,*} \le \argmax A_{j,*}$
が成り立つことを指す。
ただし適切な tie-break により $\argmax$ は $1$ つに定まるとする。

#### totally monotone
$A$ が totally monotone であるとは、その任意の部分行列が monotone であることを指す。
同値な定義に「$A$ の任意の $2\times 2$ 部分行列が monotone」がある。

## 文献
-   https://topcoder-g-hatena-ne-jp.jag-icpc.org/spaghetti_source/20120923/
    -   週刊 spaghetti_source
    -   日本語

-   http://web.cs.unlv.edu/larmore/Courses/CSC477/monge.pdf
    -   具体例が図示されており分かりやすい

-   https://link.springer.com/article/10.1007%2FBF01840359
    -   SMAWK Algorithm が提案された論文

## その他
-   実装例の引数 $\rm select$ の定義
${\rm select}(i,j,k) \coloneqq A_{i,j}$ と $A_{i,k}$ $(j \lt k)$ を比較して、後者を選ぶ


## Depends on

* :heavy_check_mark: <a href="../other/int_alias.cpp.html">other/int_alias.cpp</a>


## Required by

* :heavy_check_mark: <a href="axiotis_tzamos_knapsack.cpp.html">Axiotis-Tzamos Knapsack <small>(algorithm/axiotis_tzamos_knapsack.cpp)</small></a>
* :heavy_check_mark: <a href="concave_max_plus_convolution.cpp.html">Concave Max Plus Convlution <small>(algorithm/concave_max_plus_convolution.cpp)</small></a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/axiotis_tzamos_knapsack.test.cpp.html">test/axiotis_tzamos_knapsack.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "other/int_alias.cpp"

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
 * @see https://link.springer.com/article/10.1007/BF01840359
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
