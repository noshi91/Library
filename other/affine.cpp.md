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
  - icon: ':heavy_check_mark:'
    path: test/queue_aggregation.test.cpp
    title: test/queue_aggregation.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/segment_tree.test.cpp
    title: test/segment_tree.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"other/affine.cpp\"\ntemplate <class T> class affine {\n\
    public:\n  T a;\n  T b;\n\n  constexpr affine(const T &a = 1, const T &b = 0)\
    \ noexcept : a(a), b(b) {}\n\n  constexpr T evaluate(const T &x) const noexcept\
    \ { return x * a + b; }\n  friend constexpr affine operator+(const affine &l,\
    \ const affine &r) noexcept {\n    return affine(l.a + r.a, l.b + r.b);\n  }\n\
    \  constexpr affine composite(const affine &r) const noexcept {\n    return affine(a\
    \ * r.a, b * r.a + r.b);\n  }\n};\n\ntemplate <class T> class affine_composite_monoid\
    \ {\npublic:\n  using value_type = affine<T>;\n  static constexpr value_type operation(const\
    \ value_type &l,\n                                        const value_type &r)\
    \ noexcept {\n    return l.composite(r);\n  }\n  static constexpr value_type identity{};\n\
    };\n"
  code: "template <class T> class affine {\npublic:\n  T a;\n  T b;\n\n  constexpr\
    \ affine(const T &a = 1, const T &b = 0) noexcept : a(a), b(b) {}\n\n  constexpr\
    \ T evaluate(const T &x) const noexcept { return x * a + b; }\n  friend constexpr\
    \ affine operator+(const affine &l, const affine &r) noexcept {\n    return affine(l.a\
    \ + r.a, l.b + r.b);\n  }\n  constexpr affine composite(const affine &r) const\
    \ noexcept {\n    return affine(a * r.a, b * r.a + r.b);\n  }\n};\n\ntemplate\
    \ <class T> class affine_composite_monoid {\npublic:\n  using value_type = affine<T>;\n\
    \  static constexpr value_type operation(const value_type &l,\n              \
    \                          const value_type &r) noexcept {\n    return l.composite(r);\n\
    \  }\n  static constexpr value_type identity{};\n};"
  dependsOn: []
  isVerificationFile: false
  path: other/affine.cpp
  requiredBy:
  - other/sum_affine_action.cpp
  timestamp: '2020-02-09 00:25:15+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/segment_tree.test.cpp
  - test/lazy_segment_tree.test.cpp
  - test/queue_aggregation.test.cpp
documentation_of: other/affine.cpp
layout: document
redirect_from:
- /library/other/affine.cpp
- /library/other/affine.cpp.html
title: other/affine.cpp
---
