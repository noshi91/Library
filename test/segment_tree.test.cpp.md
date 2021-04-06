---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/segment_tree.cpp
    title: Segment Tree
  - icon: ':heavy_check_mark:'
    path: other/affine.cpp
    title: other/affine.cpp
  - icon: ':heavy_check_mark:'
    path: other/fast_ios.cpp
    title: other/fast_ios.cpp
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  - icon: ':heavy_check_mark:'
    path: other/modint.cpp
    title: other/modint.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_set_range_composite
    links:
    - https://judge.yosupo.jp/problem/point_set_range_composite
  bundledCode: "#line 1 \"test/segment_tree.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_composite\"\
    \n\n#line 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
    \nusing i32 = std::int32_t;\nusing i64 = std::int64_t;\nusing u32 = std::uint32_t;\n\
    using u64 = std::uint64_t;\nusing isize = std::ptrdiff_t;\nusing usize = std::size_t;\n\
    #line 2 \"data_structure/segment_tree.cpp\"\n\n#include <cassert>\n#line 5 \"\
    data_structure/segment_tree.cpp\"\n#include <vector>\n\ntemplate <class M> class\
    \ segment_tree {\n  using T = typename M::value_type;\n\npublic:\n  using value_type\
    \ = T;\n\nprivate:\n  std::vector<T> tree;\n\n  template <class F>\n  usize search_subtree(usize\
    \ index, const F f, T fold_l) const {\n    while (index < size()) {\n      const\
    \ T temp = M::operation(fold_l, tree[index * 2]);\n      if (!f(temp)) {\n   \
    \     index = index * 2;\n      } else {\n        fold_l = temp;\n        index\
    \ = index * 2 + 1;\n      }\n    }\n    return index - size();\n  }\n\npublic:\n\
    \  segment_tree() = default;\n\n  explicit segment_tree(const usize n) : tree(n\
    \ * 2, M::identity) {}\n\n  usize size() const noexcept { return tree.size() /\
    \ 2; }\n\n  T fold(usize first, usize last) const {\n    assert(first <= last);\n\
    \    assert(last <= size());\n    first += size();\n    last += size();\n    T\
    \ fold_l = M::identity;\n    T fold_r = M::identity;\n    while (first != last)\
    \ {\n      if (first % 2 != 0) {\n        fold_l = M::operation(fold_l, tree[first]);\n\
    \        first += 1;\n      }\n      first /= 2;\n      if (last % 2 != 0) {\n\
    \        last -= 1;\n        fold_r = M::operation(tree[last], fold_r);\n    \
    \  }\n      last /= 2;\n    }\n    return M::operation(fold_l, fold_r);\n  }\n\
    \  \n  template <class F> usize search(usize first, usize last, const F f) const\
    \ {\n    assert(first <= last);\n    assert(last <= size());\n    first += size();\n\
    \    last += size();\n    const usize last_cp = last;\n    usize shift = 0;\n\
    \    T fold_l = M::identity;\n    while (first != last) {\n      if (first % 2\
    \ != 0) {\n        const T temp = M::operation(fold_l, tree[first]);\n       \
    \ if (!f(temp))\n          return search_subtree(first, f, fold_l);\n        fold_l\
    \ = temp;\n        first += 1;\n      }\n      first /= 2;\n      last /= 2;\n\
    \      shift += 1;\n    }\n    while (shift != 0) {\n      shift -= 1;\n     \
    \ last = last_cp >> shift;\n      if (last % 2 != 0) {\n        last -= 1;\n \
    \       const T temp = M::operation(fold_l, tree[last]);\n        if (!f(temp))\n\
    \          return search_subtree(last, f, fold_l);\n        fold_l = temp;\n \
    \     }\n    }\n    return last_cp - size();\n  }\n\n  void update(usize index,\
    \ const T x) {\n    assert(index < size());\n    index += size();\n    tree[index]\
    \ = x;\n    while (index != 1) {\n      index /= 2;\n      tree[index] = M::operation(tree[index\
    \ * 2], tree[index * 2 + 1]);\n    }\n  }\n};\n\n/**\n * @brief Segment Tree\n\
    \ * @docs docs/segment_tree.md\n * @see https://scrapbox.io/data-structures/Segment_Tree\n\
    \ */\n#line 1 \"other/affine.cpp\"\ntemplate <class T> class affine {\npublic:\n\
    \  T a;\n  T b;\n\n  constexpr affine(const T &a = 1, const T &b = 0) noexcept\
    \ : a(a), b(b) {}\n\n  constexpr T evaluate(const T &x) const noexcept { return\
    \ x * a + b; }\n  friend constexpr affine operator+(const affine &l, const affine\
    \ &r) noexcept {\n    return affine(l.a + r.a, l.b + r.b);\n  }\n  constexpr affine\
    \ composite(const affine &r) const noexcept {\n    return affine(a * r.a, b *\
    \ r.a + r.b);\n  }\n};\n\ntemplate <class T> class affine_composite_monoid {\n\
    public:\n  using value_type = affine<T>;\n  static constexpr value_type operation(const\
    \ value_type &l,\n                                        const value_type &r)\
    \ noexcept {\n    return l.composite(r);\n  }\n  static constexpr value_type identity{};\n\
    };\n#line 2 \"other/modint.cpp\"\n\ntemplate <std::uint_fast64_t Modulus> class\
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
    \ typename modint<Modulus>::u64 modint<Modulus>::mod;\n#line 6 \"test/segment_tree.test.cpp\"\
    \n\n#include <iostream>\n\nint main() {\n#line 1 \"other/fast_ios.cpp\"\nstd::ios::sync_with_stdio(false);\n\
    std::cin.tie(nullptr);\n#line 11 \"test/segment_tree.test.cpp\"\n\n  int n, q;\n\
    \  std::cin >> n >> q;\n  segment_tree<affine_composite_monoid<modint<998244353>>>\
    \ st(n);\n  for (int i = 0; i != n; i += 1) {\n    int a, b;\n    std::cin >>\
    \ a >> b;\n    st.update(i, {a, b});\n  }\n  for (int i = 0; i != q; i += 1) {\n\
    \    int t;\n    std::cin >> t;\n    switch (t) {\n    case 0: {\n      int p,\
    \ c, d;\n      std::cin >> p >> c >> d;\n      st.update(p, {c, d});\n    } break;\n\
    \    case 1: {\n      int l, r, x;\n      std::cin >> l >> r >> x;\n      std::cout\
    \ << st.fold(l, r).evaluate(x).value() << \"\\n\";\n    } break;\n    }\n  }\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_composite\"\
    \n\n#include \"data_structure/segment_tree.cpp\"\n#include \"other/affine.cpp\"\
    \n#include \"other/modint.cpp\"\n\n#include <iostream>\n\nint main() {\n#include\
    \ \"other/fast_ios.cpp\"\n\n  int n, q;\n  std::cin >> n >> q;\n  segment_tree<affine_composite_monoid<modint<998244353>>>\
    \ st(n);\n  for (int i = 0; i != n; i += 1) {\n    int a, b;\n    std::cin >>\
    \ a >> b;\n    st.update(i, {a, b});\n  }\n  for (int i = 0; i != q; i += 1) {\n\
    \    int t;\n    std::cin >> t;\n    switch (t) {\n    case 0: {\n      int p,\
    \ c, d;\n      std::cin >> p >> c >> d;\n      st.update(p, {c, d});\n    } break;\n\
    \    case 1: {\n      int l, r, x;\n      std::cin >> l >> r >> x;\n      std::cout\
    \ << st.fold(l, r).evaluate(x).value() << \"\\n\";\n    } break;\n    }\n  }\n\
    }"
  dependsOn:
  - data_structure/segment_tree.cpp
  - other/int_alias.cpp
  - other/affine.cpp
  - other/modint.cpp
  - other/fast_ios.cpp
  isVerificationFile: true
  path: test/segment_tree.test.cpp
  requiredBy: []
  timestamp: '2020-03-11 22:58:19+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/segment_tree.test.cpp
layout: document
redirect_from:
- /verify/test/segment_tree.test.cpp
- /verify/test/segment_tree.test.cpp.html
title: test/segment_tree.test.cpp
---
