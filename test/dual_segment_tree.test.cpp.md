---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/dual_segment_tree.cpp
    title: Dual Segment Tree
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
  - icon: ':heavy_check_mark:'
    path: other/right_zero_semigroup.cpp
    title: other/right_zero_semigroup.cpp
  - icon: ':heavy_check_mark:'
    path: other/semigroup_to_monoid.cpp
    title: other/semigroup_to_monoid.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D&lang=ja
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D&lang=ja
  bundledCode: "#line 1 \"test/dual_segment_tree.test.cpp\"\n#define PROBLEM     \
    \                                                           \\\n  \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D&lang=ja\"\
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
    \ }\n#line 4 \"data_structure/dual_segment_tree.cpp\"\n\n#include <cassert>\n\
    #line 7 \"data_structure/dual_segment_tree.cpp\"\n#include <vector>\n\ntemplate\
    \ <class M> class dual_segment_tree {\n  using T = typename M::value_type;\n\n\
    public:\n  using value_type = T;\n\nprivate:\n  static void add(T &x, const T\
    \ y) { x = M::operation(x, y); }\n\n  std::vector<T> tree;\n\n  void push(const\
    \ usize index) {\n    add(tree[index * 2], tree[index]);\n    add(tree[index *\
    \ 2 + 1], tree[index]);\n    tree[index] = M::identity;\n  }\n  void propagate(const\
    \ usize index) {\n    if (index == 0)\n      return;\n    const usize crz = countr_zero(index);\n\
    \    for (usize h = bit_width(index) - 1; h != crz; h -= 1)\n      push(index\
    \ >> h);\n  }\n\npublic:\n  dual_segment_tree() = default;\n  explicit dual_segment_tree(const\
    \ usize n) : tree(n * 2, M::identity) {}\n\n  usize size() const noexcept { return\
    \ tree.size() / 2; }\n\n  T fold(usize index) const {\n    assert(index < size());\n\
    \    index += size();\n    T ret = tree[index];\n    while (index != 1) {\n  \
    \    index /= 2;\n      add(ret, tree[index]);\n    }\n    return ret;\n  }\n\n\
    \  void update(usize first, usize last, const T x) {\n    assert(first <= last);\n\
    \    assert(last <= size());\n    first += size();\n    last += size();\n    propagate(first);\n\
    \    propagate(last);\n    while (first != last) {\n      if (first % 2 != 0)\
    \ {\n        add(tree[first], x);\n        first += 1;\n      }\n      first /=\
    \ 2;\n      if (last % 2 != 0) {\n        last -= 1;\n        add(tree[last],\
    \ x);\n      }\n      last /= 2;\n    }\n  }\n};\n\n/**\n * @brief Dual Segment\
    \ Tree\n * @see https://kimiyuki.net/blog/2019/02/21/dual-segment-tree/\n */\n\
    #line 1 \"other/right_zero_semigroup.cpp\"\ntemplate <class T> class right_zero_semigroup\
    \ {\npublic:\n  using value_type = T;\n  static constexpr T operation(const T\
    \ &, const T &r) noexcept { return r; }\n};\n#line 1 \"other/semigroup_to_monoid.cpp\"\
    \n#include <optional>\n#include <utility>\n\ntemplate <class S> class semigroup_to_monoid\
    \ {\n  using T = std::optional<typename S::value_type>;\n\npublic:\n  using value_type\
    \ = T;\n  static constexpr T operation(const T &l, const T &r) noexcept {\n  \
    \  if (!l)\n      return r;\n    if (!r)\n      return l;\n    return T(std::in_place,\
    \ S::operation(*l, *r));\n  }\n  static constexpr T identity{std::nullopt};\n\
    };\n#line 7 \"test/dual_segment_tree.test.cpp\"\n\n#include <iostream>\n\nint\
    \ main() {\n#line 1 \"other/fast_ios.cpp\"\nstd::ios::sync_with_stdio(false);\n\
    std::cin.tie(nullptr);\n#line 12 \"test/dual_segment_tree.test.cpp\"\n\n  int\
    \ n, q;\n  std::cin >> n >> q;\n  dual_segment_tree<semigroup_to_monoid<right_zero_semigroup<int>>>\
    \ dst(n);\n  dst.update(0, n, 2147483647);\n  for (int i = 0; i != q; i += 1)\
    \ {\n    int c;\n    std::cin >> c;\n    switch (c) {\n    case 0: {\n      int\
    \ s, t, x;\n      std::cin >> s >> t >> x;\n      dst.update(s, t + 1, x);\n \
    \   } break;\n    case 1: {\n      int i;\n      std::cin >> i;\n      std::cout\
    \ << dst.fold(i).value() << \"\\n\";\n    } break;\n    }\n  }\n}\n"
  code: "#define PROBLEM                                                         \
    \       \\\n  \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D&lang=ja\"\
    \n\n#include \"data_structure/dual_segment_tree.cpp\"\n#include \"other/right_zero_semigroup.cpp\"\
    \n#include \"other/semigroup_to_monoid.cpp\"\n\n#include <iostream>\n\nint main()\
    \ {\n#include \"other/fast_ios.cpp\"\n\n  int n, q;\n  std::cin >> n >> q;\n \
    \ dual_segment_tree<semigroup_to_monoid<right_zero_semigroup<int>>> dst(n);\n\
    \  dst.update(0, n, 2147483647);\n  for (int i = 0; i != q; i += 1) {\n    int\
    \ c;\n    std::cin >> c;\n    switch (c) {\n    case 0: {\n      int s, t, x;\n\
    \      std::cin >> s >> t >> x;\n      dst.update(s, t + 1, x);\n    } break;\n\
    \    case 1: {\n      int i;\n      std::cin >> i;\n      std::cout << dst.fold(i).value()\
    \ << \"\\n\";\n    } break;\n    }\n  }\n}"
  dependsOn:
  - data_structure/dual_segment_tree.cpp
  - other/bit_width.cpp
  - other/countl_zero.cpp
  - other/countr_zero.cpp
  - other/int_alias.cpp
  - other/right_zero_semigroup.cpp
  - other/semigroup_to_monoid.cpp
  - other/fast_ios.cpp
  isVerificationFile: true
  path: test/dual_segment_tree.test.cpp
  requiredBy: []
  timestamp: '2020-03-11 22:42:07+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/dual_segment_tree.test.cpp
layout: document
redirect_from:
- /verify/test/dual_segment_tree.test.cpp
- /verify/test/dual_segment_tree.test.cpp.html
title: test/dual_segment_tree.test.cpp
---
