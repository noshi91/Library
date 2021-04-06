---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: algorithm/divisor_mobius_transform.cpp
    title: "Divisor M\xF6bius Transform"
  - icon: ':warning:'
    path: algorithm/multiple_zeta_transform.cpp
    title: Multiple Zeta Transform
  - icon: ':heavy_check_mark:'
    path: data_structure/w_ary_tree_set.cpp
    title: w-ary Tree Set
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/w_ary_tree_set.test.cpp
    title: test/w_ary_tree_set.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"other/ceildiv.cpp\"\ntemplate <class T> constexpr T ceildiv(const\
    \ T &n, const T &d) {\r\n  return n / d + (n % d != 0 ? 1 : 0);\r\n}\r\n"
  code: "template <class T> constexpr T ceildiv(const T &n, const T &d) {\r\n  return\
    \ n / d + (n % d != 0 ? 1 : 0);\r\n}\r\n"
  dependsOn: []
  isVerificationFile: false
  path: other/ceildiv.cpp
  requiredBy:
  - data_structure/w_ary_tree_set.cpp
  - algorithm/multiple_zeta_transform.cpp
  - algorithm/divisor_mobius_transform.cpp
  timestamp: '2020-09-11 14:24:32+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/w_ary_tree_set.test.cpp
documentation_of: other/ceildiv.cpp
layout: document
redirect_from:
- /library/other/ceildiv.cpp
- /library/other/ceildiv.cpp.html
title: other/ceildiv.cpp
---
