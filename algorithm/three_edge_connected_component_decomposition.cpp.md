---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/union_enumerate.cpp
    title: Union Enumerate
  - icon: ':heavy_check_mark:'
    path: other/int_alias.cpp
    title: other/int_alias.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/three_edge_connected_component_decomposition.test.cpp
    title: test/three_edge_connected_component_decomposition.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: 3-Edge-Connected Component Decomposition
    links:
    - https://www.sciencedirect.com/science/article/abs/pii/S0020019013002470
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
    \ */\n#line 3 \"algorithm/three_edge_connected_component_decomposition.cpp\"\n\
    \n#include <algorithm>\n#include <functional>\n#line 8 \"algorithm/three_edge_connected_component_decomposition.cpp\"\
    \n\nstd::vector<std::vector<usize>> three_edge_connected_component_decomposition(\n\
    \    const std::vector<std::vector<usize>> &g) {\n  const usize n = g.size();\n\
    \  std::vector<usize> in(n);\n  std::vector<usize> out(n);\n  std::vector<usize>\
    \ low(n, n);\n  std::vector<usize> deg(n, 0);\n  std::vector<usize> path(n, n);\n\
    \  std::vector<bool> visited(n, false);\n  union_enumerate tcc(n);\n\n  const\
    \ auto absorb = [&](const usize v, const usize w) -> void {\n    tcc.unite(v,\
    \ w);\n    deg[v] += deg[w];\n  };\n\n  usize count = 0;\n\n  const std::function<void(usize,\
    \ usize)> dfs = [&](const usize v,\n                                         \
    \           usize p) -> void {\n    visited[v] = true;\n    in[v] = count;\n \
    \   count += 1;\n\n    for (usize w : g[v]) {\n      if (w == v)\n        continue;\n\
    \      if (w == p) {\n        p = n;\n        continue;\n      }\n      if (visited[w])\
    \ {\n        if (in[w] < in[v]) {\n          deg[v] += 1;\n          low[v] =\
    \ std::min(low[v], in[w]);\n        } else {\n          deg[v] -= 1;\n       \
    \   usize u = path[v];\n          while (u != n && in[u] <= in[w] && in[w] < out[u])\
    \ {\n            absorb(v, u);\n            u = path[u];\n          }\n      \
    \    path[v] = u;\n        }\n        continue;\n      }\n      dfs(w, v);\n \
    \     if (path[w] == n && deg[w] <= 1) {\n        deg[v] += deg[w];\n        low[v]\
    \ = std::min(low[v], low[w]);\n        continue;\n      } else if (deg[w] == 0)\
    \ {\n        w = path[w];\n      }\n      if (low[w] < low[v]) {\n        low[v]\
    \ = low[w];\n        std::swap(w, path[v]);\n      }\n      while (w != n) {\n\
    \        absorb(v, w);\n        w = path[w];\n      }\n    }\n\n    out[v] = count;\n\
    \  };\n\n  for (usize i = 0; i != n; i += 1) {\n    if (!visited[i])\n      dfs(i,\
    \ n);\n  }\n\n  return tcc.get_all();\n}\n\n/**\n * @brief 3-Edge-Connected Component\
    \ Decomposition\n * @see https://www.sciencedirect.com/science/article/abs/pii/S0020019013002470\n\
    \ */\n"
  code: "#include \"data_structure/union_enumerate.cpp\"\n#include \"other/int_alias.cpp\"\
    \n\n#include <algorithm>\n#include <functional>\n#include <utility>\n#include\
    \ <vector>\n\nstd::vector<std::vector<usize>> three_edge_connected_component_decomposition(\n\
    \    const std::vector<std::vector<usize>> &g) {\n  const usize n = g.size();\n\
    \  std::vector<usize> in(n);\n  std::vector<usize> out(n);\n  std::vector<usize>\
    \ low(n, n);\n  std::vector<usize> deg(n, 0);\n  std::vector<usize> path(n, n);\n\
    \  std::vector<bool> visited(n, false);\n  union_enumerate tcc(n);\n\n  const\
    \ auto absorb = [&](const usize v, const usize w) -> void {\n    tcc.unite(v,\
    \ w);\n    deg[v] += deg[w];\n  };\n\n  usize count = 0;\n\n  const std::function<void(usize,\
    \ usize)> dfs = [&](const usize v,\n                                         \
    \           usize p) -> void {\n    visited[v] = true;\n    in[v] = count;\n \
    \   count += 1;\n\n    for (usize w : g[v]) {\n      if (w == v)\n        continue;\n\
    \      if (w == p) {\n        p = n;\n        continue;\n      }\n      if (visited[w])\
    \ {\n        if (in[w] < in[v]) {\n          deg[v] += 1;\n          low[v] =\
    \ std::min(low[v], in[w]);\n        } else {\n          deg[v] -= 1;\n       \
    \   usize u = path[v];\n          while (u != n && in[u] <= in[w] && in[w] < out[u])\
    \ {\n            absorb(v, u);\n            u = path[u];\n          }\n      \
    \    path[v] = u;\n        }\n        continue;\n      }\n      dfs(w, v);\n \
    \     if (path[w] == n && deg[w] <= 1) {\n        deg[v] += deg[w];\n        low[v]\
    \ = std::min(low[v], low[w]);\n        continue;\n      } else if (deg[w] == 0)\
    \ {\n        w = path[w];\n      }\n      if (low[w] < low[v]) {\n        low[v]\
    \ = low[w];\n        std::swap(w, path[v]);\n      }\n      while (w != n) {\n\
    \        absorb(v, w);\n        w = path[w];\n      }\n    }\n\n    out[v] = count;\n\
    \  };\n\n  for (usize i = 0; i != n; i += 1) {\n    if (!visited[i])\n      dfs(i,\
    \ n);\n  }\n\n  return tcc.get_all();\n}\n\n/**\n * @brief 3-Edge-Connected Component\
    \ Decomposition\n * @see https://www.sciencedirect.com/science/article/abs/pii/S0020019013002470\n\
    \ */\n"
  dependsOn:
  - data_structure/union_enumerate.cpp
  - other/int_alias.cpp
  isVerificationFile: false
  path: algorithm/three_edge_connected_component_decomposition.cpp
  requiredBy: []
  timestamp: '2020-03-10 16:21:51+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/three_edge_connected_component_decomposition.test.cpp
documentation_of: algorithm/three_edge_connected_component_decomposition.cpp
layout: document
redirect_from:
- /library/algorithm/three_edge_connected_component_decomposition.cpp
- /library/algorithm/three_edge_connected_component_decomposition.cpp.html
title: 3-Edge-Connected Component Decomposition
---
