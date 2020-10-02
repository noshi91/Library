---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: algorithm/three_edge_connected_component_decomposition.cpp
    title: 3-Edge-Connected Component Decomposition
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/three_edge_connected_component_decomposition.test.cpp
    title: test/three_edge_connected_component_decomposition.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Union Enumerate
    links:
    - http://noshi91.hatenablog.com/entry/2019/07/19/180606
  bundledCode: "#line 2 \"other/int_alias.cpp\"\n\n#include <cstddef>\n#include <cstdint>\n\
    \nusing i32 = std::int32_t;\nusing i64 = std::int64_t;\nusing u32 = std::uint32_t;\n\
    using u64 = std::uint64_t;\nusing isize = std::ptrdiff_t;\nusing usize = std::size_t;\n\
    #line 2 \"data_structure/union_enumerate.cpp\"\n\n#include <cassert>\n#line 5\
    \ \"data_structure/union_enumerate.cpp\"\n#include <numeric>\n#include <utility>\n\
    #include <vector>\n\nclass union_enumerate {\n  std::vector<usize> next;\n\npublic:\n\
    \  union_enumerate() = default;\n  union_enumerate(const usize size) : next(size)\
    \ {\n    std::iota(next.begin(), next.end(), static_cast<usize>(0));\n  }\n\n\
    \  usize size() const { return next.size(); }\n\n  std::vector<usize> enumerate(const\
    \ usize x) const {\n    assert(x < size());\n\n    std::vector<usize> ret;\n \
    \   usize y = x;\n    do {\n      ret.push_back(y);\n      y = next[y];\n    }\
    \ while (y != x);\n    return ret;\n  }\n\n  std::vector<std::vector<usize>> get_all()\
    \ const {\n    const usize n = size();\n    std::vector<std::vector<usize>> res;\n\
    \    std::vector<bool> visited(n, false);\n    for (usize i = 0; i != n; i +=\
    \ 1) {\n      if (!visited[i]) {\n        const std::vector<usize> list = enumerate(i);\n\
    \        for (const usize j : list)\n          visited[j] = true;\n        res.push_back(list);\n\
    \      }\n    }\n    return res;\n  }\n\n  void unite(const usize x, const usize\
    \ y) {\n    assert(x < size());\n    assert(y < size());\n\n    std::swap(next[x],\
    \ next[y]);\n  }\n};\n\n/**\n * @brief Union Enumerate\n * @see http://noshi91.hatenablog.com/entry/2019/07/19/180606\n\
    \ */\n"
  code: "#include \"other/int_alias.cpp\"\n\n#include <cassert>\n#include <cstddef>\n\
    #include <numeric>\n#include <utility>\n#include <vector>\n\nclass union_enumerate\
    \ {\n  std::vector<usize> next;\n\npublic:\n  union_enumerate() = default;\n \
    \ union_enumerate(const usize size) : next(size) {\n    std::iota(next.begin(),\
    \ next.end(), static_cast<usize>(0));\n  }\n\n  usize size() const { return next.size();\
    \ }\n\n  std::vector<usize> enumerate(const usize x) const {\n    assert(x < size());\n\
    \n    std::vector<usize> ret;\n    usize y = x;\n    do {\n      ret.push_back(y);\n\
    \      y = next[y];\n    } while (y != x);\n    return ret;\n  }\n\n  std::vector<std::vector<usize>>\
    \ get_all() const {\n    const usize n = size();\n    std::vector<std::vector<usize>>\
    \ res;\n    std::vector<bool> visited(n, false);\n    for (usize i = 0; i != n;\
    \ i += 1) {\n      if (!visited[i]) {\n        const std::vector<usize> list =\
    \ enumerate(i);\n        for (const usize j : list)\n          visited[j] = true;\n\
    \        res.push_back(list);\n      }\n    }\n    return res;\n  }\n\n  void\
    \ unite(const usize x, const usize y) {\n    assert(x < size());\n    assert(y\
    \ < size());\n\n    std::swap(next[x], next[y]);\n  }\n};\n\n/**\n * @brief Union\
    \ Enumerate\n * @see http://noshi91.hatenablog.com/entry/2019/07/19/180606\n */\n"
  dependsOn:
  - other/int_alias.cpp
  isVerificationFile: false
  path: data_structure/union_enumerate.cpp
  requiredBy:
  - algorithm/three_edge_connected_component_decomposition.cpp
  timestamp: '2020-03-07 01:49:05+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/three_edge_connected_component_decomposition.test.cpp
documentation_of: data_structure/union_enumerate.cpp
layout: document
redirect_from:
- /library/data_structure/union_enumerate.cpp
- /library/data_structure/union_enumerate.cpp.html
title: Union Enumerate
---
