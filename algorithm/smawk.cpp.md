---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: algorithm/axiotis_tzamos_knapsack.cpp
    title: Axiotis-Tzamos Knapsack
  - icon: ':heavy_check_mark:'
    path: algorithm/concave_max_plus_convolution.cpp
    title: Concave Max Plus Convolution
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/axiotis_tzamos_knapsack.test.cpp
    title: test/axiotis_tzamos_knapsack.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/smawk.md
    document_title: SMAWK Algorithm
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
    \ docs/smawk.md\n */\n"
  code: "#include \"other/int_alias.cpp\"\n\n#include <functional>\n#include <numeric>\n\
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
    \ docs/smawk.md\n */\n"
  dependsOn:
  - other/int_alias.cpp
  isVerificationFile: false
  path: algorithm/smawk.cpp
  requiredBy:
  - algorithm/concave_max_plus_convolution.cpp
  - algorithm/axiotis_tzamos_knapsack.cpp
  timestamp: '2020-03-03 23:12:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/axiotis_tzamos_knapsack.test.cpp
documentation_of: algorithm/smawk.cpp
layout: document
redirect_from:
- /library/algorithm/smawk.cpp
- /library/algorithm/smawk.cpp.html
title: SMAWK Algorithm
---
## 入力
$N \times M$ 行列 $A$
-   $A$ は totally monotone

## 出力
各 $i$ について $\mathop {\rm arg \, max} \limits _ j A _ {i , j}$

## 計算量
-   時間計算量 $\Theta ( N + M )$
-   空間計算量 $\Theta ( N + M )$

## 説明
$N \times M$ 行列 $A$ について、いずれかの行で最大値を取り得る高々 $N$ 個の列を $\Theta ( N + M )$ で取り出すアルゴリズムが存在する。(reduce)  
$1$ つ飛ばしに $N / 2$ 個程度の行を取り出し、reduce することで $N , M$ 共に半分になった問題を解く。  
monotone 性から、飛ばした行の $\mathop {\rm arg \, max}$ を復元する。(interpolate)

## 文献
-   [Totally Monotone Matrix Searching (SMAWK algorithm)](https://topcoder-g-hatena-ne-jp.jag-icpc.org/spaghetti_source/20120923/)  
    週刊 spaghetti_source  
    日本語

-   [The SMAWK Algorithm (pdf)](http://web.cs.unlv.edu/larmore/Courses/CSC477/monge.pdf)  
    具体例が図示されている

-   [Geometric applications of a matrix-searching algorithm](https://link.springer.com/article/10.1007%2FBF01840359)  
    SMAWK Algorithm が提案された論文

## 語
#### monotone
$A$ が monotone であるとは、任意の $i \lt j$ に対して

$\mathop {\rm arg \, max} \limits _ k A _ {i , k} \le \mathop {\rm arg \, max} \limits _ k A _ {j , k}$

が成立することを指す。  
ただし適切な tie-break により $\mathop {\rm arg \, max}$ は $1$ つに定まるとする。  
$\mathop {\rm arg \, min}$ による定義も存在するので注意。

#### totally monotone
$A$ が totally monotone であるとは、その任意の部分行列が monotone であることを指す。  
同値な定義に「$A$ の任意の $2 \times 2$ 部分行列が monotone」がある。

## その他
-   実装例の引数 $\rm select$ の定義  
    ${\rm select} ( i , j , k ) \mathrel := A _ {i , j}$ と $A _ {i , k} \  ( j \lt k )$ を比較して、前者を選ぶ場合 false、後者を選ぶ場合 true
