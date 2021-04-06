---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algorithm/axiotis_tzamos_knapsack.cpp
    title: Axiotis-Tzamos Knapsack
  - icon: ':heavy_check_mark:'
    path: algorithm/concave_max_plus_convolution.cpp
    title: Concave Max Plus Convolution
  - icon: ':heavy_check_mark:'
    path: algorithm/smawk.cpp
    title: SMAWK Algorithm
  - icon: ':heavy_check_mark:'
    path: other/fast_ios.cpp
    title: other/fast_ios.cpp
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_B&lang=ja
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_B&lang=ja
  bundledCode: "#line 1 \"test/axiotis_tzamos_knapsack.test.cpp\"\n#define PROBLEM\
    \                                                                \\\n  \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_B&lang=ja\"\
    \n\n#line 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
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
    \ */\n#line 6 \"test/axiotis_tzamos_knapsack.test.cpp\"\n\n#include <iostream>\n\
    #line 9 \"test/axiotis_tzamos_knapsack.test.cpp\"\n\nint main() {\n#line 1 \"\
    other/fast_ios.cpp\"\nstd::ios::sync_with_stdio(false);\nstd::cin.tie(nullptr);\n\
    #line 12 \"test/axiotis_tzamos_knapsack.test.cpp\"\n\n  usize n, w;\n  std::cin\
    \ >> n >> w;\n  struct item_t {\n    i64 v, w;\n  };\n  std::vector<item_t> is(n);\n\
    \  for (auto &e : is) {\n    std::cin >> e.v >> e.w;\n  }\n  std::cout << axiotis_tzamos_knapsack(w,\
    \ is) << \"\\n\";\n}\n"
  code: "#define PROBLEM                                                         \
    \       \\\n  \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_B&lang=ja\"\
    \n\n#include \"algorithm/axiotis_tzamos_knapsack.cpp\"\n#include \"other/int_alias.cpp\"\
    \n\n#include <iostream>\n#include <vector>\n\nint main() {\n#include \"other/fast_ios.cpp\"\
    \n\n  usize n, w;\n  std::cin >> n >> w;\n  struct item_t {\n    i64 v, w;\n \
    \ };\n  std::vector<item_t> is(n);\n  for (auto &e : is) {\n    std::cin >> e.v\
    \ >> e.w;\n  }\n  std::cout << axiotis_tzamos_knapsack(w, is) << \"\\n\";\n}\n"
  dependsOn:
  - algorithm/axiotis_tzamos_knapsack.cpp
  - algorithm/concave_max_plus_convolution.cpp
  - algorithm/smawk.cpp
  - other/int_alias.cpp
  - other/fast_ios.cpp
  isVerificationFile: true
  path: test/axiotis_tzamos_knapsack.test.cpp
  requiredBy: []
  timestamp: '2020-03-11 00:35:25+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/axiotis_tzamos_knapsack.test.cpp
layout: document
redirect_from:
- /verify/test/axiotis_tzamos_knapsack.test.cpp
- /verify/test/axiotis_tzamos_knapsack.test.cpp.html
title: test/axiotis_tzamos_knapsack.test.cpp
---
