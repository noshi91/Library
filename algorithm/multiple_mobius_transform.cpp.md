---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "Multiple M\xF6bius Transform"
    links: []
  bundledCode: "#line 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
    \nusing i32 = std::int32_t;\nusing i64 = std::int64_t;\nusing u32 = std::uint32_t;\n\
    using u64 = std::uint64_t;\nusing isize = std::ptrdiff_t;\nusing usize = std::size_t;\n\
    #line 2 \"algorithm/multiple_mobius_transform.cpp\"\n\n#include <vector>\n\ntemplate\
    \ <class G>\nvoid multiple_mobius_transform(std::vector<typename G::value_type>\
    \ &a) {\n  const usize n = a.size();\n  std::vector<bool> sieve(n, true);\n  for\
    \ (usize p = 2; p < n; p += 1) {\n    if (!sieve[p])\n      continue;\n    for\
    \ (usize k = 1; k * p < n; k += 1) {\n      sieve[k * p] = false;\n      a[k]\
    \ = G::operation(a[k], G::inverse(a[k * p]));\n    }\n  }\n}\n\n/**\n * @brief\
    \ Multiple M\xF6bius Transform\n */\n"
  code: "#include \"other/int_alias.cpp\"\n\n#include <vector>\n\ntemplate <class\
    \ G>\nvoid multiple_mobius_transform(std::vector<typename G::value_type> &a) {\n\
    \  const usize n = a.size();\n  std::vector<bool> sieve(n, true);\n  for (usize\
    \ p = 2; p < n; p += 1) {\n    if (!sieve[p])\n      continue;\n    for (usize\
    \ k = 1; k * p < n; k += 1) {\n      sieve[k * p] = false;\n      a[k] = G::operation(a[k],\
    \ G::inverse(a[k * p]));\n    }\n  }\n}\n\n/**\n * @brief Multiple M\xF6bius Transform\n\
    \ */\n"
  dependsOn:
  - other/int_alias.cpp
  isVerificationFile: false
  path: algorithm/multiple_mobius_transform.cpp
  requiredBy: []
  timestamp: '2020-03-11 23:32:43+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: algorithm/multiple_mobius_transform.cpp
layout: document
redirect_from:
- /library/algorithm/multiple_mobius_transform.cpp
- /library/algorithm/multiple_mobius_transform.cpp.html
title: "Multiple M\xF6bius Transform"
---
