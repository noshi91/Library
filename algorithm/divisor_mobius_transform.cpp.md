---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/ceildiv.cpp
    title: other/ceildiv.cpp
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "Divisor M\xF6bius Transform"
    links: []
  bundledCode: "#line 1 \"other/ceildiv.cpp\"\ntemplate <class T> constexpr T ceildiv(const\
    \ T &n, const T &d) {\r\n  return n / d + (n % d != 0 ? 1 : 0);\r\n}\r\n#line\
    \ 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\nusing\
    \ i32 = std::int32_t;\nusing i64 = std::int64_t;\nusing u32 = std::uint32_t;\n\
    using u64 = std::uint64_t;\nusing isize = std::ptrdiff_t;\nusing usize = std::size_t;\n\
    #line 3 \"algorithm/divisor_mobius_transform.cpp\"\n\n#include <vector>\n\ntemplate\
    \ <class G>\nvoid divisor_mobius_transform(std::vector<typename G::value_type>\
    \ &a) {\n  const usize n = a.size();\n  std::vector<bool> sieve(n, true);\n  for\
    \ (usize p = 2; p < n; p += 1) {\n    if (!sieve[p])\n      continue;\n    for\
    \ (usize k = ceildiv(n, p); k != 1;) {\n      k -= 1;\n      sieve[k * p] = false;\n\
    \      a[k * p] = G::operation(G::inverse(a[k]), a[k * p]);\n    }\n  }\n}\n\n\
    /**\n * @brief Divisor M\xF6bius Transform\n */\n"
  code: "#include \"other/ceildiv.cpp\"\n#include \"other/int_alias.cpp\"\n\n#include\
    \ <vector>\n\ntemplate <class G>\nvoid divisor_mobius_transform(std::vector<typename\
    \ G::value_type> &a) {\n  const usize n = a.size();\n  std::vector<bool> sieve(n,\
    \ true);\n  for (usize p = 2; p < n; p += 1) {\n    if (!sieve[p])\n      continue;\n\
    \    for (usize k = ceildiv(n, p); k != 1;) {\n      k -= 1;\n      sieve[k *\
    \ p] = false;\n      a[k * p] = G::operation(G::inverse(a[k]), a[k * p]);\n  \
    \  }\n  }\n}\n\n/**\n * @brief Divisor M\xF6bius Transform\n */\n"
  dependsOn:
  - other/ceildiv.cpp
  - other/int_alias.cpp
  isVerificationFile: false
  path: algorithm/divisor_mobius_transform.cpp
  requiredBy: []
  timestamp: '2020-09-11 14:24:32+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: algorithm/divisor_mobius_transform.cpp
layout: document
redirect_from:
- /library/algorithm/divisor_mobius_transform.cpp
- /library/algorithm/divisor_mobius_transform.cpp.html
title: "Divisor M\xF6bius Transform"
---
