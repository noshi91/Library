---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/potentialized_union_find.test.cpp
    title: test/potentialized_union_find.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Potentialized Union Find
    links: []
  bundledCode: "#line 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
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
    \ Find\n */\n"
  code: "#include \"other/int_alias.cpp\"\n\n#include <cassert>\n#include <vector>\n\
    #include<utility>\n\ntemplate <class G> class potentialized_union_find {\n  using\
    \ T = typename G::value_type;\n  class node_type {\n  public:\n    T value;\n\
    \    usize parent;\n    usize size;\n\n    node_type(const T value, const usize\
    \ parent, const usize size)\n        : value(value), parent(parent), size(size)\
    \ {}\n  };\n\n  std::vector<node_type> tree;\n\n  void compress(const usize x)\
    \ {\n    const usize p = tree[x].parent;\n    if (p == x)\n      return;\n   \
    \ compress(p);\n    tree[x].value = G::operation(tree[p].value, tree[x].value);\n\
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
    \ Find\n */\n"
  dependsOn:
  - other/int_alias.cpp
  isVerificationFile: false
  path: data_structure/potentialized_union_find.cpp
  requiredBy: []
  timestamp: '2020-03-11 00:35:25+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/potentialized_union_find.test.cpp
documentation_of: data_structure/potentialized_union_find.cpp
layout: document
redirect_from:
- /library/data_structure/potentialized_union_find.cpp
- /library/data_structure/potentialized_union_find.cpp.html
title: Potentialized Union Find
---
