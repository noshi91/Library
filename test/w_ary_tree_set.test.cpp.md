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
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_9_C&lang=ja
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_9_C&lang=ja
  bundledCode: "#line 1 \"test/w_ary_tree_set.test.cpp\"\n#define PROBLEM        \
    \                                                        \\\r\n  \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_9_C&lang=ja\"\
    \r\n\r\n#line 1 \"other/ceildiv.cpp\"\ntemplate <class T> constexpr T ceildiv(const\
    \ T &n, const T &d) {\r\n  return n / d + (n % d != 0 ? 1 : 0);\r\n}\r\n#line\
    \ 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\nusing\
    \ i32 = std::int32_t;\nusing i64 = std::int64_t;\nusing u32 = std::uint32_t;\n\
    using u64 = std::uint64_t;\nusing isize = std::ptrdiff_t;\nusing usize = std::size_t;\n\
    #line 3 \"data_structure/w_ary_tree_set.cpp\"\n\r\n#include <array>\r\n#include\
    \ <type_traits>\r\n\r\nnamespace w_ary_tree_set_impl {\r\nconstexpr usize calc_c(usize\
    \ n) {\r\n  usize ret = 1;\r\n  while (n > 64) {\r\n    ret *= 64;\r\n    n /=\
    \ 64;\r\n  }\r\n  return ret;\r\n}\r\nusize bsf(const u64 x) {\r\n#ifdef __GNUC__\r\
    \n  return __builtin_ctzll(x);\r\n#else\r\n  unsigned long ret;\r\n  if (_BitScanForward(&ret,\
    \ x & ~(~static_cast<u64>(0) << 32))) {\r\n    return ret;\r\n  } else {\r\n \
    \   _BitScanForward(&ret, x >> 32);\r\n    return ret + 32;\r\n  }\r\n#endif\r\
    \n}\r\nusize bsr(const u64 x) {\r\n#ifdef __GNUC__\r\n  return 63 - __builtin_clzll(x);\r\
    \n#else\r\n  unsigned long ret;\r\n  if (_BitScanReverse(&ret, x >> 32)) {\r\n\
    \    return ret + 32;\r\n  } else {\r\n    _BitScanReverse(&ret, x & ~(~static_cast<u64>(0)\
    \ << 32));\r\n    return ret;\r\n  }\r\n#endif\r\n}\r\n\r\ntemplate <usize N,\
    \ class D = void> class w_ary_tree_set {\r\n  static constexpr usize C = calc_c(N);\r\
    \n\r\n  u64 map;\r\n  std::array<w_ary_tree_set<C>, ceildiv(N, C)> child;\r\n\r\
    \npublic:\r\n  w_ary_tree_set() : map(0), child() {}\r\n\r\n  bool insert(const\
    \ usize key) {\r\n    const usize pos = key / C;\r\n    map |= static_cast<u64>(1)\
    \ << pos;\r\n    return child[pos].insert(key % C);\r\n  }\r\n\r\n  bool erase(const\
    \ usize key) {\r\n    const usize pos = key / C;\r\n    const bool ret = child[pos].erase(key\
    \ % C);\r\n    if (child[pos]._get_map() == 0) {\r\n      map &= ~(static_cast<u64>(1)\
    \ << pos);\r\n    }\r\n    return ret;\r\n  }\r\n\r\n  bool contains(const usize\
    \ key) const {\r\n    return child[key / C].contains(key % C);\r\n  }\r\n\r\n\
    \  usize min() const {\r\n    const usize pos = bsf(map);\r\n    return pos *\
    \ C + child[pos].min();\r\n  }\r\n\r\n  usize max() const {\r\n    const usize\
    \ pos = bsr(map);\r\n    return pos * C + child[pos].max();\r\n  }\r\n\r\n  u64\
    \ _get_map() const { return map; }\r\n};\r\n\r\ntemplate <usize N>\r\nclass w_ary_tree_set<N,\
    \ typename std::enable_if<(N <= 64)>::type> {\r\n  u64 map;\r\n\r\npublic:\r\n\
    \  w_ary_tree_set() : map(0) {}\r\n\r\n  bool insert(const usize key) {\r\n  \
    \  const u64 pop = static_cast<u64>(1) << key;\r\n    if ((map & pop) != 0) {\r\
    \n      return false;\r\n    } else {\r\n      map |= pop;\r\n      return true;\r\
    \n    }\r\n  }\r\n\r\n  bool erase(const usize key) {\r\n    const u64 pop = static_cast<u64>(1)\
    \ << key;\r\n    if ((map & pop) != 0) {\r\n      map &= ~pop;\r\n      return\
    \ true;\r\n    } else {\r\n      return false;\r\n    }\r\n  }\r\n\r\n  bool contains(const\
    \ usize key) const {\r\n    return (map & static_cast<u64>(1) << key) != 0;\r\n\
    \  }\r\n\r\n  usize min() const { return bsf(map); }\r\n\r\n  usize max() const\
    \ { return bsr(map); }\r\n\r\n  u64 _get_map() const { return map; }\r\n};\r\n\
    \r\n} // namespace w_ary_tree_set_impl\r\n\r\ntemplate <usize N>\r\nusing w_ary_tree_set\
    \ = w_ary_tree_set_impl::w_ary_tree_set<N>;\r\n\r\n/**\r\n * @brief w-ary Tree\
    \ Set\r\n */\r\n#line 5 \"test/w_ary_tree_set.test.cpp\"\n\r\n#line 7 \"test/w_ary_tree_set.test.cpp\"\
    \n#include <algorithm>\r\n#include <iostream>\r\n#include <string>\r\n#include\
    \ <vector>\r\n\r\nint main() {\r\n#line 1 \"other/fast_ios.cpp\"\nstd::ios::sync_with_stdio(false);\n\
    std::cin.tie(nullptr);\n#line 14 \"test/w_ary_tree_set.test.cpp\"\n\r\n  static\
    \ constexpr usize max_q = 2000000;\r\n\r\n  struct query_t {\r\n    bool t;\r\n\
    \    u32 key;\r\n  };\r\n  std::vector<query_t> q;\r\n  q.reserve(max_q);\r\n\
    \  std::vector<u32> v;\r\n  v.reserve(max_q);\r\n  std::string s;\r\n\r\n  while\
    \ (true) {\r\n    std::cin >> s;\r\n    if (s[2] == 's') {\r\n      u32 x;\r\n\
    \      std::cin >> x;\r\n      q.push_back({true, x});\r\n      v.push_back(x);\r\
    \n    } else if (s[2] == 't') {\r\n      q.push_back({false, 0});\r\n    } else\
    \ {\r\n      break;\r\n    }\r\n  }\r\n\r\n  std::sort(v.begin(), v.end());\r\n\
    \  v.erase(std::unique(v.begin(), v.end()), v.end());\r\n  std::vector<usize>\
    \ count(v.size(), 0);\r\n\r\n  w_ary_tree_set<max_q> wats;\r\n  for (const auto\
    \ &e : q) {\r\n    if (e.t) {\r\n      const usize i = std::lower_bound(v.begin(),\
    \ v.end(), e.key) - v.begin();\r\n      if (count[i] == 0) {\r\n        wats.insert(i);\r\
    \n      }\r\n      ++count[i];\r\n    } else {\r\n      const usize i = wats.max();\r\
    \n      std::cout << v[i] << \"\\n\";\r\n      --count[i];\r\n      if (count[i]\
    \ == 0) {\r\n        wats.erase(i);\r\n      }\r\n    }\r\n  }\r\n\r\n  return\
    \ 0;\r\n}\r\n"
  code: "#define PROBLEM                                                         \
    \       \\\r\n  \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_9_C&lang=ja\"\
    \r\n\r\n#include \"data_structure/w_ary_tree_set.cpp\"\r\n\r\n#include \"other/int_alias.cpp\"\
    \r\n#include <algorithm>\r\n#include <iostream>\r\n#include <string>\r\n#include\
    \ <vector>\r\n\r\nint main() {\r\n#include \"other/fast_ios.cpp\"\r\n\r\n  static\
    \ constexpr usize max_q = 2000000;\r\n\r\n  struct query_t {\r\n    bool t;\r\n\
    \    u32 key;\r\n  };\r\n  std::vector<query_t> q;\r\n  q.reserve(max_q);\r\n\
    \  std::vector<u32> v;\r\n  v.reserve(max_q);\r\n  std::string s;\r\n\r\n  while\
    \ (true) {\r\n    std::cin >> s;\r\n    if (s[2] == 's') {\r\n      u32 x;\r\n\
    \      std::cin >> x;\r\n      q.push_back({true, x});\r\n      v.push_back(x);\r\
    \n    } else if (s[2] == 't') {\r\n      q.push_back({false, 0});\r\n    } else\
    \ {\r\n      break;\r\n    }\r\n  }\r\n\r\n  std::sort(v.begin(), v.end());\r\n\
    \  v.erase(std::unique(v.begin(), v.end()), v.end());\r\n  std::vector<usize>\
    \ count(v.size(), 0);\r\n\r\n  w_ary_tree_set<max_q> wats;\r\n  for (const auto\
    \ &e : q) {\r\n    if (e.t) {\r\n      const usize i = std::lower_bound(v.begin(),\
    \ v.end(), e.key) - v.begin();\r\n      if (count[i] == 0) {\r\n        wats.insert(i);\r\
    \n      }\r\n      ++count[i];\r\n    } else {\r\n      const usize i = wats.max();\r\
    \n      std::cout << v[i] << \"\\n\";\r\n      --count[i];\r\n      if (count[i]\
    \ == 0) {\r\n        wats.erase(i);\r\n      }\r\n    }\r\n  }\r\n\r\n  return\
    \ 0;\r\n}\r\n"
  dependsOn:
  - data_structure/w_ary_tree_set.cpp
  - other/ceildiv.cpp
  - other/int_alias.cpp
  - other/fast_ios.cpp
  isVerificationFile: true
  path: test/w_ary_tree_set.test.cpp
  requiredBy: []
  timestamp: '2020-09-11 14:34:29+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/w_ary_tree_set.test.cpp
layout: document
redirect_from:
- /verify/test/w_ary_tree_set.test.cpp
- /verify/test/w_ary_tree_set.test.cpp.html
title: test/w_ary_tree_set.test.cpp
---
