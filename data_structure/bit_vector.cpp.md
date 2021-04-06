---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  - icon: ':heavy_check_mark:'
    path: other/popcount.cpp
    title: other/popcount.cpp
  - icon: ':heavy_check_mark:'
    path: other/select64.cpp
    title: other/select64.cpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: data_structure/wavelet_matrix.cpp
    title: Wavelet Matrix
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/wavelet_matrix.quantile.test.cpp
    title: test/wavelet_matrix.quantile.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/wavelet_matrix.rangefreq.test.cpp
    title: test/wavelet_matrix.rangefreq.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/wavelet_matrix.select.test.cpp
    title: test/wavelet_matrix.select.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Bit Vector
    links: []
  bundledCode: "#line 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
    \nusing i32 = std::int32_t;\nusing i64 = std::int64_t;\nusing u32 = std::uint32_t;\n\
    using u64 = std::uint64_t;\nusing isize = std::ptrdiff_t;\nusing usize = std::size_t;\n\
    #line 2 \"other/popcount.cpp\"\n\n#line 4 \"other/popcount.cpp\"\n\nusize popcount(u64\
    \ x) {\n#ifdef __GNUC__\n  return __builtin_popcountll(x);\n#else\n  x -= x >>\
    \ 1 & 0x5555555555555555;\n  x = (x & 0x3333333333333333) + (x >> 2 & 0x3333333333333333);\n\
    \  x = x + (x >> 4) & 0x0F0F0F0F0F0F0F0F;\n  return x * 0x0101010101010101 >>\
    \ 56 & 0x7f;\n#endif\n}\n#line 2 \"other/select64.cpp\"\n\n#line 5 \"other/select64.cpp\"\
    \n\nusize select64(const u64 x0, usize k) {\n  const u64 x1 = (x0 & 0x5555555555555555)\
    \ + (x0 >> 1 & 0x5555555555555555);\n  const u64 x2 = (x1 & 0x3333333333333333)\
    \ + (x1 >> 2 & 0x3333333333333333);\n  const u64 x3 = (x2 & 0x0F0F0F0F0F0F0F0F)\
    \ + (x2 >> 4 & 0x0F0F0F0F0F0F0F0F);\n  const u64 x4 = (x3 & 0x00FF00FF00FF00FF)\
    \ + (x3 >> 8 & 0x00FF00FF00FF00FF);\n  const u64 x5 = (x4 & 0x0000FFFF0000FFFF)\
    \ + (x4 >> 16 & 0x0000FFFF0000FFFF);\n  usize ret = 0;\n  usize t;\n  t = x5 >>\
    \ ret & 0xFFFFFFFF;\n  if (t <= k) {\n    k -= t;\n    ret += 32;\n  }\n  t =\
    \ x4 >> ret & 0xFFFF;\n  if (t <= k) {\n    k -= t;\n    ret += 16;\n  }\n  t\
    \ = x3 >> ret & 0xFF;\n  if (t <= k) {\n    k -= t;\n    ret += 8;\n  }\n  t =\
    \ x2 >> ret & 0xF;\n  if (t <= k) {\n    k -= t;\n    ret += 4;\n  }\n  t = x1\
    \ >> ret & 0x3;\n  if (t <= k) {\n    k -= t;\n    ret += 2;\n  }\n  t = x0 >>\
    \ ret & 0x1;\n  if (t <= k) {\n    k -= t;\n    ret += 1;\n  }\n  return ret;\n\
    }\n#line 4 \"data_structure/bit_vector.cpp\"\n\n#line 6 \"data_structure/bit_vector.cpp\"\
    \n#include <limits>\n#include <vector>\n\nclass bit_vector {\n  static constexpr\
    \ usize wordsize = std::numeric_limits<usize>::digits;\n\n  class node_type {\n\
    \  public:\n    usize bit;\n    usize sum;\n\n    node_type() : bit(0), sum(0)\
    \ {}\n  };\n\n  std::vector<node_type> v;\n\npublic:\n  bit_vector() = default;\n\
    \  explicit bit_vector(const std::vector<bool> a) : v(a.size() / wordsize + 1)\
    \ {\n    {\n      const usize s = a.size();\n      for (usize i = 0; i != s; i\
    \ += 1)\n        v[i / wordsize].bit |= static_cast<usize>(a[i] ? 1 : 0) << i\
    \ % wordsize;\n    }\n    {\n      const usize s = v.size();\n      for (usize\
    \ i = 1; i != s; i += 1)\n        v[i].sum = v[i - 1].sum + popcount(v[i - 1].bit);\n\
    \    }\n  }\n\n  usize rank0(const usize index) const { return index - rank1(index);\
    \ }\n  usize rank1(const usize index) const {\n    return v[index / wordsize].sum\
    \ +\n           popcount(v[index / wordsize].bit &\n                    ~(~static_cast<usize>(0)\
    \ << index % wordsize));\n  }\n  usize select0(const usize k) const {\n    usize\
    \ l = 0;\n    usize r = v.size();\n    while (l != r) {\n      const usize m =\
    \ (l + r) / 2;\n      if (m * wordsize - v[m].sum <= k)\n        l = m + 1;\n\
    \      else\n        r = m;\n    }\n    const usize i = l - 1;\n    return i *\
    \ wordsize + select64(~v[i].bit, k - (i * wordsize - v[i].sum));\n  }\n  usize\
    \ select1(const usize k) const {\n    usize l = 0;\n    usize r = v.size();\n\
    \    while (l != r) {\n      const usize m = (l + r) / 2;\n      if (v[m].sum\
    \ <= k)\n        l = m + 1;\n      else\n        r = m;\n    }\n    const usize\
    \ i = l - 1;\n    return i * wordsize + select64(v[i].bit, k - v[i].sum);\n  }\n\
    };\n\n/**\n * @brief Bit Vector\n */\n"
  code: "#include \"other/int_alias.cpp\"\n#include \"other/popcount.cpp\"\n#include\
    \ \"other/select64.cpp\"\n\n#include <cstddef>\n#include <limits>\n#include <vector>\n\
    \nclass bit_vector {\n  static constexpr usize wordsize = std::numeric_limits<usize>::digits;\n\
    \n  class node_type {\n  public:\n    usize bit;\n    usize sum;\n\n    node_type()\
    \ : bit(0), sum(0) {}\n  };\n\n  std::vector<node_type> v;\n\npublic:\n  bit_vector()\
    \ = default;\n  explicit bit_vector(const std::vector<bool> a) : v(a.size() /\
    \ wordsize + 1) {\n    {\n      const usize s = a.size();\n      for (usize i\
    \ = 0; i != s; i += 1)\n        v[i / wordsize].bit |= static_cast<usize>(a[i]\
    \ ? 1 : 0) << i % wordsize;\n    }\n    {\n      const usize s = v.size();\n \
    \     for (usize i = 1; i != s; i += 1)\n        v[i].sum = v[i - 1].sum + popcount(v[i\
    \ - 1].bit);\n    }\n  }\n\n  usize rank0(const usize index) const { return index\
    \ - rank1(index); }\n  usize rank1(const usize index) const {\n    return v[index\
    \ / wordsize].sum +\n           popcount(v[index / wordsize].bit &\n         \
    \           ~(~static_cast<usize>(0) << index % wordsize));\n  }\n  usize select0(const\
    \ usize k) const {\n    usize l = 0;\n    usize r = v.size();\n    while (l !=\
    \ r) {\n      const usize m = (l + r) / 2;\n      if (m * wordsize - v[m].sum\
    \ <= k)\n        l = m + 1;\n      else\n        r = m;\n    }\n    const usize\
    \ i = l - 1;\n    return i * wordsize + select64(~v[i].bit, k - (i * wordsize\
    \ - v[i].sum));\n  }\n  usize select1(const usize k) const {\n    usize l = 0;\n\
    \    usize r = v.size();\n    while (l != r) {\n      const usize m = (l + r)\
    \ / 2;\n      if (v[m].sum <= k)\n        l = m + 1;\n      else\n        r =\
    \ m;\n    }\n    const usize i = l - 1;\n    return i * wordsize + select64(v[i].bit,\
    \ k - v[i].sum);\n  }\n};\n\n/**\n * @brief Bit Vector\n */\n"
  dependsOn:
  - other/int_alias.cpp
  - other/popcount.cpp
  - other/select64.cpp
  isVerificationFile: false
  path: data_structure/bit_vector.cpp
  requiredBy:
  - data_structure/wavelet_matrix.cpp
  timestamp: '2020-03-11 22:58:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/wavelet_matrix.select.test.cpp
  - test/wavelet_matrix.quantile.test.cpp
  - test/wavelet_matrix.rangefreq.test.cpp
documentation_of: data_structure/bit_vector.cpp
layout: document
redirect_from:
- /library/data_structure/bit_vector.cpp
- /library/data_structure/bit_vector.cpp.html
title: Bit Vector
---
