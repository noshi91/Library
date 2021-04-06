---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/affine.cpp
    title: other/affine.cpp
  - icon: ':heavy_check_mark:'
    path: other/cartesian_product_monoid.cpp
    title: other/cartesian_product_monoid.cpp
  - icon: ':heavy_check_mark:'
    path: other/plus_monoid.cpp
    title: other/plus_monoid.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/lazy_segment_tree.test.cpp
    title: test/lazy_segment_tree.test.cpp
  _isVerificationFailed: false
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
    };\n#line 1 \"other/cartesian_product_monoid.cpp\"\n#include <utility>\n\ntemplate\
    \ <class M, class N> class cartesian_product_monoid {\n  using T = std::pair<typename\
    \ M::value_type, typename N::value_type>;\n\npublic:\n  using value_type = T;\n\
    \  static constexpr T operation(const T &l, const T &r) noexcept {\n    return\
    \ T(M::operation(l.first, r.first), N::operation(l.second, r.second));\n  }\n\
    \  static constexpr T identity{M::identity, N::identity};\n};\n#line 1 \"other/plus_monoid.cpp\"\
    \ntemplate <class T> class plus_monoid {\npublic:\n  using value_type = T;\n \
    \ static T operation(const T l, const T r) { return l + r; }\n  static constexpr\
    \ T identity = 0;\n};\n#line 4 \"other/sum_affine_action.cpp\"\n\ntemplate <class\
    \ T> class sum_affine_action {\npublic:\n  using value_structure =\n      cartesian_product_monoid<plus_monoid<T>,\
    \ plus_monoid<T>>;\n  using operator_structure = affine_composite_monoid<T>;\n\
    \nprivate:\n  using U = typename value_structure::value_type;\n  using E = typename\
    \ operator_structure::value_type;\n\npublic:\n  static constexpr U operation(const\
    \ U &l, const E &r) {\n    return U(l.first * r.a + l.second * r.b, l.second);\n\
    \  }\n};\n"
  code: "#include \"other/affine.cpp\"\n#include \"other/cartesian_product_monoid.cpp\"\
    \n#include \"other/plus_monoid.cpp\"\n\ntemplate <class T> class sum_affine_action\
    \ {\npublic:\n  using value_structure =\n      cartesian_product_monoid<plus_monoid<T>,\
    \ plus_monoid<T>>;\n  using operator_structure = affine_composite_monoid<T>;\n\
    \nprivate:\n  using U = typename value_structure::value_type;\n  using E = typename\
    \ operator_structure::value_type;\n\npublic:\n  static constexpr U operation(const\
    \ U &l, const E &r) {\n    return U(l.first * r.a + l.second * r.b, l.second);\n\
    \  }\n};"
  dependsOn:
  - other/affine.cpp
  - other/cartesian_product_monoid.cpp
  - other/plus_monoid.cpp
  isVerificationFile: false
  path: other/sum_affine_action.cpp
  requiredBy: []
  timestamp: '2020-02-14 17:46:13+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/lazy_segment_tree.test.cpp
documentation_of: other/sum_affine_action.cpp
layout: document
redirect_from:
- /library/other/sum_affine_action.cpp
- /library/other/sum_affine_action.cpp.html
title: other/sum_affine_action.cpp
---
