---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algorithm/smawk.cpp
    title: SMAWK Algorithm
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: algorithm/axiotis_tzamos_knapsack.cpp
    title: Axiotis-Tzamos Knapsack
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/axiotis_tzamos_knapsack.test.cpp
    title: test/axiotis_tzamos_knapsack.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/concave_max_plus_convolution.md
    document_title: Concave Max Plus Convolution
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
    \ Convolution\n * @docs docs/concave_max_plus_convolution.md\n */\n"
  code: "#include \"algorithm/smawk.cpp\"\n#include \"other/int_alias.cpp\"\n\n#include\
    \ <vector>\n\ntemplate <class T>\nstd::vector<T> concave_max_plus_convolution(const\
    \ std::vector<T> &a,\n                                            const std::vector<T>\
    \ &b) {\n  const usize n = a.size();\n  const usize m = b.size();\n  const auto\
    \ get = [&](const usize i, const usize j) {\n    return a[j] + b[i - j];\n  };\n\
    \  const auto select = [&](const usize i, const usize j, const usize k) {\n  \
    \  if (i < k)\n      return false;\n    if (i - j >= m)\n      return true;\n\
    \    return get(i, j) <= get(i, k);\n  };\n  const std::vector<usize> amax = smawk(n\
    \ + m - 1, n, select);\n  std::vector<T> c(n + m - 1);\n  for (usize i = 0; i\
    \ != n + m - 1; i += 1)\n    c[i] = get(i, amax[i]);\n  return c;\n}\n\n/**\n\
    \ * @brief Concave Max Plus Convolution\n * @docs docs/concave_max_plus_convolution.md\n\
    \ */\n"
  dependsOn:
  - algorithm/smawk.cpp
  - other/int_alias.cpp
  isVerificationFile: false
  path: algorithm/concave_max_plus_convolution.cpp
  requiredBy:
  - algorithm/axiotis_tzamos_knapsack.cpp
  timestamp: '2020-03-05 22:38:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/axiotis_tzamos_knapsack.test.cpp
documentation_of: algorithm/concave_max_plus_convolution.cpp
layout: document
redirect_from:
- /library/algorithm/concave_max_plus_convolution.cpp
- /library/algorithm/concave_max_plus_convolution.cpp.html
title: Concave Max Plus Convolution
---
## 入力
長さ $N$ の列 $A$  
長さ $M$ の列 $B$
-   $B$ は上に凸

## 出力
$C_i \mathrel := \max \limits _ j \lbrace A _ j + B _ {i - j} \rbrace$

で定義される長さ $N + M - 1$ の列 $C$

## 計算量
-   時間計算量 $\Theta ( N + M )$
-   空間計算量 $\Theta ( N + M )$

## 説明
$( N + M - 1 ) \times N$ 行列 $X$ を以下のように定義する。

$X _ {i , j} \mathrel := A _ j + B _ {i - j}$

ただし、$k \lt 0$ や $M \leq k$ に対する $B _ k$ は、十分小さい値を $B$ の凸性を保つように設定するものとする。  
目的は $C _ i = \max \limits _ j X _ {i , j}$ を計算することである。  
$B$ が上に凸であることから $X$ は (anti-)monge であり、すなわち totally monotone。よって[SMAWK Algorithm](https://noshi91.github.io/Library/library/algorithm/smawk.cpp.html) を用いると $\Theta ( N + M )$ で計算可能。

## 文献
-   [Capacitated Dynamic Programming: Faster Knapsack and Graph Algorithms](https://arxiv.org/abs/1802.06440)  
    [Axiotis-Tzamos Knapsack](https://noshi91.github.io/Library/library/algorithm/axiotis_tzamos_knapsack.cpp.html) で使用されている
