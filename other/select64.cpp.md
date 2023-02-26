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
  bundledCode: "#line 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
    \nusing i32 = std::int32_t;\nusing i64 = std::int64_t;\nusing u32 = std::uint32_t;\n\
    using u64 = std::uint64_t;\nusing isize = std::ptrdiff_t;\nusing usize = std::size_t;\n\
    #line 2 \"other/select64.cpp\"\n\n#line 5 \"other/select64.cpp\"\n\nusize select64(const\
    \ u64 x0, usize k) {\n  const u64 x1 = (x0 & 0x5555555555555555) + (x0 >> 1 &\
    \ 0x5555555555555555);\n  const u64 x2 = (x1 & 0x3333333333333333) + (x1 >> 2\
    \ & 0x3333333333333333);\n  const u64 x3 = (x2 & 0x0F0F0F0F0F0F0F0F) + (x2 >>\
    \ 4 & 0x0F0F0F0F0F0F0F0F);\n  const u64 x4 = (x3 & 0x00FF00FF00FF00FF) + (x3 >>\
    \ 8 & 0x00FF00FF00FF00FF);\n  const u64 x5 = (x4 & 0x0000FFFF0000FFFF) + (x4 >>\
    \ 16 & 0x0000FFFF0000FFFF);\n  usize ret = 0;\n  usize t;\n  t = x5 >> ret & 0xFFFFFFFF;\n\
    \  if (t <= k) {\n    k -= t;\n    ret += 32;\n  }\n  t = x4 >> ret & 0xFFFF;\n\
    \  if (t <= k) {\n    k -= t;\n    ret += 16;\n  }\n  t = x3 >> ret & 0xFF;\n\
    \  if (t <= k) {\n    k -= t;\n    ret += 8;\n  }\n  t = x2 >> ret & 0xF;\n  if\
    \ (t <= k) {\n    k -= t;\n    ret += 4;\n  }\n  t = x1 >> ret & 0x3;\n  if (t\
    \ <= k) {\n    k -= t;\n    ret += 2;\n  }\n  t = x0 >> ret & 0x1;\n  if (t <=\
    \ k) {\n    k -= t;\n    ret += 1;\n  }\n  return ret;\n}\n"
  code: "#include \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
    \nusize select64(const u64 x0, usize k) {\n  const u64 x1 = (x0 & 0x5555555555555555)\
    \ + (x0 >> 1 & 0x5555555555555555);\n  const u64 x2 = (x1 & 0x3333333333333333)\
    \ + (x1 >> 2 & 0x3333333333333333);\n  const u64 x3 = (x2 & 0x0F0F0F0F0F0F0F0F)\
    \ + (x2 >> 4 & 0x0F0F0F0F0F0F0F0F);\n  const u64 x4 = (x3 & 0x00FF00FF00FF00FF)\
    \ + (x3 >> 8 & 0x00FF00FF00FF00FF);\n  const u64 x5 = (x4 & 0x0000FFFF0000FFFF)\
    \ + (x4 >> 16 & 0x0000FFFF0000FFFF);\n  usize ret = 0;\n  usize t;\n  t = x5 >>\
    \ ret & 0xFFFFFFFF;\n  if (t <= k) {\n    k -= t;\n    ret += 32;\n  }\n  t =\
    \ x4 >> ret & 0xFFFF;\n  if (t <= k) {\n    k -= t;\n    ret += 16;\n  }\n  t\
    \ = x3 >> ret & 0xFF;\n  if (t <= k) {\n    k -= t;\n    ret += 8;\n  }\n  t =\
    \ x2 >> ret & 0xF;\n  if (t <= k) {\n    k -= t;\n    ret += 4;\n  }\n  t = x1\
    \ >> ret & 0x3;\n  if (t <= k) {\n    k -= t;\n    ret += 2;\n  }\n  t = x0 >>\
    \ ret & 0x1;\n  if (t <= k) {\n    k -= t;\n    ret += 1;\n  }\n  return ret;\n\
    }\n"
  dependsOn:
  - other/int_alias.cpp
  isVerificationFile: false
  path: other/select64.cpp
  requiredBy:
  - data_structure/bit_vector.cpp
  - data_structure/wavelet_matrix.cpp
  timestamp: '2020-03-11 22:58:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/wavelet_matrix.select.test.cpp
  - test/wavelet_matrix.rangefreq.test.cpp
  - test/wavelet_matrix.quantile.test.cpp
documentation_of: other/select64.cpp
layout: document
redirect_from:
- /library/other/select64.cpp
- /library/other/select64.cpp.html
title: other/select64.cpp
---
