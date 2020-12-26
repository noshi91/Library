---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/erasable_heap.test.cpp
    title: test/erasable_heap.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/larsch.test.cpp
    title: test/larsch.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/pairing_heap.test.cpp
    title: test/pairing_heap.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"other/less_equal_ordered_set.cpp\"\ntemplate <class T> class\
    \ less_equal_ordered_set {\npublic:\n  using value_type = T;\n  static constexpr\
    \ bool compare(const T &x, const T &y) noexcept {\n    return x <= y;\n  }\n};\n"
  code: "template <class T> class less_equal_ordered_set {\npublic:\n  using value_type\
    \ = T;\n  static constexpr bool compare(const T &x, const T &y) noexcept {\n \
    \   return x <= y;\n  }\n};"
  dependsOn: []
  isVerificationFile: false
  path: other/less_equal_ordered_set.cpp
  requiredBy: []
  timestamp: '2020-02-14 16:53:57+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/larsch.test.cpp
  - test/erasable_heap.test.cpp
  - test/pairing_heap.test.cpp
documentation_of: other/less_equal_ordered_set.cpp
layout: document
redirect_from:
- /library/other/less_equal_ordered_set.cpp
- /library/other/less_equal_ordered_set.cpp.html
title: other/less_equal_ordered_set.cpp
---
