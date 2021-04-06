---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/zeta_transform.test.cpp
    title: test/zeta_transform.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"other/multiplies_monoid.cpp\"\ntemplate <class T> class\
    \ multiplies_monoid {\npublic:\n  using value_type = T;\n  static constexpr T\
    \ operation(const T &l, const T &r) noexcept {\n    return l * r;\n  }\n  static\
    \ constexpr T identity = 1;\n};\n"
  code: "template <class T> class multiplies_monoid {\npublic:\n  using value_type\
    \ = T;\n  static constexpr T operation(const T &l, const T &r) noexcept {\n  \
    \  return l * r;\n  }\n  static constexpr T identity = 1;\n};"
  dependsOn: []
  isVerificationFile: false
  path: other/multiplies_monoid.cpp
  requiredBy: []
  timestamp: '2020-02-23 00:23:42+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/zeta_transform.test.cpp
documentation_of: other/multiplies_monoid.cpp
layout: document
redirect_from:
- /library/other/multiplies_monoid.cpp
- /library/other/multiplies_monoid.cpp.html
title: other/multiplies_monoid.cpp
---
