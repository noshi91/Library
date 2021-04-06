---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Partially Persistent Union Find
    links: []
  bundledCode: "#line 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
    \nusing i32 = std::int32_t;\nusing i64 = std::int64_t;\nusing u32 = std::uint32_t;\n\
    using u64 = std::uint64_t;\nusing isize = std::ptrdiff_t;\nusing usize = std::size_t;\n\
    #line 2 \"data_structure/partially_persistent_union_find.cpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#line 6 \"data_structure/partially_persistent_union_find.cpp\"\
    \n#include <iterator>\n#include <limits>\n#include <vector>\n\nclass partially_persistent_union_find\
    \ {\npublic:\n  using time_type = usize;\n\nprivate:\n  class node_type {\n  public:\n\
    \    time_type time;\n    usize parent;\n    usize size;\n\n    node_type(const\
    \ time_type time, const usize parent, const usize size)\n        : time(time),\
    \ parent(parent), size(size) {}\n  };\n\n  class sh_node {\n  public:\n    time_type\
    \ time;\n    usize size;\n\n    sh_node(const time_type time, const usize size)\
    \ : time(time), size(size) {}\n  };\n\n  std::vector<node_type> tree;\n  std::vector<std::vector<sh_node>>\
    \ size_history;\n  time_type time_count;\n\n  usize size() const { return tree.size();\
    \ }\n\npublic:\n  partially_persistent_union_find() = default;\n\n  explicit partially_persistent_union_find(const\
    \ usize n)\n      : tree(n, node_type(std::numeric_limits<time_type>::max(), 0,\
    \ 1)),\n        size_history(n, std::vector<sh_node>({sh_node(0, 1)})), time_count(0)\
    \ {\n    for (usize i = 0; i != n; i += 1)\n      tree[i].parent = i;\n  }\n\n\
    \  time_type now() const { return time_count; }\n\n  usize find(const time_type\
    \ time, usize x) const {\n    assert(x < size());\n    \n    while (tree[x].time\
    \ <= time)\n      x = tree[x].parent;\n    return x;\n  }\n\n  bool same(const\
    \ time_type time, const usize x, const usize y) const {\n    assert(x < size());\n\
    \    assert(y < size());\n\n    return find(time, x) == find(time, y);\n  }\n\n\
    \  usize size(const time_type time, usize x) const {\n    assert(x < size());\n\
    \n    x = find(time, x);\n    return std::prev(std::partition_point(\n       \
    \                  size_history[x].cbegin(), size_history[x].cend(),\n       \
    \                  [time](const sh_node &h) { return h.time <= time; }))\n   \
    \     ->size;\n  }\n\n  time_type unite(usize x, usize y) {\n    assert(x < tree.size());\n\
    \    assert(y < tree.size());\n\n    x = find(now(), x);\n    y = find(now(),\
    \ y);\n    time_count += 1;\n    if (x != y) {\n      if (tree[x].size < tree[y].size)\n\
    \        std::swap(x, y);\n      tree[x].size += tree[y].size;\n      tree[y].parent\
    \ = x;\n      tree[y].time = time_count;\n      size_history[x].push_back(sh_node(time_count,\
    \ tree[x].size));\n    }\n    return time_count - 1;\n  }\n};\n\n/**\n * @brief\
    \ Partially Persistent Union Find\n */\n"
  code: "#include \"other/int_alias.cpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <cstddef>\n#include <iterator>\n#include <limits>\n#include <vector>\n\
    \nclass partially_persistent_union_find {\npublic:\n  using time_type = usize;\n\
    \nprivate:\n  class node_type {\n  public:\n    time_type time;\n    usize parent;\n\
    \    usize size;\n\n    node_type(const time_type time, const usize parent, const\
    \ usize size)\n        : time(time), parent(parent), size(size) {}\n  };\n\n \
    \ class sh_node {\n  public:\n    time_type time;\n    usize size;\n\n    sh_node(const\
    \ time_type time, const usize size) : time(time), size(size) {}\n  };\n\n  std::vector<node_type>\
    \ tree;\n  std::vector<std::vector<sh_node>> size_history;\n  time_type time_count;\n\
    \n  usize size() const { return tree.size(); }\n\npublic:\n  partially_persistent_union_find()\
    \ = default;\n\n  explicit partially_persistent_union_find(const usize n)\n  \
    \    : tree(n, node_type(std::numeric_limits<time_type>::max(), 0, 1)),\n    \
    \    size_history(n, std::vector<sh_node>({sh_node(0, 1)})), time_count(0) {\n\
    \    for (usize i = 0; i != n; i += 1)\n      tree[i].parent = i;\n  }\n\n  time_type\
    \ now() const { return time_count; }\n\n  usize find(const time_type time, usize\
    \ x) const {\n    assert(x < size());\n    \n    while (tree[x].time <= time)\n\
    \      x = tree[x].parent;\n    return x;\n  }\n\n  bool same(const time_type\
    \ time, const usize x, const usize y) const {\n    assert(x < size());\n    assert(y\
    \ < size());\n\n    return find(time, x) == find(time, y);\n  }\n\n  usize size(const\
    \ time_type time, usize x) const {\n    assert(x < size());\n\n    x = find(time,\
    \ x);\n    return std::prev(std::partition_point(\n                         size_history[x].cbegin(),\
    \ size_history[x].cend(),\n                         [time](const sh_node &h) {\
    \ return h.time <= time; }))\n        ->size;\n  }\n\n  time_type unite(usize\
    \ x, usize y) {\n    assert(x < tree.size());\n    assert(y < tree.size());\n\n\
    \    x = find(now(), x);\n    y = find(now(), y);\n    time_count += 1;\n    if\
    \ (x != y) {\n      if (tree[x].size < tree[y].size)\n        std::swap(x, y);\n\
    \      tree[x].size += tree[y].size;\n      tree[y].parent = x;\n      tree[y].time\
    \ = time_count;\n      size_history[x].push_back(sh_node(time_count, tree[x].size));\n\
    \    }\n    return time_count - 1;\n  }\n};\n\n/**\n * @brief Partially Persistent\
    \ Union Find\n */\n"
  dependsOn:
  - other/int_alias.cpp
  isVerificationFile: false
  path: data_structure/partially_persistent_union_find.cpp
  requiredBy: []
  timestamp: '2020-03-11 22:58:19+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/partially_persistent_union_find.cpp
layout: document
redirect_from:
- /library/data_structure/partially_persistent_union_find.cpp
- /library/data_structure/partially_persistent_union_find.cpp.html
title: Partially Persistent Union Find
---
