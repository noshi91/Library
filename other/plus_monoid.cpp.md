---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: other/sum_affine_action.cpp
    title: other/sum_affine_action.cpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/fenwick_tree.test.cpp
    title: test/fenwick_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/lazy_segment_tree.test.cpp
    title: test/lazy_segment_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"other/plus_monoid.cpp\"\ntemplate <class T> class plus_monoid\
    \ {\npublic:\n  using value_type = T;\n  static T operation(const T l, const T\
    \ r) { return l + r; }\n  static constexpr T identity = 0;\n};\n"
  code: "template <class T> class plus_monoid {\npublic:\n  using value_type = T;\n\
    \  static T operation(const T l, const T r) { return l + r; }\n  static constexpr\
    \ T identity = 0;\n};"
  dependsOn: []
  isVerificationFile: false
  path: other/plus_monoid.cpp
  requiredBy:
  - other/sum_affine_action.cpp
  timestamp: '2020-02-09 00:25:15+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/fenwick_tree.test.cpp
  - test/lazy_segment_tree.test.cpp
documentation_of: other/plus_monoid.cpp
layout: document
redirect_from:
- /library/other/plus_monoid.cpp
- /library/other/plus_monoid.cpp.html
title: other/plus_monoid.cpp
---
