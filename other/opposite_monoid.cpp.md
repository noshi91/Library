---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: data_structure/queue_aggregation.cpp
    title: Queue Aggregation
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/queue_aggregation.test.cpp
    title: test/queue_aggregation.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"other/opposite_monoid.cpp\"\ntemplate <class M> class opposite_monoid\
    \ {\n  using T = typename M::value_type;\n\npublic:\n  using value_type = T;\n\
    \  static constexpr T operation(const T &l, const T &r) noexcept {\n    return\
    \ M::operation(r, l);\n  }\n  static constexpr T identity = M::identity;\n};\n"
  code: "template <class M> class opposite_monoid {\n  using T = typename M::value_type;\n\
    \npublic:\n  using value_type = T;\n  static constexpr T operation(const T &l,\
    \ const T &r) noexcept {\n    return M::operation(r, l);\n  }\n  static constexpr\
    \ T identity = M::identity;\n};"
  dependsOn: []
  isVerificationFile: false
  path: other/opposite_monoid.cpp
  requiredBy:
  - data_structure/queue_aggregation.cpp
  timestamp: '2020-02-11 11:45:48+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/queue_aggregation.test.cpp
documentation_of: other/opposite_monoid.cpp
layout: document
redirect_from:
- /library/other/opposite_monoid.cpp
- /library/other/opposite_monoid.cpp.html
title: other/opposite_monoid.cpp
---
