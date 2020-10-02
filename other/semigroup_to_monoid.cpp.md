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
  - icon: ':heavy_check_mark:'
    path: test/larsch.test.cpp
    title: test/larsch.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"other/semigroup_to_monoid.cpp\"\n#include <optional>\n#include\
    \ <utility>\n\ntemplate <class S> class semigroup_to_monoid {\n  using T = std::optional<typename\
    \ S::value_type>;\n\npublic:\n  using value_type = T;\n  static constexpr T operation(const\
    \ T &l, const T &r) noexcept {\n    if (!l)\n      return r;\n    if (!r)\n  \
    \    return l;\n    return T(std::in_place, S::operation(*l, *r));\n  }\n  static\
    \ constexpr T identity{std::nullopt};\n};\n"
  code: "#include <optional>\n#include <utility>\n\ntemplate <class S> class semigroup_to_monoid\
    \ {\n  using T = std::optional<typename S::value_type>;\n\npublic:\n  using value_type\
    \ = T;\n  static constexpr T operation(const T &l, const T &r) noexcept {\n  \
    \  if (!l)\n      return r;\n    if (!r)\n      return l;\n    return T(std::in_place,\
    \ S::operation(*l, *r));\n  }\n  static constexpr T identity{std::nullopt};\n\
    };"
  dependsOn: []
  isVerificationFile: false
  path: other/semigroup_to_monoid.cpp
  requiredBy:
  - other/min_assign_action.cpp
  timestamp: '2020-02-09 00:25:15+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/larsch.test.cpp
  - test/dual_segment_tree.test.cpp
documentation_of: other/semigroup_to_monoid.cpp
layout: document
redirect_from:
- /library/other/semigroup_to_monoid.cpp
- /library/other/semigroup_to_monoid.cpp.html
title: other/semigroup_to_monoid.cpp
---
