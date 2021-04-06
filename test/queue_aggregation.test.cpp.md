---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/queue_aggregation.cpp
    title: Queue Aggregation
  - icon: ':heavy_check_mark:'
    path: data_structure/stack_aggregation.cpp
    title: Stack Aggregation
  - icon: ':heavy_check_mark:'
    path: other/affine.cpp
    title: other/affine.cpp
  - icon: ':heavy_check_mark:'
    path: other/fast_ios.cpp
    title: other/fast_ios.cpp
  - icon: ':heavy_check_mark:'
    path: other/modint.cpp
    title: other/modint.cpp
  - icon: ':heavy_check_mark:'
    path: other/opposite_monoid.cpp
    title: other/opposite_monoid.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/queue_operate_all_composite
    links:
    - https://judge.yosupo.jp/problem/queue_operate_all_composite
  bundledCode: "#line 1 \"test/queue_aggregation.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/queue_operate_all_composite\"\
    \n\n#line 1 \"data_structure/stack_aggregation.cpp\"\n#include <cassert>\n#include\
    \ <stack>\n\ntemplate <class M> class stack_aggregation {\n  using T = typename\
    \ M::value_type;\n\n  class node_type {\n  public:\n    T value;\n    T fold;\n\
    \n    node_type(const T value, const T fold) : value(value), fold(fold) {}\n \
    \ };\n\n  std::stack<node_type> st;\n\npublic:\n  stack_aggregation() = default;\n\
    \n  bool empty() const { return st.empty(); }\n  T top() const {\n    assert(!empty());\n\
    \    return st.top().value;\n  }\n  T fold() const { return st.empty() ? M::identity\
    \ : st.top().fold; }\n\n  void push(const T x) { st.push(node_type(x, M::operation(fold(),\
    \ x))); }\n  void pop() {\n    assert(!empty());\n    st.pop();\n  }\n};\n\n/**\n\
    \ * @brief Stack Aggregation\n * @see https://scrapbox.io/data-structures/Sliding_Window_Aggregation\n\
    \ */\n#line 1 \"other/opposite_monoid.cpp\"\ntemplate <class M> class opposite_monoid\
    \ {\n  using T = typename M::value_type;\n\npublic:\n  using value_type = T;\n\
    \  static constexpr T operation(const T &l, const T &r) noexcept {\n    return\
    \ M::operation(r, l);\n  }\n  static constexpr T identity = M::identity;\n};\n\
    #line 3 \"data_structure/queue_aggregation.cpp\"\n\ntemplate <class M> class queue_aggregation\
    \ {\n  using T = typename M::value_type;\n\n  stack_aggregation<opposite_monoid<M>>\
    \ front_st;\n  stack_aggregation<M> back_st;\n\npublic:\n  queue_aggregation()\
    \ = default;\n\n  bool empty() const { return front_st.empty(); }\n  T fold()\
    \ const { return M::operation(front_st.fold(), back_st.fold()); }\n\n  void push(const\
    \ T x) {\n    if (empty())\n      front_st.push(x);\n    else\n      back_st.push(x);\n\
    \  }\n  void pop() {\n    assert(!empty());\n    front_st.pop();\n    if (front_st.empty())\
    \ {\n      while (!back_st.empty()) {\n        front_st.push(back_st.top());\n\
    \        back_st.pop();\n      }\n    }\n  }\n};\n\n/**\n * @brief Queue Aggregation\n\
    \ * @see https://scrapbox.io/data-structures/Sliding_Window_Aggregation\n */\n\
    #line 1 \"other/affine.cpp\"\ntemplate <class T> class affine {\npublic:\n  T\
    \ a;\n  T b;\n\n  constexpr affine(const T &a = 1, const T &b = 0) noexcept :\
    \ a(a), b(b) {}\n\n  constexpr T evaluate(const T &x) const noexcept { return\
    \ x * a + b; }\n  friend constexpr affine operator+(const affine &l, const affine\
    \ &r) noexcept {\n    return affine(l.a + r.a, l.b + r.b);\n  }\n  constexpr affine\
    \ composite(const affine &r) const noexcept {\n    return affine(a * r.a, b *\
    \ r.a + r.b);\n  }\n};\n\ntemplate <class T> class affine_composite_monoid {\n\
    public:\n  using value_type = affine<T>;\n  static constexpr value_type operation(const\
    \ value_type &l,\n                                        const value_type &r)\
    \ noexcept {\n    return l.composite(r);\n  }\n  static constexpr value_type identity{};\n\
    };\n#line 1 \"other/modint.cpp\"\n#include <cstdint>\n\ntemplate <std::uint_fast64_t\
    \ Modulus> class modint {\n  using u64 = std::uint_fast64_t;\n\npublic:\n  using\
    \ value_type = u64;\n\n  static constexpr u64 mod = Modulus;\n\nprivate:\n  static_assert(mod\
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
    \ typename modint<Modulus>::u64 modint<Modulus>::mod;\n#line 6 \"test/queue_aggregation.test.cpp\"\
    \n\n#include <iostream>\n\nint main() {\n#line 1 \"other/fast_ios.cpp\"\nstd::ios::sync_with_stdio(false);\n\
    std::cin.tie(nullptr);\n#line 11 \"test/queue_aggregation.test.cpp\"\n\n  queue_aggregation<affine_composite_monoid<modint<998244353>>>\
    \ qa;\n\n  int q;\n  std::cin >> q;\n\n  for (int i = 0; i != q; i += 1) {\n \
    \   int t;\n    std::cin >> t;\n    switch (t) {\n    case 0: {\n      int a,\
    \ b;\n      std::cin >> a >> b;\n      qa.push({a, b});\n    } break;\n    case\
    \ 1: {\n      qa.pop();\n    } break;\n    case 2: {\n      int x;\n      std::cin\
    \ >> x;\n      std::cout << qa.fold().evaluate(x).value() << \"\\n\";\n    } break;\n\
    \    }\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/queue_operate_all_composite\"\
    \n\n#include \"data_structure/queue_aggregation.cpp\"\n#include \"other/affine.cpp\"\
    \n#include \"other/modint.cpp\"\n\n#include <iostream>\n\nint main() {\n#include\
    \ \"other/fast_ios.cpp\"\n\n  queue_aggregation<affine_composite_monoid<modint<998244353>>>\
    \ qa;\n\n  int q;\n  std::cin >> q;\n\n  for (int i = 0; i != q; i += 1) {\n \
    \   int t;\n    std::cin >> t;\n    switch (t) {\n    case 0: {\n      int a,\
    \ b;\n      std::cin >> a >> b;\n      qa.push({a, b});\n    } break;\n    case\
    \ 1: {\n      qa.pop();\n    } break;\n    case 2: {\n      int x;\n      std::cin\
    \ >> x;\n      std::cout << qa.fold().evaluate(x).value() << \"\\n\";\n    } break;\n\
    \    }\n  }\n}"
  dependsOn:
  - data_structure/queue_aggregation.cpp
  - data_structure/stack_aggregation.cpp
  - other/opposite_monoid.cpp
  - other/affine.cpp
  - other/modint.cpp
  - other/fast_ios.cpp
  isVerificationFile: true
  path: test/queue_aggregation.test.cpp
  requiredBy: []
  timestamp: '2020-03-11 00:35:25+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/queue_aggregation.test.cpp
layout: document
redirect_from:
- /verify/test/queue_aggregation.test.cpp
- /verify/test/queue_aggregation.test.cpp.html
title: test/queue_aggregation.test.cpp
---
