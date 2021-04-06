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
    path: test/lazy_segment_tree.test.cpp
    title: test/lazy_segment_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Lazy Segment Tree
    links:
    - https://scrapbox.io/data-structures/Lazy_Segment_Tree
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
    \ }\n#line 4 \"data_structure/lazy_segment_tree.cpp\"\n\n#include <cassert>\n\
    #line 7 \"data_structure/lazy_segment_tree.cpp\"\n#include <vector>\n\ntemplate\
    \ <class A> class lazy_segment_tree {\n  using V = typename A::value_structure;\n\
    \  using T = typename V::value_type;\n  using O = typename A::operator_structure;\n\
    \  using E = typename O::value_type;\n\n  class node_type {\n  public:\n    T\
    \ value;\n    E lazy;\n\n    node_type(const T value, const E lazy) : value(value),\
    \ lazy(lazy) {}\n  };\n\n  static T get(const node_type &x) { return A::operation(x.value,\
    \ x.lazy); }\n  static void add(E &x, const E y) { x = O::operation(x, y); }\n\
    \n  std::vector<node_type> tree;\n\n  void propagate(const usize index) {\n  \
    \  add(tree[index * 2].lazy, tree[index].lazy);\n    add(tree[index * 2 + 1].lazy,\
    \ tree[index].lazy);\n    tree[index].lazy = O::identity;\n  }\n\n  void propagate_bound(const\
    \ usize index) {\n    if (index == 0)\n      return;\n    const usize crz = countr_zero(index);\n\
    \    for (usize h = bit_width(index) - 1; h != crz; h -= 1)\n      propagate(index\
    \ >> h);\n  }\n\n  void recalc(const usize index) {\n    tree[index].value =\n\
    \        V::operation(get(tree[index * 2]), get(tree[index * 2 + 1]));\n  }\n\n\
    \  void recalc_bound(usize index) {\n    if (index == 0)\n      return;\n    index\
    \ >>= countr_zero(index);\n    while (index != 1) {\n      index /= 2;\n     \
    \ recalc(index);\n    }\n  }\n\npublic:\n  lazy_segment_tree() = default;\n\n\
    \  explicit lazy_segment_tree(const usize n)\n      : tree(n * 2, node_type(V::identity,\
    \ O::identity)) {}\n\n  usize size() const { return tree.size() / 2; }\n\n  T\
    \ fold(usize first, usize last) {\n    assert(first <= last);\n    assert(last\
    \ <= size());\n    first += size();\n    last += size();\n    propagate_bound(first);\n\
    \    recalc_bound(first);\n    propagate_bound(last);\n    recalc_bound(last);\n\
    \    T fold_l = V::identity;\n    T fold_r = V::identity;\n    while (first !=\
    \ last) {\n      if (first % 2 != 0) {\n        fold_l = V::operation(fold_l,\
    \ get(tree[first]));\n        first += 1;\n      }\n      first /= 2;\n      if\
    \ (last % 2 != 0) {\n        last -= 1;\n        fold_r = V::operation(get(tree[last]),\
    \ fold_r);\n      }\n      last /= 2;\n    }\n    return V::operation(fold_l,\
    \ fold_r);\n  }\n\n  void update_range(usize first, usize last, const E x) {\n\
    \    assert(first <= last);\n    assert(last <= size());\n    first += size();\n\
    \    last += size();\n    propagate_bound(first);\n    propagate_bound(last);\n\
    \    const usize first_c = first;\n    const usize last_c = last;\n    while (first\
    \ != last) {\n      if (first % 2 != 0) {\n        add(tree[first].lazy, x);\n\
    \        first += 1;\n      }\n      first /= 2;\n      if (last % 2 != 0) {\n\
    \        last -= 1;\n        add(tree[last].lazy, x);\n      }\n      last /=\
    \ 2;\n    }\n    recalc_bound(first_c);\n    recalc_bound(last_c);\n  }\n\n  void\
    \ update_point(usize index, const T x) {\n    assert(index < size());\n    index\
    \ += size();\n    for (usize h = bit_width(index) - 1; h != 0; h -= 1)\n     \
    \ propagate(index >> h);\n    tree[index] = node_type(x, O::identity);\n    while\
    \ (index != 1) {\n      index /= 2;\n      recalc(index);\n    }\n  }\n};\n\n\
    /**\n * @brief Lazy Segment Tree\n * @see https://scrapbox.io/data-structures/Lazy_Segment_Tree\n\
    \ */\n"
  code: "#include \"other/bit_width.cpp\"\n#include \"other/countr_zero.cpp\"\n#include\
    \ \"other/int_alias.cpp\"\n\n#include <cassert>\n#include <cstddef>\n#include\
    \ <vector>\n\ntemplate <class A> class lazy_segment_tree {\n  using V = typename\
    \ A::value_structure;\n  using T = typename V::value_type;\n  using O = typename\
    \ A::operator_structure;\n  using E = typename O::value_type;\n\n  class node_type\
    \ {\n  public:\n    T value;\n    E lazy;\n\n    node_type(const T value, const\
    \ E lazy) : value(value), lazy(lazy) {}\n  };\n\n  static T get(const node_type\
    \ &x) { return A::operation(x.value, x.lazy); }\n  static void add(E &x, const\
    \ E y) { x = O::operation(x, y); }\n\n  std::vector<node_type> tree;\n\n  void\
    \ propagate(const usize index) {\n    add(tree[index * 2].lazy, tree[index].lazy);\n\
    \    add(tree[index * 2 + 1].lazy, tree[index].lazy);\n    tree[index].lazy =\
    \ O::identity;\n  }\n\n  void propagate_bound(const usize index) {\n    if (index\
    \ == 0)\n      return;\n    const usize crz = countr_zero(index);\n    for (usize\
    \ h = bit_width(index) - 1; h != crz; h -= 1)\n      propagate(index >> h);\n\
    \  }\n\n  void recalc(const usize index) {\n    tree[index].value =\n        V::operation(get(tree[index\
    \ * 2]), get(tree[index * 2 + 1]));\n  }\n\n  void recalc_bound(usize index) {\n\
    \    if (index == 0)\n      return;\n    index >>= countr_zero(index);\n    while\
    \ (index != 1) {\n      index /= 2;\n      recalc(index);\n    }\n  }\n\npublic:\n\
    \  lazy_segment_tree() = default;\n\n  explicit lazy_segment_tree(const usize\
    \ n)\n      : tree(n * 2, node_type(V::identity, O::identity)) {}\n\n  usize size()\
    \ const { return tree.size() / 2; }\n\n  T fold(usize first, usize last) {\n \
    \   assert(first <= last);\n    assert(last <= size());\n    first += size();\n\
    \    last += size();\n    propagate_bound(first);\n    recalc_bound(first);\n\
    \    propagate_bound(last);\n    recalc_bound(last);\n    T fold_l = V::identity;\n\
    \    T fold_r = V::identity;\n    while (first != last) {\n      if (first % 2\
    \ != 0) {\n        fold_l = V::operation(fold_l, get(tree[first]));\n        first\
    \ += 1;\n      }\n      first /= 2;\n      if (last % 2 != 0) {\n        last\
    \ -= 1;\n        fold_r = V::operation(get(tree[last]), fold_r);\n      }\n  \
    \    last /= 2;\n    }\n    return V::operation(fold_l, fold_r);\n  }\n\n  void\
    \ update_range(usize first, usize last, const E x) {\n    assert(first <= last);\n\
    \    assert(last <= size());\n    first += size();\n    last += size();\n    propagate_bound(first);\n\
    \    propagate_bound(last);\n    const usize first_c = first;\n    const usize\
    \ last_c = last;\n    while (first != last) {\n      if (first % 2 != 0) {\n \
    \       add(tree[first].lazy, x);\n        first += 1;\n      }\n      first /=\
    \ 2;\n      if (last % 2 != 0) {\n        last -= 1;\n        add(tree[last].lazy,\
    \ x);\n      }\n      last /= 2;\n    }\n    recalc_bound(first_c);\n    recalc_bound(last_c);\n\
    \  }\n\n  void update_point(usize index, const T x) {\n    assert(index < size());\n\
    \    index += size();\n    for (usize h = bit_width(index) - 1; h != 0; h -= 1)\n\
    \      propagate(index >> h);\n    tree[index] = node_type(x, O::identity);\n\
    \    while (index != 1) {\n      index /= 2;\n      recalc(index);\n    }\n  }\n\
    };\n\n/**\n * @brief Lazy Segment Tree\n * @see https://scrapbox.io/data-structures/Lazy_Segment_Tree\n\
    \ */\n"
  dependsOn:
  - other/bit_width.cpp
  - other/countl_zero.cpp
  - other/countr_zero.cpp
  - other/int_alias.cpp
  isVerificationFile: false
  path: data_structure/lazy_segment_tree.cpp
  requiredBy: []
  timestamp: '2020-03-11 22:42:07+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/lazy_segment_tree.test.cpp
documentation_of: data_structure/lazy_segment_tree.cpp
layout: document
redirect_from:
- /library/data_structure/lazy_segment_tree.cpp
- /library/data_structure/lazy_segment_tree.cpp.html
title: Lazy Segment Tree
---
