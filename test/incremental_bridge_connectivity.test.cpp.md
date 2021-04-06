---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/incremental_bridge_connectivity.cpp
    title: Incremental Bridge-Connectivity
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
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/two_edge_connected_components
    links:
    - https://judge.yosupo.jp/problem/two_edge_connected_components
  bundledCode: "#line 1 \"test/incremental_bridge_connectivity.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/two_edge_connected_components\"\n\n\
    #line 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\n\
    using i32 = std::int32_t;\nusing i64 = std::int64_t;\nusing u32 = std::uint32_t;\n\
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
    \ 3 \"data_structure/incremental_bridge_connectivity.cpp\"\n\n#line 6 \"data_structure/incremental_bridge_connectivity.cpp\"\
    \n#include <unordered_set>\n#line 9 \"data_structure/incremental_bridge_connectivity.cpp\"\
    \n\nclass incremental_bridge_connectivity {\n  union_find cc;\n  union_find bcc;\n\
    \  std::vector<usize> bbf;\n\n  usize size() const { return bbf.size(); }\n\n\
    \  usize nil() const { return size(); }\n\n  usize parent(const usize v) {\n \
    \   if (bbf[v] == nil())\n      return nil();\n    else\n      return bcc.find(bbf[v]);\n\
    \  }\n\n  usize lca(usize u, usize v) {\n    std::unordered_set<usize> reached;\n\
    \    while (true) {\n      if (u != nil()) {\n        if (!reached.insert(u).second)\n\
    \          return u;\n        u = parent(u);\n      }\n      std::swap(u, v);\n\
    \    }\n  }\n\n  void condense_path(usize u, const usize v) {\n    while (!bcc.same(u,\
    \ v)) {\n      const usize next = parent(u);\n      bbf[u] = bbf[v];\n      bcc.unite(u,\
    \ v);\n      u = next;\n    }\n  }\n\n  void link(const usize x, const usize y)\
    \ {\n    usize v = x, prev = y;\n    while (v != nil()) {\n      const usize next\
    \ = parent(v);\n      bbf[v] = prev;\n      prev = v;\n      v = next;\n    }\n\
    \  }\n\npublic:\n  incremental_bridge_connectivity() = default;\n\n  explicit\
    \ incremental_bridge_connectivity(const usize n)\n      : cc(n), bcc(n), bbf(n,\
    \ n) {}\n\n  usize find_block(const usize v) {\n    assert(v < size());\n\n  \
    \  return bcc.find(v);\n  }\n\n  bool bridge_connected(const usize u, const usize\
    \ v) {\n    assert(u < size());\n    assert(v < size());\n\n    return bcc.same(u,\
    \ v);\n  }\n\n  void insert_edge(usize u, usize v) {\n    assert(u < size());\n\
    \    assert(v < size());\n\n    u = bcc.find(u);\n    v = bcc.find(v);\n    if\
    \ (cc.same(u, v)) {\n      const usize w = lca(u, v);\n      condense_path(u,\
    \ w);\n      condense_path(v, w);\n    } else {\n      if (cc.size(u) > cc.size(v))\n\
    \        std::swap(u, v);\n      link(u, v);\n      cc.unite(u, v);\n    }\n \
    \ }\n};\n\n/**\n * @brief Incremental Bridge-Connectivity\n * @see https://scrapbox.io/data-structures/Incremental_Bridge-Connectivity\n\
    \ */\n#line 4 \"test/incremental_bridge_connectivity.test.cpp\"\n\n#include <iostream>\n\
    #line 7 \"test/incremental_bridge_connectivity.test.cpp\"\n\nint main() {\n#line\
    \ 1 \"other/fast_ios.cpp\"\nstd::ios::sync_with_stdio(false);\nstd::cin.tie(nullptr);\n\
    #line 10 \"test/incremental_bridge_connectivity.test.cpp\"\n\n  int n, m;\n  std::cin\
    \ >> n >> m;\n  incremental_bridge_connectivity ibc(n);\n  for (int i = 0; i !=\
    \ m; i += 1) {\n    int a, b;\n    std::cin >> a >> b;\n    ibc.insert_edge(a,\
    \ b);\n  }\n\n  std::vector<int> id(n, n);\n  int k = 0;\n  std::vector<std::vector<int>>\
    \ ans(n);\n  for (int i = 0; i != n; i += 1) {\n    const int r = ibc.find_block(i);\n\
    \    if (id[r] == n) {\n      id[r] = k;\n      k += 1;\n    }\n    ans[id[r]].push_back(i);\n\
    \  }\n\n  std::cout << k << \"\\n\";\n  for (int i = 0; i != k; i += 1) {\n  \
    \  std::cout << ans[i].size();\n    for (const int e : ans[i])\n      std::cout\
    \ << \" \" << e;\n    std::cout << \"\\n\";\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/two_edge_connected_components\"\
    \n\n#include \"data_structure/incremental_bridge_connectivity.cpp\"\n\n#include\
    \ <iostream>\n#include <vector>\n\nint main() {\n#include \"other/fast_ios.cpp\"\
    \n\n  int n, m;\n  std::cin >> n >> m;\n  incremental_bridge_connectivity ibc(n);\n\
    \  for (int i = 0; i != m; i += 1) {\n    int a, b;\n    std::cin >> a >> b;\n\
    \    ibc.insert_edge(a, b);\n  }\n\n  std::vector<int> id(n, n);\n  int k = 0;\n\
    \  std::vector<std::vector<int>> ans(n);\n  for (int i = 0; i != n; i += 1) {\n\
    \    const int r = ibc.find_block(i);\n    if (id[r] == n) {\n      id[r] = k;\n\
    \      k += 1;\n    }\n    ans[id[r]].push_back(i);\n  }\n\n  std::cout << k <<\
    \ \"\\n\";\n  for (int i = 0; i != k; i += 1) {\n    std::cout << ans[i].size();\n\
    \    for (const int e : ans[i])\n      std::cout << \" \" << e;\n    std::cout\
    \ << \"\\n\";\n  }\n}\n"
  dependsOn:
  - data_structure/incremental_bridge_connectivity.cpp
  - data_structure/union_find.cpp
  - other/int_alias.cpp
  - other/fast_ios.cpp
  isVerificationFile: true
  path: test/incremental_bridge_connectivity.test.cpp
  requiredBy: []
  timestamp: '2020-03-12 15:47:16+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/incremental_bridge_connectivity.test.cpp
layout: document
redirect_from:
- /verify/test/incremental_bridge_connectivity.test.cpp
- /verify/test/incremental_bridge_connectivity.test.cpp.html
title: test/incremental_bridge_connectivity.test.cpp
---
