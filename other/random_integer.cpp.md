---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: data_structure/randomized_queue.cpp
    title: Randomized Queue
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/randomized_queue.test.cpp
    title: test/randomized_queue.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/wavelet_matrix.select.test.cpp
    title: test/wavelet_matrix.select.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"other/random_integer.cpp\"\n\n#include <random>\n#include\
    \ <type_traits>\n\ntemplate <class T, class... Args>\nusing any_of_is_same = std::disjunction<std::is_same<T,\
    \ Args>...>;\n\ntemplate <class IntType = int>\nIntType random_integer(const IntType\
    \ a, const IntType b) {\n  static_assert(\n      any_of_is_same<IntType, short,\
    \ int, long, long long, unsigned short,\n                     unsigned int, unsigned\
    \ long, unsigned long long>::value);\n  static std::default_random_engine g(91);\n\
    \  return std::uniform_int_distribution<IntType>(a, b)(g);\n}\n"
  code: "#pragma once\n\n#include <random>\n#include <type_traits>\n\ntemplate <class\
    \ T, class... Args>\nusing any_of_is_same = std::disjunction<std::is_same<T, Args>...>;\n\
    \ntemplate <class IntType = int>\nIntType random_integer(const IntType a, const\
    \ IntType b) {\n  static_assert(\n      any_of_is_same<IntType, short, int, long,\
    \ long long, unsigned short,\n                     unsigned int, unsigned long,\
    \ unsigned long long>::value);\n  static std::default_random_engine g(91);\n \
    \ return std::uniform_int_distribution<IntType>(a, b)(g);\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: other/random_integer.cpp
  requiredBy:
  - data_structure/randomized_queue.cpp
  timestamp: '2020-03-09 21:14:06+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/wavelet_matrix.select.test.cpp
  - test/randomized_queue.test.cpp
documentation_of: other/random_integer.cpp
layout: document
redirect_from:
- /library/other/random_integer.cpp
- /library/other/random_integer.cpp.html
title: other/random_integer.cpp
---
