---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/zeta_transform.test.cpp
    title: test/zeta_transform.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Superset Zeta Transform
    links: []
  bundledCode: "#line 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
    \nusing i32 = std::int32_t;\nusing i64 = std::int64_t;\nusing u32 = std::uint32_t;\n\
    using u64 = std::uint64_t;\nusing isize = std::ptrdiff_t;\nusing usize = std::size_t;\n\
    #line 2 \"algorithm/superset_zeta_transform.cpp\"\n\n#include <vector>\n\ntemplate\
    \ <class S>\nvoid superset_zeta_transform(std::vector<typename S::value_type>\
    \ &a) {\n  const usize n = a.size();\n  for (usize i = 1; i < n; i *= 2) {\n \
    \   for (usize j = 0; j != n; j += 1) {\n      if ((j & i) != 0)\n        a[j\
    \ & ~i] = S::operation(a[j & ~i], a[j]);\n    }\n  }\n}\n\n/**\n * @brief Superset\
    \ Zeta Transform\n */\n"
  code: "#include \"other/int_alias.cpp\"\n\n#include <vector>\n\ntemplate <class\
    \ S>\nvoid superset_zeta_transform(std::vector<typename S::value_type> &a) {\n\
    \  const usize n = a.size();\n  for (usize i = 1; i < n; i *= 2) {\n    for (usize\
    \ j = 0; j != n; j += 1) {\n      if ((j & i) != 0)\n        a[j & ~i] = S::operation(a[j\
    \ & ~i], a[j]);\n    }\n  }\n}\n\n/**\n * @brief Superset Zeta Transform\n */\n"
  dependsOn:
  - other/int_alias.cpp
  isVerificationFile: false
  path: algorithm/superset_zeta_transform.cpp
  requiredBy: []
  timestamp: '2020-03-11 23:32:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/zeta_transform.test.cpp
documentation_of: algorithm/superset_zeta_transform.cpp
layout: document
redirect_from:
- /library/algorithm/superset_zeta_transform.cpp
- /library/algorithm/superset_zeta_transform.cpp.html
title: Superset Zeta Transform
---
