---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: data_structure/bit_vector.cpp
    title: Bit Vector
  - icon: ':heavy_check_mark:'
    path: data_structure/wavelet_matrix.cpp
    title: Wavelet Matrix
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/wavelet_matrix.quantile.test.cpp
    title: test/wavelet_matrix.quantile.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/wavelet_matrix.rangefreq.test.cpp
    title: test/wavelet_matrix.rangefreq.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/wavelet_matrix.select.test.cpp
    title: test/wavelet_matrix.select.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"other/popcount.cpp\"\n\n#line 2 \"other/int_alias.cpp\"\n\
    \n#include <cstddef>\n#include <cstdint>\n\nusing i32 = std::int32_t;\nusing i64\
    \ = std::int64_t;\nusing u32 = std::uint32_t;\nusing u64 = std::uint64_t;\nusing\
    \ isize = std::ptrdiff_t;\nusing usize = std::size_t;\n#line 4 \"other/popcount.cpp\"\
    \n\nusize popcount(u64 x) {\n#ifdef __GNUC__\n  return __builtin_popcountll(x);\n\
    #else\n  x -= x >> 1 & 0x5555555555555555;\n  x = (x & 0x3333333333333333) + (x\
    \ >> 2 & 0x3333333333333333);\n  x = x + (x >> 4) & 0x0F0F0F0F0F0F0F0F;\n  return\
    \ x * 0x0101010101010101 >> 56 & 0x7f;\n#endif\n}\n"
  code: "#pragma once\n\n#include \"other/int_alias.cpp\"\n\nusize popcount(u64 x)\
    \ {\n#ifdef __GNUC__\n  return __builtin_popcountll(x);\n#else\n  x -= x >> 1\
    \ & 0x5555555555555555;\n  x = (x & 0x3333333333333333) + (x >> 2 & 0x3333333333333333);\n\
    \  x = x + (x >> 4) & 0x0F0F0F0F0F0F0F0F;\n  return x * 0x0101010101010101 >>\
    \ 56 & 0x7f;\n#endif\n}\n"
  dependsOn:
  - other/int_alias.cpp
  isVerificationFile: false
  path: other/popcount.cpp
  requiredBy:
  - data_structure/wavelet_matrix.cpp
  - data_structure/bit_vector.cpp
  timestamp: '2020-03-10 16:21:51+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/wavelet_matrix.select.test.cpp
  - test/wavelet_matrix.quantile.test.cpp
  - test/wavelet_matrix.rangefreq.test.cpp
documentation_of: other/popcount.cpp
layout: document
redirect_from:
- /library/other/popcount.cpp
- /library/other/popcount.cpp.html
title: other/popcount.cpp
---
