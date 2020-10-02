---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/potentialized_union_find.cpp
    title: Potentialized Union Find
  - icon: ':heavy_check_mark:'
    path: other/fast_ios.cpp
    title: other/fast_ios.cpp
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  - icon: ':heavy_check_mark:'
    path: other/plus_group.cpp
    title: other/plus_group.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B&lang=ja
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B&lang=ja
  bundledCode: "#line 1 \"test/potentialized_union_find.test.cpp\"\n#define PROBLEM\
    \                                                                \\\n  \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B&lang=ja\"\
    \n\n#line 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
    \nusing i32 = std::int32_t;\nusing i64 = std::int64_t;\nusing u32 = std::uint32_t;\n\
    using u64 = std::uint64_t;\nusing isize = std::ptrdiff_t;\nusing usize = std::size_t;\n\
    #line 2 \"data_structure/potentialized_union_find.cpp\"\n\n#include <cassert>\n\
    #include <vector>\n#include<utility>\n\ntemplate <class G> class potentialized_union_find\
    \ {\n  using T = typename G::value_type;\n  class node_type {\n  public:\n   \
    \ T value;\n    usize parent;\n    usize size;\n\n    node_type(const T value,\
    \ const usize parent, const usize size)\n        : value(value), parent(parent),\
    \ size(size) {}\n  };\n\n  std::vector<node_type> tree;\n\n  void compress(const\
    \ usize x) {\n    const usize p = tree[x].parent;\n    if (p == x)\n      return;\n\
    \    compress(p);\n    tree[x].value = G::operation(tree[p].value, tree[x].value);\n\
    \    tree[x].parent = tree[p].parent;\n  }\n\npublic:\n  potentialized_union_find()\
    \ = default;\n\n  explicit potentialized_union_find(const usize n)\n      : tree(n,\
    \ node_type(G::identity, 0, 1)) {\n    for (usize i = 0; i != n; i += 1)\n   \
    \   tree[i].parent = i;\n  }\n\n  usize size() const { return tree.size(); }\n\
    \n  usize find(const usize x) {\n    assert(x < size());\n\n    compress(x);\n\
    \    return tree[x].parent;\n  }\n\n  T potential(const usize x) {\n    assert(x\
    \ < size());\n\n    compress(x);\n    return tree[x].value;\n  }\n\n  bool same(const\
    \ usize x, const usize y) {\n    assert(x < size());\n\n    compress(x);\n   \
    \ return find(x) == find(y);\n  }\n\n  T distance(const usize x, const usize y)\
    \ {\n    assert(x < size());\n    assert(y < size());\n\n    return G::operation(G::inverse(potential(x)),\
    \ potential(y));\n  }\n\n  usize size(const usize x) {\n    assert(x < size());\n\
    \n    return tree[find(x)].size;\n  }\n\n  void unite(usize x, usize y, T d) {\n\
    \    assert(x < size());\n    assert(y < size());\n    assert(!same(x, y));\n\n\
    \    if (size(x) < size(y)) {\n      d = G::inverse(d);\n      std::swap(x, y);\n\
    \    }\n    d = G::operation(G::operation(potential(x), d), G::inverse(potential(y)));\n\
    \    x = find(x);\n    y = find(y);\n    tree[x].size += tree[y].size;\n    tree[y].parent\
    \ = x;\n    tree[y].value = d;\n  }\n};\n\n/**\n * @brief Potentialized Union\
    \ Find\n */\n#line 1 \"other/plus_group.cpp\"\ntemplate <class T> class plus_group\
    \ {\npublic:\n  using value_type = T;\n  static constexpr T operation(const T\
    \ &l, const T &r) noexcept {\n    return l + r;\n  }\n  static constexpr T identity\
    \ = 0;\n  static constexpr T inverse(const T &x) noexcept { return -x; }\n};\n\
    #line 6 \"test/potentialized_union_find.test.cpp\"\n\n#include <iostream>\n\n\
    int main() {\n#line 1 \"other/fast_ios.cpp\"\nstd::ios::sync_with_stdio(false);\n\
    std::cin.tie(nullptr);\n#line 11 \"test/potentialized_union_find.test.cpp\"\n\n\
    \  int n, q;\n  std::cin >> n >> q;\n  potentialized_union_find<plus_group<int>>\
    \ puf(n);\n  for (int i = 0; i != q; i += 1) {\n    int c;\n    std::cin >> c;\n\
    \    switch (c) {\n    case 0: {\n      int x, y, z;\n      std::cin >> x >> y\
    \ >> z;\n      if (!puf.same(x, y))\n        puf.unite(x, y, z);\n    } break;\n\
    \    case 1: {\n      int x, y;\n      std::cin >> x >> y;\n      if (puf.same(x,\
    \ y))\n        std::cout << puf.distance(x, y) << \"\\n\";\n      else\n     \
    \   std::cout << \"?\\n\";\n    } break;\n    }\n  }\n}\n"
  code: "#define PROBLEM                                                         \
    \       \\\n  \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B&lang=ja\"\
    \n\n#include \"data_structure/potentialized_union_find.cpp\"\n#include \"other/plus_group.cpp\"\
    \n\n#include <iostream>\n\nint main() {\n#include \"other/fast_ios.cpp\"\n\n \
    \ int n, q;\n  std::cin >> n >> q;\n  potentialized_union_find<plus_group<int>>\
    \ puf(n);\n  for (int i = 0; i != q; i += 1) {\n    int c;\n    std::cin >> c;\n\
    \    switch (c) {\n    case 0: {\n      int x, y, z;\n      std::cin >> x >> y\
    \ >> z;\n      if (!puf.same(x, y))\n        puf.unite(x, y, z);\n    } break;\n\
    \    case 1: {\n      int x, y;\n      std::cin >> x >> y;\n      if (puf.same(x,\
    \ y))\n        std::cout << puf.distance(x, y) << \"\\n\";\n      else\n     \
    \   std::cout << \"?\\n\";\n    } break;\n    }\n  }\n}"
  dependsOn:
  - data_structure/potentialized_union_find.cpp
  - other/int_alias.cpp
  - other/plus_group.cpp
  - other/fast_ios.cpp
  isVerificationFile: true
  path: test/potentialized_union_find.test.cpp
  requiredBy: []
  timestamp: '2020-03-11 00:35:25+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/potentialized_union_find.test.cpp
layout: document
redirect_from:
- /verify/test/potentialized_union_find.test.cpp
- /verify/test/potentialized_union_find.test.cpp.html
title: test/potentialized_union_find.test.cpp
---
