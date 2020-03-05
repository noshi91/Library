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


# :heavy_check_mark: Axiotis-Tzamos Knapsack <small>(algorithm/axiotis_tzamos_knapsack.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed469618898d75b149e5c7c4b6a1c415">algorithm</a>
* <a href="{{ site.github.repository_url }}/blob/master/algorithm/axiotis_tzamos_knapsack.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-05 22:38:55+09:00




## 入力
非負整数 $T$  
長さ $N$ の正整数列 $w$  
長さ $N$ の非負整数列 $v$  

## 出力
$x _ i \in \lbrace 0 , 1 \rbrace$

$\displaystyle \sum x _ i w _ i \le T$

を満たす列 $x$ について

$\displaystyle \sum x _ i v _ i$

の最大値

## 計算量
$D$ を $w$ の種類数とする
-   時間計算量 $O ( N \log ( N ) + T D )$
-   空間計算量 $\Theta ( N + T )$

## 説明
${\rm dp} \lbrack i \rbrack \mathrel := w$ の総和 $i$ で達成される $v$ の総和の最大値

最初

${\rm dp} \lbrack i \rbrack = \begin{cases} 0 & ( i = 0 ) \newline - \infty & ( i \neq 0 ) \end{cases}$

であり、各 $w ^ \prime$ について $w _ j = w ^ \prime$ となる $j$ でまとめて $\rm dp$ を更新していく。そのような $j$ について $v _ j$ を降順にソートした列を $v ^ \prime$ とすると、$\rm dp$ の更新は以下のように表せる。

$\displaystyle {\rm dp} \lbrack i \rbrack \leftarrow \max \limits _ k \lbrace {\rm dp} \lbrack i - k w ^ \prime \rbrack + \sum \limits _ {0 \le l \lt k} v ^ \prime _ l \rbrace$

これは $\rm dp$ を $w ^ \prime$ 間隔で取り出した列に $v ^ \prime$ の累積和を (max,+)-convolution する操作である。$v ^ \prime$ が広義単調減少であるから、その累積和は上に凸である。よって [Concave Max Plus Convolution](https://noshi91.github.io/Library/library/algorithm/concave_max_plus_convolution.cpp.html) を用いて高速に計算することが出来る。  
$1$ 回の更新につきソートと加えて $\Theta ( T )$ 掛かるため、全体では $O ( N \log ( N ) + T D )$ となる。

## 文献
-   [Capacitated Dynamic Programming: Faster Knapsack and Graph Algorithms](https://arxiv.org/abs/1802.06440)  
    $3.1 \  {\rm Knapsack}$ に記述がある 

## 語
#### (max,+)-convolution
[Concave Max Plus Convolution](https://noshi91.github.io/Library/library/algorithm/concave_max_plus_convolution.cpp.html)

## その他
-   アルゴリズムの名前について  
    Axiotis-Tzamos は論文の著者名から取ったが、正式な / 主流な名前は知らないため注意  
    ご存知の方は教えて頂けると嬉しいです


## Depends on

* :heavy_check_mark: <a href="concave_max_plus_convolution.cpp.html">Concave Max Plus Convolution <small>(algorithm/concave_max_plus_convolution.cpp)</small></a>
* :heavy_check_mark: <a href="smawk.cpp.html">SMAWK Algorithm <small>(algorithm/smawk.cpp)</small></a>
* :heavy_check_mark: <a href="../other/int_alias.cpp.html">other/int_alias.cpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/axiotis_tzamos_knapsack.test.cpp.html">test/axiotis_tzamos_knapsack.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "algorithm/concave_max_plus_convolution.cpp"
#include "other/int_alias.cpp"

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
 * @docs docs/axiotis_tzamos_knapsack.md
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
 * @brief Concave Max Plus Convolution
 * @docs docs/concave_max_plus_convolution.md
 */
#line 3 "algorithm/axiotis_tzamos_knapsack.cpp"

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
 * @docs docs/axiotis_tzamos_knapsack.md
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

