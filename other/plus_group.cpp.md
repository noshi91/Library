---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/potentialized_union_find.test.cpp
    title: test/potentialized_union_find.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/zeta_transform.test.cpp
    title: test/zeta_transform.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"other/plus_group.cpp\"\ntemplate <class T> class plus_group\
    \ {\npublic:\n  using value_type = T;\n  static constexpr T operation(const T\
    \ &l, const T &r) noexcept {\n    return l + r;\n  }\n  static constexpr T identity\
    \ = 0;\n  static constexpr T inverse(const T &x) noexcept { return -x; }\n};\n"
  code: "template <class T> class plus_group {\npublic:\n  using value_type = T;\n\
    \  static constexpr T operation(const T &l, const T &r) noexcept {\n    return\
    \ l + r;\n  }\n  static constexpr T identity = 0;\n  static constexpr T inverse(const\
    \ T &x) noexcept { return -x; }\n};"
  dependsOn: []
  isVerificationFile: false
  path: other/plus_group.cpp
  requiredBy: []
  timestamp: '2020-02-09 00:38:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/potentialized_union_find.test.cpp
  - test/zeta_transform.test.cpp
documentation_of: other/plus_group.cpp
layout: document
redirect_from:
- /library/other/plus_group.cpp
- /library/other/plus_group.cpp.html
title: other/plus_group.cpp
---
