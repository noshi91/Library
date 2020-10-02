---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
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
  bundledCode: "#line 1 \"other/opposite_ordered_set.cpp\"\ntemplate <class W> class\
    \ opposite_ordered_set {\n  using T = typename W::value_type;\n\npublic:\n  using\
    \ value_type = T;\n  static constexpr bool compare(const T &l, const T &r) noexcept\
    \ {\n    return W::compare(r, l);\n  }\n};\n"
  code: "template <class W> class opposite_ordered_set {\n  using T = typename W::value_type;\n\
    \npublic:\n  using value_type = T;\n  static constexpr bool compare(const T &l,\
    \ const T &r) noexcept {\n    return W::compare(r, l);\n  }\n};"
  dependsOn: []
  isVerificationFile: false
  path: other/opposite_ordered_set.cpp
  requiredBy: []
  timestamp: '2020-02-15 23:51:29+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/pairing_heap.test.cpp
  - test/larsch.test.cpp
documentation_of: other/opposite_ordered_set.cpp
layout: document
redirect_from:
- /library/other/opposite_ordered_set.cpp
- /library/other/opposite_ordered_set.cpp.html
title: other/opposite_ordered_set.cpp
---
