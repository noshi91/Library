---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: algorithm/axiotis_tzamos_unbounded_knapsack.cpp
    title: Axiotis-Tzamos Unbounded Knapsack
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/axiotis_tzamos_unbounded_knapsack.test.cpp
    title: test/axiotis_tzamos_unbounded_knapsack.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Max Plus Convolution
    links: []
  bundledCode: "#line 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
    \nusing i32 = std::int32_t;\nusing i64 = std::int64_t;\nusing u32 = std::uint32_t;\n\
    using u64 = std::uint64_t;\nusing isize = std::ptrdiff_t;\nusing usize = std::size_t;\n\
    #line 2 \"algorithm/max_plus_convolution.cpp\"\n\n#include <algorithm>\n#include\
    \ <vector>\n\ntemplate <class T>\nstd::vector<T> max_plus_convolution(const std::vector<T>\
    \ &a,\n                                    const std::vector<T> &b) {\n  const\
    \ usize n = a.size();\n  const usize m = b.size();\n  std::vector<T> c(n + m -\
    \ 1, std::numeric_limits<T>::lowest());\n  for (usize i = 0; i != n; i += 1) {\n\
    \    for (usize j = 0; j != m; j += 1)\n      c[i + j] = std::max(c[i + j], a[i]\
    \ + b[j]);\n  }\n  return c;\n}\n\n/**\n * @brief Max Plus Convolution\n */\n"
  code: "#include \"other/int_alias.cpp\"\n\n#include <algorithm>\n#include <vector>\n\
    \ntemplate <class T>\nstd::vector<T> max_plus_convolution(const std::vector<T>\
    \ &a,\n                                    const std::vector<T> &b) {\n  const\
    \ usize n = a.size();\n  const usize m = b.size();\n  std::vector<T> c(n + m -\
    \ 1, std::numeric_limits<T>::lowest());\n  for (usize i = 0; i != n; i += 1) {\n\
    \    for (usize j = 0; j != m; j += 1)\n      c[i + j] = std::max(c[i + j], a[i]\
    \ + b[j]);\n  }\n  return c;\n}\n\n/**\n * @brief Max Plus Convolution\n */\n"
  dependsOn:
  - other/int_alias.cpp
  isVerificationFile: false
  path: algorithm/max_plus_convolution.cpp
  requiredBy:
  - algorithm/axiotis_tzamos_unbounded_knapsack.cpp
  timestamp: '2020-03-03 16:21:51+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/axiotis_tzamos_unbounded_knapsack.test.cpp
documentation_of: algorithm/max_plus_convolution.cpp
layout: document
redirect_from:
- /library/algorithm/max_plus_convolution.cpp
- /library/algorithm/max_plus_convolution.cpp.html
title: Max Plus Convolution
---
