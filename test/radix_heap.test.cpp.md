---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/radix_heap.cpp
    title: Radix Heap
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
    path: other/fast_ios.cpp
    title: other/fast_ios.cpp
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja
  bundledCode: "#line 1 \"test/radix_heap.test.cpp\"\n#define PROBLEM            \
    \                                                    \\\n  \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja\"\
    \n\n#line 2 \"other/bit_width.cpp\"\n\n#line 2 \"other/countl_zero.cpp\"\n\n#line\
    \ 2 \"other/countr_zero.cpp\"\n\n#line 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n\
    #include <cstdint>\n\nusing i32 = std::int32_t;\nusing i64 = std::int64_t;\nusing\
    \ u32 = std::uint32_t;\nusing u64 = std::uint64_t;\nusing isize = std::ptrdiff_t;\n\
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
    \ */\n#line 5 \"test/radix_heap.test.cpp\"\n\n#include <iostream>\n#line 10 \"\
    test/radix_heap.test.cpp\"\n\nint main() {\n#line 1 \"other/fast_ios.cpp\"\nstd::ios::sync_with_stdio(false);\n\
    std::cin.tie(nullptr);\n#line 13 \"test/radix_heap.test.cpp\"\n\n  int n, m, r;\n\
    \  std::cin >> n >> m >> r;\n  std::vector<std::vector<std::pair<int, int>>> g(n);\n\
    \  for (int i = 0; i != m; i += 1) {\n    int s, t, d;\n    std::cin >> s >> t\
    \ >> d;\n    g[s].emplace_back(d, t);\n  }\n  constexpr int Inf = std::numeric_limits<int>::max();\n\
    \  std::vector<int> dist(n, Inf);\n  dist[r] = 0;\n  radix_heap<int> heap;\n \
    \ int size = 0;\n  heap.push({0, r});\n  size += 1;\n  while (size != 0) {\n \
    \   const auto [c_, v] = heap.pop();\n    const int c = c_;\n    size -= 1;\n\
    \    if (dist[v] < c)\n      continue;\n    for (const auto &[d, u] : g[v]) {\n\
    \      if (c + d < dist[u]) {\n        dist[u] = c + d;\n        heap.push({dist[u],\
    \ u});\n        size += 1;\n      }\n    }\n  }\n  for (int i = 0; i != n; i +=\
    \ 1) {\n    if (dist[i] < Inf)\n      std::cout << dist[i];\n    else\n      std::cout\
    \ << \"INF\";\n    std::cout << \"\\n\";\n  }\n}\n"
  code: "#define PROBLEM                                                         \
    \       \\\n  \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja\"\
    \n\n#include \"data_structure/radix_heap.cpp\"\n\n#include <iostream>\n#include\
    \ <limits>\n#include <utility>\n#include <vector>\n\nint main() {\n#include \"\
    other/fast_ios.cpp\"\n\n  int n, m, r;\n  std::cin >> n >> m >> r;\n  std::vector<std::vector<std::pair<int,\
    \ int>>> g(n);\n  for (int i = 0; i != m; i += 1) {\n    int s, t, d;\n    std::cin\
    \ >> s >> t >> d;\n    g[s].emplace_back(d, t);\n  }\n  constexpr int Inf = std::numeric_limits<int>::max();\n\
    \  std::vector<int> dist(n, Inf);\n  dist[r] = 0;\n  radix_heap<int> heap;\n \
    \ int size = 0;\n  heap.push({0, r});\n  size += 1;\n  while (size != 0) {\n \
    \   const auto [c_, v] = heap.pop();\n    const int c = c_;\n    size -= 1;\n\
    \    if (dist[v] < c)\n      continue;\n    for (const auto &[d, u] : g[v]) {\n\
    \      if (c + d < dist[u]) {\n        dist[u] = c + d;\n        heap.push({dist[u],\
    \ u});\n        size += 1;\n      }\n    }\n  }\n  for (int i = 0; i != n; i +=\
    \ 1) {\n    if (dist[i] < Inf)\n      std::cout << dist[i];\n    else\n      std::cout\
    \ << \"INF\";\n    std::cout << \"\\n\";\n  }\n}"
  dependsOn:
  - data_structure/radix_heap.cpp
  - other/bit_width.cpp
  - other/countl_zero.cpp
  - other/countr_zero.cpp
  - other/int_alias.cpp
  - other/fast_ios.cpp
  isVerificationFile: true
  path: test/radix_heap.test.cpp
  requiredBy: []
  timestamp: '2020-03-11 22:42:07+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/radix_heap.test.cpp
layout: document
redirect_from:
- /verify/test/radix_heap.test.cpp
- /verify/test/radix_heap.test.cpp.html
title: test/radix_heap.test.cpp
---
