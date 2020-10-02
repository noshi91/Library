---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/fenwick_tree.cpp
    title: Fenwick Tree
  - icon: ':heavy_check_mark:'
    path: other/fast_ios.cpp
    title: other/fast_ios.cpp
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  - icon: ':heavy_check_mark:'
    path: other/plus_monoid.cpp
    title: other/plus_monoid.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_range_sum
  bundledCode: "#line 1 \"test/fenwick_tree.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\
    \n\n#line 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
    \nusing i32 = std::int32_t;\nusing i64 = std::int64_t;\nusing u32 = std::uint32_t;\n\
    using u64 = std::uint64_t;\nusing isize = std::ptrdiff_t;\nusing usize = std::size_t;\n\
    #line 2 \"data_structure/fenwick_tree.cpp\"\n\n#include <cassert>\n#line 5 \"\
    data_structure/fenwick_tree.cpp\"\n#include <vector>\n\ntemplate <class M> class\
    \ fenwick_tree {\n  using T = typename M::value_type;\n\npublic:\n  using value_type\
    \ = T;\n\nprivate:\n  std::vector<T> tree;\n\npublic:\n  fenwick_tree() = default;\n\
    \n  explicit fenwick_tree(const usize size) : tree(size + 1, M::identity) {}\n\
    \n  bool empty() const { return size() == 0; }\n  \n  usize size() const { return\
    \ tree.size() - 1; }\n\n  T fold_prefix(usize last) const {\n    assert(last <=\
    \ size());\n    T ret = M::identity;\n    while (last != 0) {\n      ret = M::operation(tree[last],\
    \ ret);\n      last &= last - 1;\n    }\n    return ret;\n  }\n\n  void add(usize\
    \ index, const T value) {\n    assert(index < size());\n    index += 1;\n    while\
    \ (index < tree.size()) {\n      tree[index] = M::operation(tree[index], value);\n\
    \      index += index & ~index + 1;\n    }\n  }\n};\n\n/**\n * @brief Fenwick\
    \ Tree\n * @see https://scrapbox.io/data-structures/Fenwick_Tree\n */\n#line 1\
    \ \"other/plus_monoid.cpp\"\ntemplate <class T> class plus_monoid {\npublic:\n\
    \  using value_type = T;\n  static T operation(const T l, const T r) { return\
    \ l + r; }\n  static constexpr T identity = 0;\n};\n#line 5 \"test/fenwick_tree.test.cpp\"\
    \n\n#include <iostream>\n\nint main() {\n#line 1 \"other/fast_ios.cpp\"\nstd::ios::sync_with_stdio(false);\n\
    std::cin.tie(nullptr);\n#line 10 \"test/fenwick_tree.test.cpp\"\n\n  using i64\
    \ = long long;\n\n  int n, q;\n  std::cin >> n >> q;\n  fenwick_tree<plus_monoid<i64>>\
    \ ft(n);\n  for (int i = 0; i != n; i += 1) {\n    i64 a;\n    std::cin >> a;\n\
    \    ft.add(i, a);\n  }\n  for (int i = 0; i != q; i += 1) {\n    int t;\n   \
    \ std::cin >> t;\n    switch (t) {\n    case 0: {\n      int p;\n      i64 x;\n\
    \      std::cin >> p >> x;\n      ft.add(p, x);\n    } break;\n    case 1: {\n\
    \      int l, r;\n      std::cin >> l >> r;\n      std::cout << -ft.fold_prefix(l)\
    \ + ft.fold_prefix(r) << \"\\n\";\n    } break;\n    }\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\
    \n#include \"data_structure/fenwick_tree.cpp\"\n#include \"other/plus_monoid.cpp\"\
    \n\n#include <iostream>\n\nint main() {\n#include \"other/fast_ios.cpp\"\n\n \
    \ using i64 = long long;\n\n  int n, q;\n  std::cin >> n >> q;\n  fenwick_tree<plus_monoid<i64>>\
    \ ft(n);\n  for (int i = 0; i != n; i += 1) {\n    i64 a;\n    std::cin >> a;\n\
    \    ft.add(i, a);\n  }\n  for (int i = 0; i != q; i += 1) {\n    int t;\n   \
    \ std::cin >> t;\n    switch (t) {\n    case 0: {\n      int p;\n      i64 x;\n\
    \      std::cin >> p >> x;\n      ft.add(p, x);\n    } break;\n    case 1: {\n\
    \      int l, r;\n      std::cin >> l >> r;\n      std::cout << -ft.fold_prefix(l)\
    \ + ft.fold_prefix(r) << \"\\n\";\n    } break;\n    }\n  }\n}"
  dependsOn:
  - data_structure/fenwick_tree.cpp
  - other/int_alias.cpp
  - other/plus_monoid.cpp
  - other/fast_ios.cpp
  isVerificationFile: true
  path: test/fenwick_tree.test.cpp
  requiredBy: []
  timestamp: '2020-03-11 22:42:07+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/fenwick_tree.test.cpp
layout: document
redirect_from:
- /verify/test/fenwick_tree.test.cpp
- /verify/test/fenwick_tree.test.cpp.html
title: test/fenwick_tree.test.cpp
---
