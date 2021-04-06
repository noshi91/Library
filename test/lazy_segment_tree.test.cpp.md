---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/lazy_segment_tree.cpp
    title: Lazy Segment Tree
  - icon: ':heavy_check_mark:'
    path: other/affine.cpp
    title: other/affine.cpp
  - icon: ':heavy_check_mark:'
    path: other/bit_width.cpp
    title: other/bit_width.cpp
  - icon: ':heavy_check_mark:'
    path: other/cartesian_product_monoid.cpp
    title: other/cartesian_product_monoid.cpp
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
    path: other/modint.cpp
    title: other/modint.cpp
  - icon: ':heavy_check_mark:'
    path: other/plus_monoid.cpp
    title: other/plus_monoid.cpp
  - icon: ':heavy_check_mark:'
    path: other/sum_affine_action.cpp
    title: other/sum_affine_action.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_affine_range_sum
    links:
    - https://judge.yosupo.jp/problem/range_affine_range_sum
  bundledCode: "#line 1 \"test/lazy_segment_tree.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\
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
    \ */\n#line 2 \"other/modint.cpp\"\n\ntemplate <std::uint_fast64_t Modulus> class\
    \ modint {\n  using u64 = std::uint_fast64_t;\n\npublic:\n  using value_type =\
    \ u64;\n\n  static constexpr u64 mod = Modulus;\n\nprivate:\n  static_assert(mod\
    \ < static_cast<u64>(1) << 32,\n                \"Modulus must be less than 2**32\"\
    );\n\n  u64 v;\n\n  constexpr modint &negate() noexcept {\n    if (v != 0)\n \
    \     v = mod - v;\n    return *this;\n  }\n\npublic:\n  constexpr modint(const\
    \ u64 x = 0) noexcept : v(x % mod) {}\n  constexpr u64 &value() noexcept { return\
    \ v; }\n  constexpr const u64 &value() const noexcept { return v; }\n  constexpr\
    \ modint operator+() const noexcept { return modint(*this); }\n  constexpr modint\
    \ operator-() const noexcept { return modint(*this).negate(); }\n  constexpr modint\
    \ operator+(const modint rhs) const noexcept {\n    return modint(*this) += rhs;\n\
    \  }\n  constexpr modint operator-(const modint rhs) const noexcept {\n    return\
    \ modint(*this) -= rhs;\n  }\n  constexpr modint operator*(const modint rhs) const\
    \ noexcept {\n    return modint(*this) *= rhs;\n  }\n  constexpr modint operator/(const\
    \ modint rhs) const noexcept {\n    return modint(*this) /= rhs;\n  }\n  constexpr\
    \ modint &operator+=(const modint rhs) noexcept {\n    v += rhs.v;\n    if (v\
    \ >= mod)\n      v -= mod;\n    return *this;\n  }\n  constexpr modint &operator-=(const\
    \ modint rhs) noexcept {\n    if (v < rhs.v)\n      v += mod;\n    v -= rhs.v;\n\
    \    return *this;\n  }\n  constexpr modint &operator*=(const modint rhs) noexcept\
    \ {\n    v = v * rhs.v % mod;\n    return *this;\n  }\n  constexpr modint &operator/=(modint\
    \ rhs) noexcept {\n    u64 exp = mod - 2;\n    while (exp != 0) {\n      if (exp\
    \ % 2 != 0)\n        *this *= rhs;\n      rhs *= rhs;\n      exp /= 2;\n    }\n\
    \    return *this;\n  }\n};\ntemplate <std::uint_fast64_t Modulus>\nconstexpr\
    \ typename modint<Modulus>::u64 modint<Modulus>::mod;\n#line 1 \"other/affine.cpp\"\
    \ntemplate <class T> class affine {\npublic:\n  T a;\n  T b;\n\n  constexpr affine(const\
    \ T &a = 1, const T &b = 0) noexcept : a(a), b(b) {}\n\n  constexpr T evaluate(const\
    \ T &x) const noexcept { return x * a + b; }\n  friend constexpr affine operator+(const\
    \ affine &l, const affine &r) noexcept {\n    return affine(l.a + r.a, l.b + r.b);\n\
    \  }\n  constexpr affine composite(const affine &r) const noexcept {\n    return\
    \ affine(a * r.a, b * r.a + r.b);\n  }\n};\n\ntemplate <class T> class affine_composite_monoid\
    \ {\npublic:\n  using value_type = affine<T>;\n  static constexpr value_type operation(const\
    \ value_type &l,\n                                        const value_type &r)\
    \ noexcept {\n    return l.composite(r);\n  }\n  static constexpr value_type identity{};\n\
    };\n#line 1 \"other/cartesian_product_monoid.cpp\"\n#include <utility>\n\ntemplate\
    \ <class M, class N> class cartesian_product_monoid {\n  using T = std::pair<typename\
    \ M::value_type, typename N::value_type>;\n\npublic:\n  using value_type = T;\n\
    \  static constexpr T operation(const T &l, const T &r) noexcept {\n    return\
    \ T(M::operation(l.first, r.first), N::operation(l.second, r.second));\n  }\n\
    \  static constexpr T identity{M::identity, N::identity};\n};\n#line 1 \"other/plus_monoid.cpp\"\
    \ntemplate <class T> class plus_monoid {\npublic:\n  using value_type = T;\n \
    \ static T operation(const T l, const T r) { return l + r; }\n  static constexpr\
    \ T identity = 0;\n};\n#line 4 \"other/sum_affine_action.cpp\"\n\ntemplate <class\
    \ T> class sum_affine_action {\npublic:\n  using value_structure =\n      cartesian_product_monoid<plus_monoid<T>,\
    \ plus_monoid<T>>;\n  using operator_structure = affine_composite_monoid<T>;\n\
    \nprivate:\n  using U = typename value_structure::value_type;\n  using E = typename\
    \ operator_structure::value_type;\n\npublic:\n  static constexpr U operation(const\
    \ U &l, const E &r) {\n    return U(l.first * r.a + l.second * r.b, l.second);\n\
    \  }\n};\n#line 6 \"test/lazy_segment_tree.test.cpp\"\n\n#include <iostream>\n\
    \nint main() {\n#line 1 \"other/fast_ios.cpp\"\nstd::ios::sync_with_stdio(false);\n\
    std::cin.tie(nullptr);\n#line 11 \"test/lazy_segment_tree.test.cpp\"\n\n  using\
    \ mint = modint<998244353>;\n\n  int n, q;\n  std::cin >> n >> q;\n  lazy_segment_tree<sum_affine_action<mint>>\
    \ lst(n);\n  for (int i = 0; i != n; i += 1) {\n    int a;\n    std::cin >> a;\n\
    \    lst.update_point(i, {a, 1});\n  }\n  for (int i = 0; i != q; i += 1) {\n\
    \    int t;\n    std::cin >> t;\n    switch (t) {\n    case 0: {\n      int l,\
    \ r, b, c;\n      std::cin >> l >> r >> b >> c;\n      lst.update_range(l, r,\
    \ {b, c});\n    } break;\n    case 1: {\n      int l, r;\n      std::cin >> l\
    \ >> r;\n      std::cout << lst.fold(l, r).first.value() << \"\\n\";\n    } break;\n\
    \    }\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\
    \n\n#include \"data_structure/lazy_segment_tree.cpp\"\n#include \"other/modint.cpp\"\
    \n#include \"other/sum_affine_action.cpp\"\n\n#include <iostream>\n\nint main()\
    \ {\n#include \"other/fast_ios.cpp\"\n\n  using mint = modint<998244353>;\n\n\
    \  int n, q;\n  std::cin >> n >> q;\n  lazy_segment_tree<sum_affine_action<mint>>\
    \ lst(n);\n  for (int i = 0; i != n; i += 1) {\n    int a;\n    std::cin >> a;\n\
    \    lst.update_point(i, {a, 1});\n  }\n  for (int i = 0; i != q; i += 1) {\n\
    \    int t;\n    std::cin >> t;\n    switch (t) {\n    case 0: {\n      int l,\
    \ r, b, c;\n      std::cin >> l >> r >> b >> c;\n      lst.update_range(l, r,\
    \ {b, c});\n    } break;\n    case 1: {\n      int l, r;\n      std::cin >> l\
    \ >> r;\n      std::cout << lst.fold(l, r).first.value() << \"\\n\";\n    } break;\n\
    \    }\n  }\n}"
  dependsOn:
  - data_structure/lazy_segment_tree.cpp
  - other/bit_width.cpp
  - other/countl_zero.cpp
  - other/countr_zero.cpp
  - other/int_alias.cpp
  - other/modint.cpp
  - other/sum_affine_action.cpp
  - other/affine.cpp
  - other/cartesian_product_monoid.cpp
  - other/plus_monoid.cpp
  - other/fast_ios.cpp
  isVerificationFile: true
  path: test/lazy_segment_tree.test.cpp
  requiredBy: []
  timestamp: '2020-03-11 22:42:07+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/lazy_segment_tree.test.cpp
layout: document
redirect_from:
- /verify/test/lazy_segment_tree.test.cpp
- /verify/test/lazy_segment_tree.test.cpp.html
title: test/lazy_segment_tree.test.cpp
---
