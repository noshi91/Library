---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/min_semigroup.cpp
    title: other/min_semigroup.cpp
  - icon: ':heavy_check_mark:'
    path: other/right_zero_semigroup.cpp
    title: other/right_zero_semigroup.cpp
  - icon: ':heavy_check_mark:'
    path: other/semigroup_to_monoid.cpp
    title: other/semigroup_to_monoid.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"other/min_semigroup.cpp\"\ntemplate <class W> class min_semigroup\
    \ {\n  using T = typename W::value_type;\n\npublic:\n  using value_type = T;\n\
    \  static constexpr T operation(const T &l, const T &r) noexcept {\n    return\
    \ W::compare(l, r) ? l : r;\n  }\n};\n#line 1 \"other/right_zero_semigroup.cpp\"\
    \ntemplate <class T> class right_zero_semigroup {\npublic:\n  using value_type\
    \ = T;\n  static constexpr T operation(const T &, const T &r) noexcept { return\
    \ r; }\n};\n#line 1 \"other/semigroup_to_monoid.cpp\"\n#include <optional>\n#include\
    \ <utility>\n\ntemplate <class S> class semigroup_to_monoid {\n  using T = std::optional<typename\
    \ S::value_type>;\n\npublic:\n  using value_type = T;\n  static constexpr T operation(const\
    \ T &l, const T &r) noexcept {\n    if (!l)\n      return r;\n    if (!r)\n  \
    \    return l;\n    return T(std::in_place, S::operation(*l, *r));\n  }\n  static\
    \ constexpr T identity{std::nullopt};\n};\n#line 4 \"other/min_assign_action.cpp\"\
    \n\n#line 6 \"other/min_assign_action.cpp\"\n\ntemplate <class W> class min_assign_action\
    \ {\n  using T = typename W::value_type;\n  using U = std::optional<T>;\n\npublic:\n\
    \  using value_structure = semigroup_to_monoid<min_semigroup<W>>;\n  using operator_structure\
    \ = semigroup_to_monoid<right_zero_semigroup<T>>;\n  static constexpr U operation(const\
    \ U &l, const U &r) noexcept {\n    return r ? r : l;\n  }\n};\n"
  code: "#include \"other/min_semigroup.cpp\"\n#include \"other/right_zero_semigroup.cpp\"\
    \n#include \"other/semigroup_to_monoid.cpp\"\n\n#include <optional>\n\ntemplate\
    \ <class W> class min_assign_action {\n  using T = typename W::value_type;\n \
    \ using U = std::optional<T>;\n\npublic:\n  using value_structure = semigroup_to_monoid<min_semigroup<W>>;\n\
    \  using operator_structure = semigroup_to_monoid<right_zero_semigroup<T>>;\n\
    \  static constexpr U operation(const U &l, const U &r) noexcept {\n    return\
    \ r ? r : l;\n  }\n};"
  dependsOn:
  - other/min_semigroup.cpp
  - other/right_zero_semigroup.cpp
  - other/semigroup_to_monoid.cpp
  isVerificationFile: false
  path: other/min_assign_action.cpp
  requiredBy: []
  timestamp: '2020-02-14 16:53:57+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: other/min_assign_action.cpp
layout: document
redirect_from:
- /library/other/min_assign_action.cpp
- /library/other/min_assign_action.cpp.html
title: other/min_assign_action.cpp
---
