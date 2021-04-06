---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: other/min_assign_action.cpp
    title: other/min_assign_action.cpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/dual_segment_tree.test.cpp
    title: test/dual_segment_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"other/right_zero_semigroup.cpp\"\ntemplate <class T> class\
    \ right_zero_semigroup {\npublic:\n  using value_type = T;\n  static constexpr\
    \ T operation(const T &, const T &r) noexcept { return r; }\n};\n"
  code: "template <class T> class right_zero_semigroup {\npublic:\n  using value_type\
    \ = T;\n  static constexpr T operation(const T &, const T &r) noexcept { return\
    \ r; }\n};"
  dependsOn: []
  isVerificationFile: false
  path: other/right_zero_semigroup.cpp
  requiredBy:
  - other/min_assign_action.cpp
  timestamp: '2020-02-09 00:25:15+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/dual_segment_tree.test.cpp
documentation_of: other/right_zero_semigroup.cpp
layout: document
redirect_from:
- /library/other/right_zero_semigroup.cpp
- /library/other/right_zero_semigroup.cpp.html
title: other/right_zero_semigroup.cpp
---
