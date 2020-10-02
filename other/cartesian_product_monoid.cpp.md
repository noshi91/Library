---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: other/sum_affine_action.cpp
    title: other/sum_affine_action.cpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/lazy_segment_tree.test.cpp
    title: test/lazy_segment_tree.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"other/cartesian_product_monoid.cpp\"\n#include <utility>\n\
    \ntemplate <class M, class N> class cartesian_product_monoid {\n  using T = std::pair<typename\
    \ M::value_type, typename N::value_type>;\n\npublic:\n  using value_type = T;\n\
    \  static constexpr T operation(const T &l, const T &r) noexcept {\n    return\
    \ T(M::operation(l.first, r.first), N::operation(l.second, r.second));\n  }\n\
    \  static constexpr T identity{M::identity, N::identity};\n};\n"
  code: "#include <utility>\n\ntemplate <class M, class N> class cartesian_product_monoid\
    \ {\n  using T = std::pair<typename M::value_type, typename N::value_type>;\n\n\
    public:\n  using value_type = T;\n  static constexpr T operation(const T &l, const\
    \ T &r) noexcept {\n    return T(M::operation(l.first, r.first), N::operation(l.second,\
    \ r.second));\n  }\n  static constexpr T identity{M::identity, N::identity};\n\
    };"
  dependsOn: []
  isVerificationFile: false
  path: other/cartesian_product_monoid.cpp
  requiredBy:
  - other/sum_affine_action.cpp
  timestamp: '2020-02-14 17:46:13+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/lazy_segment_tree.test.cpp
documentation_of: other/cartesian_product_monoid.cpp
layout: document
redirect_from:
- /library/other/cartesian_product_monoid.cpp
- /library/other/cartesian_product_monoid.cpp.html
title: other/cartesian_product_monoid.cpp
---
