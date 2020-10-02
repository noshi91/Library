---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: algorithm/axiotis_tzamos_unbounded_knapsack.cpp
    title: Axiotis-Tzamos Unbounded Knapsack
  - icon: ':heavy_check_mark:'
    path: algorithm/max_plus_convolution.cpp
    title: Max Plus Convolution
  - icon: ':heavy_check_mark:'
    path: other/bit_width.cpp
    title: other/bit_width.cpp
  - icon: ':heavy_check_mark:'
    path: other/countl_zero.cpp
    title: other/countl_zero.cpp
  - icon: ':heavy_check_mark:'
    path: other/countr_zero.cpp
    title: other/countr_zero.cpp
  - icon: ':heavy_check_mark:'
    path: other/fast_ios.cpp
    title: other/fast_ios.cpp
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_C&lang=ja
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_C&lang=ja
  bundledCode: "#line 1 \"test/axiotis_tzamos_unbounded_knapsack.test.cpp\"\n#define\
    \ PROBLEM                                                                \\\n\
    \  \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_C&lang=ja\"\
    \n\n#line 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
    \nusing i32 = std::int32_t;\nusing i64 = std::int64_t;\nusing u32 = std::uint32_t;\n\
    using u64 = std::uint64_t;\nusing isize = std::ptrdiff_t;\nusing usize = std::size_t;\n\
    #line 2 \"algorithm/max_plus_convolution.cpp\"\n\n#include <algorithm>\n#include\
    \ <vector>\n\ntemplate <class T>\nstd::vector<T> max_plus_convolution(const std::vector<T>\
    \ &a,\n                                    const std::vector<T> &b) {\n  const\
    \ usize n = a.size();\n  const usize m = b.size();\n  std::vector<T> c(n + m -\
    \ 1, std::numeric_limits<T>::lowest());\n  for (usize i = 0; i != n; i += 1) {\n\
    \    for (usize j = 0; j != m; j += 1)\n      c[i + j] = std::max(c[i + j], a[i]\
    \ + b[j]);\n  }\n  return c;\n}\n\n/**\n * @brief Max Plus Convolution\n */\n\
    #line 2 \"other/bit_width.cpp\"\n\n#line 2 \"other/countl_zero.cpp\"\n\n#line\
    \ 2 \"other/countr_zero.cpp\"\n\n#line 4 \"other/countr_zero.cpp\"\n\n#include\
    \ <array>\n\nusize countr_zero(u64 x) {\n  if (x == 0)\n    return 64;\n#ifdef\
    \ __GNUC__\n  return __builtin_ctzll(x);\n#else\n  constexpr std::array<usize,\
    \ 64> table = {\n      0,  1,  2,  7,  3,  13, 8,  27, 4,  33, 14, 36, 9,  49,\
    \ 28, 19,\n      5,  25, 34, 17, 15, 53, 37, 55, 10, 46, 50, 39, 29, 42, 20, 57,\n\
    \      63, 6,  12, 26, 32, 35, 48, 18, 24, 16, 52, 54, 45, 38, 41, 56,\n     \
    \ 62, 11, 31, 47, 23, 51, 44, 40, 61, 30, 22, 43, 60, 21, 59, 58};\n  return table[(x\
    \ & ~x + 1) * 0x218A7A392DD9ABF >> 58 & 0x3F];\n#endif\n}\n#line 5 \"other/countl_zero.cpp\"\
    \n\nusize countl_zero(u64 x) {\n#ifdef __GNUC__\n  return x == 0 ? 64 : __builtin_clzll(x);\n\
    #else\n  x |= x >> 1;\n  x |= x >> 2;\n  x |= x >> 4;\n  x |= x >> 8;\n  x |=\
    \ x >> 16;\n  x |= x >> 32;\n  return 64 - countr_zero(~x);\n#endif\n}\n#line\
    \ 5 \"other/bit_width.cpp\"\n\nusize bit_width(const u64 x) { return 64 - countl_zero(x);\
    \ }\n#line 4 \"algorithm/axiotis_tzamos_unbounded_knapsack.cpp\"\n\n#line 6 \"\
    algorithm/axiotis_tzamos_unbounded_knapsack.cpp\"\n#include <cassert>\n#line 8\
    \ \"algorithm/axiotis_tzamos_unbounded_knapsack.cpp\"\n\ntemplate <class I>\n\
    u64 axiotis_tzamos_unbounded_knapsack(const u64 t, const std::vector<I> &item)\
    \ {\n  assert(!item.empty());\n\n  constexpr i64 minf = std::numeric_limits<i64>::lowest()\
    \ / 2;\n\n  usize m = 0;\n  for (const I &e : item) {\n    assert(e.w > 0);\n\
    \    assert(e.v >= 0);\n\n    m = std::max<usize>(m, e.w);\n  }\n  std::vector<i64>\
    \ dp(m + 1, minf);\n  dp[0] = 0;\n  for (const I &e : item)\n    dp[e.w] = std::max(dp[e.w],\
    \ e.v);\n  for (usize z = 1; z < m; z *= 2) {\n    dp = max_plus_convolution(dp,\
    \ dp);\n    dp.resize(m + 1);\n  }\n  {\n    const std::vector<i64> temp(m, minf);\n\
    \    dp.insert(dp.begin(), temp.begin(), temp.end());\n  }\n\n  for (usize i =\
    \ bit_width(t); i != 0; i -= 1) {\n    dp = max_plus_convolution(dp, dp);\n  \
    \  auto itr = dp.begin() + 2 * m;\n    if ((t >> i - 1) % 2 == 1)\n      itr +=\
    \ 1;\n    dp = std::vector<i64>(itr - m, itr + m + 1);\n  }\n  return *std::max_element(dp.begin(),\
    \ dp.begin() + m + 1);\n}\n\n/**\n * @brief Axiotis-Tzamos Unbounded Knapsack\n\
    \ * @see https://arxiv.org/abs/1802.06440\n */\n#line 6 \"test/axiotis_tzamos_unbounded_knapsack.test.cpp\"\
    \n\n#include <iostream>\n#line 9 \"test/axiotis_tzamos_unbounded_knapsack.test.cpp\"\
    \n\nint main() {\n#line 1 \"other/fast_ios.cpp\"\nstd::ios::sync_with_stdio(false);\n\
    std::cin.tie(nullptr);\n#line 12 \"test/axiotis_tzamos_unbounded_knapsack.test.cpp\"\
    \n\n  usize n, w;\n  std::cin >> n >> w;\n  struct item_t {\n    i64 v, w;\n \
    \ };\n  std::vector<item_t> is(n);\n  for (auto &e : is) {\n    std::cin >> e.v\
    \ >> e.w;\n  }\n  std::cout << axiotis_tzamos_unbounded_knapsack(w, is) << \"\\\
    n\";\n}\n"
  code: "#define PROBLEM                                                         \
    \       \\\n  \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_C&lang=ja\"\
    \n\n#include \"algorithm/axiotis_tzamos_unbounded_knapsack.cpp\"\n#include \"\
    other/int_alias.cpp\"\n\n#include <iostream>\n#include <vector>\n\nint main()\
    \ {\n#include \"other/fast_ios.cpp\"\n\n  usize n, w;\n  std::cin >> n >> w;\n\
    \  struct item_t {\n    i64 v, w;\n  };\n  std::vector<item_t> is(n);\n  for (auto\
    \ &e : is) {\n    std::cin >> e.v >> e.w;\n  }\n  std::cout << axiotis_tzamos_unbounded_knapsack(w,\
    \ is) << \"\\n\";\n}\n"
  dependsOn:
  - algorithm/axiotis_tzamos_unbounded_knapsack.cpp
  - algorithm/max_plus_convolution.cpp
  - other/int_alias.cpp
  - other/bit_width.cpp
  - other/countl_zero.cpp
  - other/countr_zero.cpp
  - other/fast_ios.cpp
  isVerificationFile: true
  path: test/axiotis_tzamos_unbounded_knapsack.test.cpp
  requiredBy: []
  timestamp: '2020-03-11 22:42:07+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/axiotis_tzamos_unbounded_knapsack.test.cpp
layout: document
redirect_from:
- /verify/test/axiotis_tzamos_unbounded_knapsack.test.cpp
- /verify/test/axiotis_tzamos_unbounded_knapsack.test.cpp.html
title: test/axiotis_tzamos_unbounded_knapsack.test.cpp
---
