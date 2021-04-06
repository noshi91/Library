---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/bit_vector.cpp
    title: Bit Vector
  - icon: ':heavy_check_mark:'
    path: data_structure/wavelet_matrix.cpp
    title: Wavelet Matrix
  - icon: ':heavy_check_mark:'
    path: other/fast_ios.cpp
    title: other/fast_ios.cpp
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  - icon: ':heavy_check_mark:'
    path: other/popcount.cpp
    title: other/popcount.cpp
  - icon: ':heavy_check_mark:'
    path: other/select64.cpp
    title: other/select64.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_kth_smallest
    links:
    - https://judge.yosupo.jp/problem/range_kth_smallest
  bundledCode: "#line 1 \"test/wavelet_matrix.quantile.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n#line 2 \"other/int_alias.cpp\"\
    \n\n#include <cstddef>\n#include <cstdint>\n\nusing i32 = std::int32_t;\nusing\
    \ i64 = std::int64_t;\nusing u32 = std::uint32_t;\nusing u64 = std::uint64_t;\n\
    using isize = std::ptrdiff_t;\nusing usize = std::size_t;\n#line 2 \"other/popcount.cpp\"\
    \n\n#line 4 \"other/popcount.cpp\"\n\nusize popcount(u64 x) {\n#ifdef __GNUC__\n\
    \  return __builtin_popcountll(x);\n#else\n  x -= x >> 1 & 0x5555555555555555;\n\
    \  x = (x & 0x3333333333333333) + (x >> 2 & 0x3333333333333333);\n  x = x + (x\
    \ >> 4) & 0x0F0F0F0F0F0F0F0F;\n  return x * 0x0101010101010101 >> 56 & 0x7f;\n\
    #endif\n}\n#line 2 \"other/select64.cpp\"\n\n#line 5 \"other/select64.cpp\"\n\n\
    usize select64(const u64 x0, usize k) {\n  const u64 x1 = (x0 & 0x5555555555555555)\
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
    };\n\n/**\n * @brief Bit Vector\n */\n#line 3 \"data_structure/wavelet_matrix.cpp\"\
    \n\n#include <algorithm>\n#include <cassert>\n#line 8 \"data_structure/wavelet_matrix.cpp\"\
    \n\ntemplate <class Key> class wavelet_matrix {\npublic:\n  using key_type = Key;\n\
    \  using value_type = Key;\n\nprivate:\n  static bool test(const key_type x, const\
    \ usize k) {\n    return (x & static_cast<key_type>(1) << k) != 0;\n  }\n  static\
    \ void set(key_type &x, const usize k) {\n    x |= static_cast<key_type>(1) <<\
    \ k;\n  }\n\n  usize size_;\n  std::vector<bit_vector> mat;\n\n  usize less(usize\
    \ first, usize last, const key_type key) const {\n    usize ret = 0;\n    for\
    \ (usize p = mat.size(); p != 0;) {\n      p -= 1;\n      const bit_vector &v\
    \ = mat[p];\n      if (!test(key, p)) {\n        first = v.rank0(first);\n   \
    \     last = v.rank0(last);\n      } else {\n        ret += v.rank0(last) - v.rank0(first);\n\
    \        const usize b = v.rank0(size());\n        first = b + v.rank1(first);\n\
    \        last = b + v.rank1(last);\n      }\n    }\n    return ret;\n  }\n\npublic:\n\
    \  wavelet_matrix() = default;\n  explicit wavelet_matrix(const usize bit_length,\
    \ std::vector<key_type> a)\n      : size_(a.size()), mat(bit_length, bit_vector())\
    \ {\n    const usize s = size();\n    for (usize p = bit_length; p != 0;) {\n\
    \      p -= 1;\n      {\n        std::vector<bool> t(s);\n        for (usize i\
    \ = 0; i != s; i += 1)\n          t[i] = test(a[i], p);\n        mat[p] = bit_vector(t);\n\
    \      }\n      {\n        std::vector<key_type> v0, v1;\n        for (const usize\
    \ e : a)\n          (test(e, p) ? v1 : v0).push_back(e);\n        const auto itr\
    \ = std::copy(v0.cbegin(), v0.cend(), a.begin());\n        std::copy(v1.cbegin(),\
    \ v1.cend(), itr);\n      }\n    }\n  }\n\n  usize size() const { return size_;\
    \ }\n\n  usize rangefreq(const usize first, const usize last, const key_type lower,\n\
    \                  const key_type upper) const {\n    assert(first <= last);\n\
    \    assert(last <= size());\n    assert(lower <= upper);\n\n    return less(first,\
    \ last, upper) - less(first, last, lower);\n  }\n  key_type quantile(usize first,\
    \ usize last, usize k) const {\n    assert(first <= last);\n    assert(last <=\
    \ size());\n    assert(k < last - first);\n\n    key_type ret = 0;\n    for (usize\
    \ p = mat.size(); p != 0;) {\n      p -= 1;\n      const bit_vector &v = mat[p];\n\
    \      const usize z = v.rank0(last) - v.rank0(first);\n      if (k < z) {\n \
    \       first = v.rank0(first);\n        last = v.rank0(last);\n      } else {\n\
    \        set(ret, p);\n        k -= z;\n        const usize b = v.rank0(size());\n\
    \        first = b + v.rank1(first);\n        last = b + v.rank1(last);\n    \
    \  }\n    }\n    return ret;\n  }\n  usize select(const key_type key, const usize\
    \ k) const {\n    usize index = 0;\n    for (usize p = mat.size(); p != 0;) {\n\
    \      p -= 1;\n      const bit_vector &v = mat[p];\n      if (!test(key, p))\n\
    \        index = v.rank0(index);\n      else\n        index = v.rank0(size())\
    \ + v.rank1(index);\n    }\n    index += k;\n    for (usize p = 0; p != mat.size();\
    \ p += 1) {\n      const bit_vector &v = mat[p];\n      if (!test(key, p))\n \
    \       index = v.select0(index);\n      else\n        index = v.select1(index\
    \ - v.rank0(size()));\n    }\n    return index;\n  }\n};\n\n/**\n * @brief Wavelet\
    \ Matrix\n */\n#line 4 \"test/wavelet_matrix.quantile.test.cpp\"\n\n#include <iostream>\n\
    #line 7 \"test/wavelet_matrix.quantile.test.cpp\"\n\nint main() {\n#line 1 \"\
    other/fast_ios.cpp\"\nstd::ios::sync_with_stdio(false);\nstd::cin.tie(nullptr);\n\
    #line 10 \"test/wavelet_matrix.quantile.test.cpp\"\n\n  int n, q;\n  std::cin\
    \ >> n >> q;\n\n  const auto wm = [&] {\n    std::vector<int> a(n);\n    for (int\
    \ &e : a)\n      std::cin >> e;\n    return wavelet_matrix<int>(30, a);\n  }();\n\
    \n  for (int i = 0; i != q; i += 1) {\n    int l, r, k;\n    std::cin >> l >>\
    \ r >> k;\n    std::cout << wm.quantile(l, r, k) << \"\\n\";\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n\
    #include \"data_structure/wavelet_matrix.cpp\"\n\n#include <iostream>\n#include\
    \ <vector>\n\nint main() {\n#include \"other/fast_ios.cpp\"\n\n  int n, q;\n \
    \ std::cin >> n >> q;\n\n  const auto wm = [&] {\n    std::vector<int> a(n);\n\
    \    for (int &e : a)\n      std::cin >> e;\n    return wavelet_matrix<int>(30,\
    \ a);\n  }();\n\n  for (int i = 0; i != q; i += 1) {\n    int l, r, k;\n    std::cin\
    \ >> l >> r >> k;\n    std::cout << wm.quantile(l, r, k) << \"\\n\";\n  }\n}\n"
  dependsOn:
  - data_structure/wavelet_matrix.cpp
  - data_structure/bit_vector.cpp
  - other/int_alias.cpp
  - other/popcount.cpp
  - other/select64.cpp
  - other/fast_ios.cpp
  isVerificationFile: true
  path: test/wavelet_matrix.quantile.test.cpp
  requiredBy: []
  timestamp: '2020-03-11 22:58:19+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/wavelet_matrix.quantile.test.cpp
layout: document
redirect_from:
- /verify/test/wavelet_matrix.quantile.test.cpp
- /verify/test/wavelet_matrix.quantile.test.cpp.html
title: test/wavelet_matrix.quantile.test.cpp
---
