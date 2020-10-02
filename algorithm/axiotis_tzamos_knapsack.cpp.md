---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algorithm/concave_max_plus_convolution.cpp
    title: Concave Max Plus Convolution
  - icon: ':heavy_check_mark:'
    path: algorithm/smawk.cpp
    title: SMAWK Algorithm
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/axiotis_tzamos_knapsack.test.cpp
    title: test/axiotis_tzamos_knapsack.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/axiotis_tzamos_knapsack.md
    document_title: Axiotis-Tzamos Knapsack
    links: []
  bundledCode: "#line 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
    \nusing i32 = std::int32_t;\nusing i64 = std::int64_t;\nusing u32 = std::uint32_t;\n\
    using u64 = std::uint64_t;\nusing isize = std::ptrdiff_t;\nusing usize = std::size_t;\n\
    #line 2 \"algorithm/smawk.cpp\"\n\n#include <functional>\n#include <numeric>\n\
    #include <vector>\n\ntemplate <class Select>\nstd::vector<usize> smawk(const usize\
    \ row_size, const usize col_size,\n                         const Select &select)\
    \ {\n  using vec_zu = std::vector<usize>;\n\n  const std::function<vec_zu(const\
    \ vec_zu &, const vec_zu &)> solve =\n      [&](const vec_zu &row, const vec_zu\
    \ &col) -> vec_zu {\n    const usize n = row.size();\n    if (n == 0)\n      return\
    \ {};\n    vec_zu c2;\n    for (const usize i : col) {\n      while (!c2.empty()\
    \ && select(row[c2.size() - 1], c2.back(), i))\n        c2.pop_back();\n     \
    \ if (c2.size() < n)\n        c2.push_back(i);\n    }\n    vec_zu r2;\n    for\
    \ (usize i = 1; i < n; i += 2)\n      r2.push_back(row[i]);\n    const vec_zu\
    \ a2 = solve(r2, c2);\n    vec_zu ans(n);\n    for (usize i = 0; i != a2.size();\
    \ i += 1)\n      ans[i * 2 + 1] = a2[i];\n    usize j = 0;\n    for (usize i =\
    \ 0; i < n; i += 2) {\n      ans[i] = c2[j];\n      const usize end = i + 1 ==\
    \ n ? c2.back() : ans[i + 1];\n      while (c2[j] != end) {\n        j += 1;\n\
    \        if (select(row[i], ans[i], c2[j]))\n          ans[i] = c2[j];\n     \
    \ }\n    }\n    return ans;\n  };\n  vec_zu row(row_size);\n  std::iota(row.begin(),\
    \ row.end(), 0);\n  vec_zu col(col_size);\n  std::iota(col.begin(), col.end(),\
    \ 0);\n  return solve(row, col);\n}\n\n/**\n * @brief SMAWK Algorithm\n * @docs\
    \ docs/smawk.md\n */\n#line 3 \"algorithm/concave_max_plus_convolution.cpp\"\n\
    \n#line 5 \"algorithm/concave_max_plus_convolution.cpp\"\n\ntemplate <class T>\n\
    std::vector<T> concave_max_plus_convolution(const std::vector<T> &a,\n       \
    \                                     const std::vector<T> &b) {\n  const usize\
    \ n = a.size();\n  const usize m = b.size();\n  const auto get = [&](const usize\
    \ i, const usize j) {\n    return a[j] + b[i - j];\n  };\n  const auto select\
    \ = [&](const usize i, const usize j, const usize k) {\n    if (i < k)\n     \
    \ return false;\n    if (i - j >= m)\n      return true;\n    return get(i, j)\
    \ <= get(i, k);\n  };\n  const std::vector<usize> amax = smawk(n + m - 1, n, select);\n\
    \  std::vector<T> c(n + m - 1);\n  for (usize i = 0; i != n + m - 1; i += 1)\n\
    \    c[i] = get(i, amax[i]);\n  return c;\n}\n\n/**\n * @brief Concave Max Plus\
    \ Convolution\n * @docs docs/concave_max_plus_convolution.md\n */\n#line 3 \"\
    algorithm/axiotis_tzamos_knapsack.cpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #line 7 \"algorithm/axiotis_tzamos_knapsack.cpp\"\n#include <utility>\n#line 9\
    \ \"algorithm/axiotis_tzamos_knapsack.cpp\"\n\ntemplate <class I>\nu64 axiotis_tzamos_knapsack(const\
    \ usize t, const std::vector<I> &item) {\n  std::vector<std::vector<i64>> bucket(t\
    \ + 1);\n  for (const I &e : item) {\n    assert(e.w > 0);\n    assert(e.v >=\
    \ 0);\n\n    if (e.w <= t)\n      bucket[e.w].push_back(e.v);\n  }\n\n  std::vector<i64>\
    \ dp(t + 1, std::numeric_limits<i64>::lowest());\n  dp[0] = 0;\n  for (usize w\
    \ = 1; w <= t; w += 1) {\n    std::vector<i64> &list = bucket[w];\n    if (list.empty())\n\
    \      continue;\n    std::sort(list.begin(), list.end(), std::greater<i64>());\n\
    \    const usize m = std::min(list.size(), t / w);\n    std::vector<i64> sum(m\
    \ + 1);\n    sum[0] = 0;\n    for (usize i = 0; i != m; i += 1)\n      sum[i +\
    \ 1] = sum[i] + list[i];\n    for (usize k = 0; k != w; k += 1) {\n      const\
    \ usize n = (t - k) / w + 1;\n      std::vector<i64> v(n);\n      for (usize i\
    \ = 0; i != n; i += 1)\n        v[i] = dp[i * w + k];\n      const std::vector<i64>\
    \ res = concave_max_plus_convolution(v, sum);\n      for (usize i = 0; i != n;\
    \ i += 1)\n        dp[i * w + k] = res[i];\n    }\n  }\n  return *std::max_element(dp.begin(),\
    \ dp.end());\n}\n\n/**\n * @brief Axiotis-Tzamos Knapsack\n * @docs docs/axiotis_tzamos_knapsack.md\n\
    \ */\n"
  code: "#include \"algorithm/concave_max_plus_convolution.cpp\"\n#include \"other/int_alias.cpp\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <functional>\n#include\
    \ <utility>\n#include <vector>\n\ntemplate <class I>\nu64 axiotis_tzamos_knapsack(const\
    \ usize t, const std::vector<I> &item) {\n  std::vector<std::vector<i64>> bucket(t\
    \ + 1);\n  for (const I &e : item) {\n    assert(e.w > 0);\n    assert(e.v >=\
    \ 0);\n\n    if (e.w <= t)\n      bucket[e.w].push_back(e.v);\n  }\n\n  std::vector<i64>\
    \ dp(t + 1, std::numeric_limits<i64>::lowest());\n  dp[0] = 0;\n  for (usize w\
    \ = 1; w <= t; w += 1) {\n    std::vector<i64> &list = bucket[w];\n    if (list.empty())\n\
    \      continue;\n    std::sort(list.begin(), list.end(), std::greater<i64>());\n\
    \    const usize m = std::min(list.size(), t / w);\n    std::vector<i64> sum(m\
    \ + 1);\n    sum[0] = 0;\n    for (usize i = 0; i != m; i += 1)\n      sum[i +\
    \ 1] = sum[i] + list[i];\n    for (usize k = 0; k != w; k += 1) {\n      const\
    \ usize n = (t - k) / w + 1;\n      std::vector<i64> v(n);\n      for (usize i\
    \ = 0; i != n; i += 1)\n        v[i] = dp[i * w + k];\n      const std::vector<i64>\
    \ res = concave_max_plus_convolution(v, sum);\n      for (usize i = 0; i != n;\
    \ i += 1)\n        dp[i * w + k] = res[i];\n    }\n  }\n  return *std::max_element(dp.begin(),\
    \ dp.end());\n}\n\n/**\n * @brief Axiotis-Tzamos Knapsack\n * @docs docs/axiotis_tzamos_knapsack.md\n\
    \ */\n"
  dependsOn:
  - algorithm/concave_max_plus_convolution.cpp
  - algorithm/smawk.cpp
  - other/int_alias.cpp
  isVerificationFile: false
  path: algorithm/axiotis_tzamos_knapsack.cpp
  requiredBy: []
  timestamp: '2020-03-05 22:38:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/axiotis_tzamos_knapsack.test.cpp
documentation_of: algorithm/axiotis_tzamos_knapsack.cpp
layout: document
redirect_from:
- /library/algorithm/axiotis_tzamos_knapsack.cpp
- /library/algorithm/axiotis_tzamos_knapsack.cpp.html
title: Axiotis-Tzamos Knapsack
---
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
