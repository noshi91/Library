---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/w_ary_tree_set.cpp
    title: w-ary Tree Set
  - icon: ':heavy_check_mark:'
    path: other/ceildiv.cpp
    title: other/ceildiv.cpp
  - icon: ':heavy_check_mark:'
    path: other/fast_ios.cpp
    title: other/fast_ios.cpp
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/predecessor_problem
    links:
    - https://judge.yosupo.jp/problem/predecessor_problem
  bundledCode: "#line 1 \"test/w_ary_tree_set.pred.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/predecessor_problem\"\r\n\r\n#line 1 \"other/ceildiv.cpp\"\
    \ntemplate <class T> constexpr T ceildiv(const T &n, const T &d) {\r\n  return\
    \ n / d + (n % d != 0 ? 1 : 0);\r\n}\r\n#line 2 \"other/int_alias.cpp\"\n\n#include\
    \ <cstddef>\n#include <cstdint>\n\nusing i32 = std::int32_t;\nusing i64 = std::int64_t;\n\
    using u32 = std::uint32_t;\nusing u64 = std::uint64_t;\nusing isize = std::ptrdiff_t;\n\
    using usize = std::size_t;\n#line 3 \"data_structure/w_ary_tree_set.cpp\"\n\r\n\
    #include <array>\r\n#include <type_traits>\r\n\r\nnamespace w_ary_tree_set_impl\
    \ {\r\nconstexpr usize calc_c(usize n) {\r\n  usize ret = 1;\r\n  while (n > 64)\
    \ {\r\n    ret *= 64;\r\n    n /= 64;\r\n  }\r\n  return ret;\r\n}\r\nusize bsf(const\
    \ u64 x) {\r\n#ifdef __GNUC__\r\n  return __builtin_ctzll(x);\r\n#else\r\n  unsigned\
    \ long ret;\r\n  if (_BitScanForward(&ret, x & ~(~static_cast<u64>(0) << 32)))\
    \ {\r\n    return ret;\r\n  } else {\r\n    _BitScanForward(&ret, x >> 32);\r\n\
    \    return ret + 32;\r\n  }\r\n#endif\r\n}\r\nusize bsr(const u64 x) {\r\n#ifdef\
    \ __GNUC__\r\n  return 63 - __builtin_clzll(x);\r\n#else\r\n  unsigned long ret;\r\
    \n  if (_BitScanReverse(&ret, x >> 32)) {\r\n    return ret + 32;\r\n  } else\
    \ {\r\n    _BitScanReverse(&ret, x & ~(~static_cast<u64>(0) << 32));\r\n    return\
    \ ret;\r\n  }\r\n#endif\r\n}\r\n\r\ntemplate <usize N, class D = void> class w_ary_tree_set\
    \ {\r\n  static constexpr usize C = calc_c(N);\r\n\r\n  u64 map;\r\n  std::array<w_ary_tree_set<C>,\
    \ ceildiv(N, C)> child;\r\n\r\npublic:\r\n  w_ary_tree_set() : map(0), child()\
    \ {}\r\n\r\n  bool insert(const usize key) {\r\n    const usize pos = key / C;\r\
    \n    map |= static_cast<u64>(1) << pos;\r\n    return child[pos].insert(key %\
    \ C);\r\n  }\r\n\r\n  bool erase(const usize key) {\r\n    const usize pos = key\
    \ / C;\r\n    const bool ret = child[pos].erase(key % C);\r\n    if (child[pos]._get_map()\
    \ == 0) {\r\n      map &= ~(static_cast<u64>(1) << pos);\r\n    }\r\n    return\
    \ ret;\r\n  }\r\n\r\n  bool contains(const usize key) const {\r\n    return child[key\
    \ / C].contains(key % C);\r\n  }\r\n\r\n  usize min() const {\r\n    const usize\
    \ pos = bsf(map);\r\n    return pos * C + child[pos].min();\r\n  }\r\n\r\n  usize\
    \ max() const {\r\n    const usize pos = bsr(map);\r\n    return pos * C + child[pos].max();\r\
    \n  }\r\n\r\n  usize pred(const usize key) const {\r\n    const usize pos = key\
    \ / C;\r\n    const usize t = child[pos].pred(key % C);\r\n    if (t != -1) {\r\
    \n      return pos * C + t;\r\n    }\r\n    const u64 masked = map & ~(~static_cast<u64>(0)\
    \ << pos);\r\n    if (masked == 0) {\r\n      return -1;\r\n    }\r\n    const\
    \ usize pos2 = bsr(masked);\r\n    return pos2 * C + child[pos2].max();\r\n  }\r\
    \n\r\n  usize succ(const usize key) const {\r\n    const usize pos = key / C;\r\
    \n    const usize t = child[pos].succ(key % C);\r\n    if (t != -1) {\r\n    \
    \  return pos * C + t;\r\n    }\r\n    const u64 masked = map & ~(~static_cast<u64>(0)\
    \ >> (63 - pos));\r\n    if (masked == 0) {\r\n      return -1;\r\n    }\r\n \
    \   const usize pos2 = bsf(masked);\r\n    return pos2 * C + child[pos2].min();\r\
    \n  }\r\n\r\n  u64 _get_map() const { return map; }\r\n};\r\n\r\ntemplate <usize\
    \ N>\r\nclass w_ary_tree_set<N, typename std::enable_if<(N <= 64)>::type> {\r\n\
    \  u64 map;\r\n\r\npublic:\r\n  w_ary_tree_set() : map(0) {}\r\n\r\n  bool insert(const\
    \ usize key) {\r\n    const u64 pop = static_cast<u64>(1) << key;\r\n    if ((map\
    \ & pop) != 0) {\r\n      return false;\r\n    } else {\r\n      map |= pop;\r\
    \n      return true;\r\n    }\r\n  }\r\n\r\n  bool erase(const usize key) {\r\n\
    \    const u64 pop = static_cast<u64>(1) << key;\r\n    if ((map & pop) != 0)\
    \ {\r\n      map &= ~pop;\r\n      return true;\r\n    } else {\r\n      return\
    \ false;\r\n    }\r\n  }\r\n\r\n  bool contains(const usize key) const {\r\n \
    \   return (map & static_cast<u64>(1) << key) != 0;\r\n  }\r\n\r\n  usize min()\
    \ const { return bsf(map); }\r\n\r\n  usize max() const { return bsr(map); }\r\
    \n\r\n  usize pred(const usize key) const {\r\n    const u64 masked = map & ~(~static_cast<u64>(0)\
    \ << key);\r\n    if (masked == 0) {\r\n      return -1;\r\n    }\r\n    return\
    \ bsr(masked);\r\n  }\r\n\r\n  usize succ(const usize key) const {\r\n    const\
    \ u64 masked = map & (~static_cast<u64>(0) << key);\r\n    if (masked == 0) {\r\
    \n      return -1;\r\n    }\r\n    return bsf(masked);\r\n  }\r\n\r\n  u64 _get_map()\
    \ const { return map; }\r\n};\r\n\r\n} // namespace w_ary_tree_set_impl\r\n\r\n\
    template <usize N>\r\nusing w_ary_tree_set = w_ary_tree_set_impl::w_ary_tree_set<N>;\r\
    \n\r\n/**\r\n * @brief w-ary Tree Set\r\n */\r\n#line 4 \"test/w_ary_tree_set.pred.test.cpp\"\
    \n\r\n#line 6 \"test/w_ary_tree_set.pred.test.cpp\"\n#include <algorithm>\r\n\
    #include <iostream>\r\n#include <string>\r\n#include <vector>\r\n\r\nint main()\
    \ {\r\n#line 1 \"other/fast_ios.cpp\"\nstd::ios::sync_with_stdio(false);\nstd::cin.tie(nullptr);\n\
    #line 13 \"test/w_ary_tree_set.pred.test.cpp\"\n\r\n  w_ary_tree_set<10000000>\
    \ wats;\r\n\r\n  usize N, Q;\r\n  std::cin >> N >> Q;\r\n  std::string T;\r\n\
    \  std::cin >> T;\r\n  for (usize i = 0; i != N; i += 1) {\r\n    if (T[i] ==\
    \ '1') {\r\n      wats.insert(i);\r\n    }\r\n  }\r\n  for (usize i = 0; i !=\
    \ Q; i += 1) {\r\n    u32 type;\r\n    usize k;\r\n    std::cin >> type >> k;\r\
    \n    if (type == 0) {\r\n      wats.insert(k);\r\n    } else if (type == 1) {\r\
    \n      wats.erase(k);\r\n    } else if (type == 2) {\r\n      std::cout << wats.contains(k)\
    \ << \"\\n\";\r\n    } else if (type == 3) {\r\n      std::cout << static_cast<isize>(wats.succ(k))\
    \ << \"\\n\";\r\n    } else {\r\n      std::cout << static_cast<isize>(wats.pred(k\
    \ + 1)) << \"\\n\";\r\n    }\r\n  }\r\n\r\n  return 0;\r\n}\r\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/predecessor_problem\"\r\
    \n\r\n#include \"data_structure/w_ary_tree_set.cpp\"\r\n\r\n#include \"other/int_alias.cpp\"\
    \r\n#include <algorithm>\r\n#include <iostream>\r\n#include <string>\r\n#include\
    \ <vector>\r\n\r\nint main() {\r\n#include \"other/fast_ios.cpp\"\r\n\r\n  w_ary_tree_set<10000000>\
    \ wats;\r\n\r\n  usize N, Q;\r\n  std::cin >> N >> Q;\r\n  std::string T;\r\n\
    \  std::cin >> T;\r\n  for (usize i = 0; i != N; i += 1) {\r\n    if (T[i] ==\
    \ '1') {\r\n      wats.insert(i);\r\n    }\r\n  }\r\n  for (usize i = 0; i !=\
    \ Q; i += 1) {\r\n    u32 type;\r\n    usize k;\r\n    std::cin >> type >> k;\r\
    \n    if (type == 0) {\r\n      wats.insert(k);\r\n    } else if (type == 1) {\r\
    \n      wats.erase(k);\r\n    } else if (type == 2) {\r\n      std::cout << wats.contains(k)\
    \ << \"\\n\";\r\n    } else if (type == 3) {\r\n      std::cout << static_cast<isize>(wats.succ(k))\
    \ << \"\\n\";\r\n    } else {\r\n      std::cout << static_cast<isize>(wats.pred(k\
    \ + 1)) << \"\\n\";\r\n    }\r\n  }\r\n\r\n  return 0;\r\n}\r\n"
  dependsOn:
  - data_structure/w_ary_tree_set.cpp
  - other/ceildiv.cpp
  - other/int_alias.cpp
  - other/fast_ios.cpp
  isVerificationFile: true
  path: test/w_ary_tree_set.pred.test.cpp
  requiredBy: []
  timestamp: '2021-09-15 01:28:19+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/w_ary_tree_set.pred.test.cpp
layout: document
redirect_from:
- /verify/test/w_ary_tree_set.pred.test.cpp
- /verify/test/w_ary_tree_set.pred.test.cpp.html
title: test/w_ary_tree_set.pred.test.cpp
---
