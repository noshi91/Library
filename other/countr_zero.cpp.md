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
  - icon: ':heavy_check_mark:'
    path: data_structure/dual_segment_tree.cpp
    title: Dual Segment Tree
  - icon: ':heavy_check_mark:'
    path: data_structure/lazy_segment_tree.cpp
    title: Lazy Segment Tree
  - icon: ':heavy_check_mark:'
    path: data_structure/radix_heap.cpp
    title: Radix Heap
  - icon: ':heavy_check_mark:'
    path: other/bit_width.cpp
    title: other/bit_width.cpp
  - icon: ':heavy_check_mark:'
    path: other/countl_zero.cpp
    title: other/countl_zero.cpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/axiotis_tzamos_unbounded_knapsack.test.cpp
    title: test/axiotis_tzamos_unbounded_knapsack.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/dual_segment_tree.test.cpp
    title: test/dual_segment_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/lazy_segment_tree.test.cpp
    title: test/lazy_segment_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/radix_heap.test.cpp
    title: test/radix_heap.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"other/countr_zero.cpp\"\n\n#line 2 \"other/int_alias.cpp\"\
    \n\n#include <cstddef>\n#include <cstdint>\n\nusing i32 = std::int32_t;\nusing\
    \ i64 = std::int64_t;\nusing u32 = std::uint32_t;\nusing u64 = std::uint64_t;\n\
    using isize = std::ptrdiff_t;\nusing usize = std::size_t;\n#line 4 \"other/countr_zero.cpp\"\
    \n\n#include <array>\n\nusize countr_zero(u64 x) {\n  if (x == 0)\n    return\
    \ 64;\n#ifdef __GNUC__\n  return __builtin_ctzll(x);\n#else\n  constexpr std::array<usize,\
    \ 64> table = {\n      0,  1,  2,  7,  3,  13, 8,  27, 4,  33, 14, 36, 9,  49,\
    \ 28, 19,\n      5,  25, 34, 17, 15, 53, 37, 55, 10, 46, 50, 39, 29, 42, 20, 57,\n\
    \      63, 6,  12, 26, 32, 35, 48, 18, 24, 16, 52, 54, 45, 38, 41, 56,\n     \
    \ 62, 11, 31, 47, 23, 51, 44, 40, 61, 30, 22, 43, 60, 21, 59, 58};\n  return table[(x\
    \ & ~x + 1) * 0x218A7A392DD9ABF >> 58 & 0x3F];\n#endif\n}\n"
  code: "#pragma once\n\n#include \"other/int_alias.cpp\"\n\n#include <array>\n\n\
    usize countr_zero(u64 x) {\n  if (x == 0)\n    return 64;\n#ifdef __GNUC__\n \
    \ return __builtin_ctzll(x);\n#else\n  constexpr std::array<usize, 64> table =\
    \ {\n      0,  1,  2,  7,  3,  13, 8,  27, 4,  33, 14, 36, 9,  49, 28, 19,\n \
    \     5,  25, 34, 17, 15, 53, 37, 55, 10, 46, 50, 39, 29, 42, 20, 57,\n      63,\
    \ 6,  12, 26, 32, 35, 48, 18, 24, 16, 52, 54, 45, 38, 41, 56,\n      62, 11, 31,\
    \ 47, 23, 51, 44, 40, 61, 30, 22, 43, 60, 21, 59, 58};\n  return table[(x & ~x\
    \ + 1) * 0x218A7A392DD9ABF >> 58 & 0x3F];\n#endif\n}\n"
  dependsOn:
  - other/int_alias.cpp
  isVerificationFile: false
  path: other/countr_zero.cpp
  requiredBy:
  - data_structure/radix_heap.cpp
  - data_structure/dual_segment_tree.cpp
  - data_structure/lazy_segment_tree.cpp
  - other/countl_zero.cpp
  - other/bit_width.cpp
  - algorithm/axiotis_tzamos_unbounded_knapsack.cpp
  timestamp: '2020-03-10 16:21:51+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/lazy_segment_tree.test.cpp
  - test/axiotis_tzamos_unbounded_knapsack.test.cpp
  - test/radix_heap.test.cpp
  - test/dual_segment_tree.test.cpp
documentation_of: other/countr_zero.cpp
layout: document
redirect_from:
- /library/other/countr_zero.cpp
- /library/other/countr_zero.cpp.html
title: other/countr_zero.cpp
---
