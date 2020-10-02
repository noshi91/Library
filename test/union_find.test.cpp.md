---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/union_find.cpp
    title: Union Find
  - icon: ':heavy_check_mark:'
    path: other/fast_ios.cpp
    title: other/fast_ios.cpp
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/unionfind
    links:
    - https://judge.yosupo.jp/problem/unionfind
  bundledCode: "#line 1 \"test/union_find.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\
    \n\n#line 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
    \nusing i32 = std::int32_t;\nusing i64 = std::int64_t;\nusing u32 = std::uint32_t;\n\
    using u64 = std::uint64_t;\nusing isize = std::ptrdiff_t;\nusing usize = std::size_t;\n\
    #line 2 \"data_structure/union_find.cpp\"\n\n#include <cassert>\n#include <utility>\n\
    #include <vector>\n\nclass union_find {\nprivate:\n  class node_type {\n    friend\
    \ union_find;\n\n    usize parent;\n    usize size;\n\n    node_type(const usize\
    \ parent, const usize size)\n        : parent(parent), size(size) {}\n  };\n\n\
    \  std::vector<node_type> tree;\n\npublic:\n  union_find() = default;\n\n  explicit\
    \ union_find(const usize n) : tree(n, node_type(n, 1)) {}\n\n  usize size() const\
    \ { return tree.size(); }\n\n  usize find(const usize x) {\n    assert(x < size());\n\
    \    if (tree[x].parent == size())\n      return x;\n    else\n      return tree[x].parent\
    \ = find(tree[x].parent);\n  }\n\n  bool same(const usize x, const usize y) {\n\
    \    assert(x < size());\n    assert(y < size());\n    return find(x) == find(y);\n\
    \  }\n\n  usize size(const usize x) {\n    assert(x < size());\n    return tree[find(x)].size;\n\
    \  }\n\n  void unite(usize x, usize y) {\n    assert(x < size());\n    assert(y\
    \ < size());\n    x = find(x);\n    y = find(y);\n    if (x != y) {\n      if\
    \ (tree[x].size < tree[y].size)\n        std::swap(x, y);\n      tree[x].size\
    \ += tree[y].size;\n      tree[y].parent = x;\n    }\n  }\n};\n\n/**\n * @brief\
    \ Union Find\n * @see https://scrapbox.io/data-structures/Union_Find\n */\n#line\
    \ 4 \"test/union_find.test.cpp\"\n\n#include <iostream>\n\nint main() {\n#line\
    \ 1 \"other/fast_ios.cpp\"\nstd::ios::sync_with_stdio(false);\nstd::cin.tie(nullptr);\n\
    #line 9 \"test/union_find.test.cpp\"\n\n  int n, q;\n  std::cin >> n >> q;\n \
    \ union_find uf(n);\n  for (int i = 0; i != q; i += 1) {\n    int t, u, v;\n \
    \   std::cin >> t >> u >> v;\n    switch (t) {\n    case 0: {\n      uf.unite(u,\
    \ v);\n    } break;\n    case 1: {\n      std::cout << uf.same(u, v) << \"\\n\"\
    ;\n    } break;\n    }\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\n\n#include\
    \ \"data_structure/union_find.cpp\"\n\n#include <iostream>\n\nint main() {\n#include\
    \ \"other/fast_ios.cpp\"\n\n  int n, q;\n  std::cin >> n >> q;\n  union_find uf(n);\n\
    \  for (int i = 0; i != q; i += 1) {\n    int t, u, v;\n    std::cin >> t >> u\
    \ >> v;\n    switch (t) {\n    case 0: {\n      uf.unite(u, v);\n    } break;\n\
    \    case 1: {\n      std::cout << uf.same(u, v) << \"\\n\";\n    } break;\n \
    \   }\n  }\n}\n"
  dependsOn:
  - data_structure/union_find.cpp
  - other/int_alias.cpp
  - other/fast_ios.cpp
  isVerificationFile: true
  path: test/union_find.test.cpp
  requiredBy: []
  timestamp: '2020-03-11 22:58:19+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/union_find.test.cpp
layout: document
redirect_from:
- /verify/test/union_find.test.cpp
- /verify/test/union_find.test.cpp.html
title: test/union_find.test.cpp
---
