---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: data_structure/incremental_bridge_connectivity.cpp
    title: Incremental Bridge-Connectivity
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/incremental_bridge_connectivity.test.cpp
    title: test/incremental_bridge_connectivity.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/union_find.test.cpp
    title: test/union_find.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Union Find
    links:
    - https://scrapbox.io/data-structures/Union_Find
  bundledCode: "#line 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
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
    \ Union Find\n * @see https://scrapbox.io/data-structures/Union_Find\n */\n"
  code: "#include \"other/int_alias.cpp\"\n\n#include <cassert>\n#include <utility>\n\
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
    \ Union Find\n * @see https://scrapbox.io/data-structures/Union_Find\n */\n"
  dependsOn:
  - other/int_alias.cpp
  isVerificationFile: false
  path: data_structure/union_find.cpp
  requiredBy:
  - data_structure/incremental_bridge_connectivity.cpp
  timestamp: '2020-03-11 22:58:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/union_find.test.cpp
  - test/incremental_bridge_connectivity.test.cpp
documentation_of: data_structure/union_find.cpp
layout: document
redirect_from:
- /library/data_structure/union_find.cpp
- /library/data_structure/union_find.cpp.html
title: Union Find
---
