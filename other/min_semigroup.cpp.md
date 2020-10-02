---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: other/min_assign_action.cpp
    title: other/min_assign_action.cpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/larsch.test.cpp
    title: test/larsch.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"other/min_semigroup.cpp\"\ntemplate <class W> class min_semigroup\
    \ {\n  using T = typename W::value_type;\n\npublic:\n  using value_type = T;\n\
    \  static constexpr T operation(const T &l, const T &r) noexcept {\n    return\
    \ W::compare(l, r) ? l : r;\n  }\n};\n"
  code: "template <class W> class min_semigroup {\n  using T = typename W::value_type;\n\
    \npublic:\n  using value_type = T;\n  static constexpr T operation(const T &l,\
    \ const T &r) noexcept {\n    return W::compare(l, r) ? l : r;\n  }\n};"
  dependsOn: []
  isVerificationFile: false
  path: other/min_semigroup.cpp
  requiredBy:
  - other/min_assign_action.cpp
  timestamp: '2020-02-14 16:53:57+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/larsch.test.cpp
documentation_of: other/min_semigroup.cpp
layout: document
redirect_from:
- /library/other/min_semigroup.cpp
- /library/other/min_semigroup.cpp.html
title: other/min_semigroup.cpp
---
