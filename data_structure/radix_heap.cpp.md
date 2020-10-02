---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/bit_width.cpp
    title: other/bit_width.cpp
  - icon: ':heavy_check_mark:'
    path: other/countl_zero.cpp
    title: other/countl_zero.cpp
  - icon: ':heavy_check_mark:'
    path: other/countr_zero.cpp
    title: other/countr_zero.cpp
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/radix_heap.test.cpp
    title: test/radix_heap.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Radix Heap
    links:
    - https://yosupo.hatenablog.com/entry/2015/04/03/224649
  bundledCode: "#line 2 \"other/bit_width.cpp\"\n\n#line 2 \"other/countl_zero.cpp\"\
    \n\n#line 2 \"other/countr_zero.cpp\"\n\n#line 2 \"other/int_alias.cpp\"\n\n#include\
    \ <cstddef>\n#include <cstdint>\n\nusing i32 = std::int32_t;\nusing i64 = std::int64_t;\n\
    using u32 = std::uint32_t;\nusing u64 = std::uint64_t;\nusing isize = std::ptrdiff_t;\n\
    using usize = std::size_t;\n#line 4 \"other/countr_zero.cpp\"\n\n#include <array>\n\
    \nusize countr_zero(u64 x) {\n  if (x == 0)\n    return 64;\n#ifdef __GNUC__\n\
    \  return __builtin_ctzll(x);\n#else\n  constexpr std::array<usize, 64> table\
    \ = {\n      0,  1,  2,  7,  3,  13, 8,  27, 4,  33, 14, 36, 9,  49, 28, 19,\n\
    \      5,  25, 34, 17, 15, 53, 37, 55, 10, 46, 50, 39, 29, 42, 20, 57,\n     \
    \ 63, 6,  12, 26, 32, 35, 48, 18, 24, 16, 52, 54, 45, 38, 41, 56,\n      62, 11,\
    \ 31, 47, 23, 51, 44, 40, 61, 30, 22, 43, 60, 21, 59, 58};\n  return table[(x\
    \ & ~x + 1) * 0x218A7A392DD9ABF >> 58 & 0x3F];\n#endif\n}\n#line 5 \"other/countl_zero.cpp\"\
    \n\nusize countl_zero(u64 x) {\n#ifdef __GNUC__\n  return x == 0 ? 64 : __builtin_clzll(x);\n\
    #else\n  x |= x >> 1;\n  x |= x >> 2;\n  x |= x >> 4;\n  x |= x >> 8;\n  x |=\
    \ x >> 16;\n  x |= x >> 32;\n  return 64 - countr_zero(~x);\n#endif\n}\n#line\
    \ 5 \"other/bit_width.cpp\"\n\nusize bit_width(const u64 x) { return 64 - countl_zero(x);\
    \ }\n#line 3 \"data_structure/radix_heap.cpp\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <limits>\n#include <utility>\n#include <vector>\n\ntemplate\
    \ <class T> class radix_heap {\n  using V = std::pair<u64, T>;\n\npublic:\n  using\
    \ key_type = u64;\n  using mapped_type = T;\n  using value_type = V;\n\nprivate:\n\
    \  std::vector<std::vector<V>> u;\n  u64 last;\n\npublic:\n  radix_heap() : u(),\
    \ last(0) {}\n\n  void push(V x) {\n    assert(last <= x.first);\n\n    const\
    \ usize i = bit_width(x.first ^ last);\n    if (u.size() <= i)\n      u.resize(i\
    \ + 1);\n    u[i].push_back(std::move(x));\n  }\n\n  V pop() {\n    if (u[0].empty())\
    \ {\n      usize i = 1;\n      while (u[i].empty())\n        i += 1;\n      last\
    \ = std::numeric_limits<u64>::max();\n      for (const V &e : u[i])\n        last\
    \ = std::min(last, e.first);\n      for (V &e : u[i]) {\n        const usize j\
    \ = bit_width(e.first ^ last);\n        u[j].push_back(std::move(e));\n      }\n\
    \      u[i].clear();\n    }\n    V ret = std::move(u[0].back());\n    u[0].pop_back();\n\
    \    return ret;\n  }\n};\n\n/**\n * @brief Radix Heap\n * @see https://yosupo.hatenablog.com/entry/2015/04/03/224649\n\
    \ */\n"
  code: "#include \"other/bit_width.cpp\"\n#include \"other/int_alias.cpp\"\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <limits>\n#include <utility>\n#include\
    \ <vector>\n\ntemplate <class T> class radix_heap {\n  using V = std::pair<u64,\
    \ T>;\n\npublic:\n  using key_type = u64;\n  using mapped_type = T;\n  using value_type\
    \ = V;\n\nprivate:\n  std::vector<std::vector<V>> u;\n  u64 last;\n\npublic:\n\
    \  radix_heap() : u(), last(0) {}\n\n  void push(V x) {\n    assert(last <= x.first);\n\
    \n    const usize i = bit_width(x.first ^ last);\n    if (u.size() <= i)\n   \
    \   u.resize(i + 1);\n    u[i].push_back(std::move(x));\n  }\n\n  V pop() {\n\
    \    if (u[0].empty()) {\n      usize i = 1;\n      while (u[i].empty())\n   \
    \     i += 1;\n      last = std::numeric_limits<u64>::max();\n      for (const\
    \ V &e : u[i])\n        last = std::min(last, e.first);\n      for (V &e : u[i])\
    \ {\n        const usize j = bit_width(e.first ^ last);\n        u[j].push_back(std::move(e));\n\
    \      }\n      u[i].clear();\n    }\n    V ret = std::move(u[0].back());\n  \
    \  u[0].pop_back();\n    return ret;\n  }\n};\n\n/**\n * @brief Radix Heap\n *\
    \ @see https://yosupo.hatenablog.com/entry/2015/04/03/224649\n */\n"
  dependsOn:
  - other/bit_width.cpp
  - other/countl_zero.cpp
  - other/countr_zero.cpp
  - other/int_alias.cpp
  isVerificationFile: false
  path: data_structure/radix_heap.cpp
  requiredBy: []
  timestamp: '2020-03-11 22:42:07+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/radix_heap.test.cpp
documentation_of: data_structure/radix_heap.cpp
layout: document
redirect_from:
- /library/data_structure/radix_heap.cpp
- /library/data_structure/radix_heap.cpp.html
title: Radix Heap
---
