---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/erasable_heap.cpp
    title: Erasable Heap
  - icon: ':heavy_check_mark:'
    path: data_structure/pairing_heap.cpp
    title: Pairing Heap
  - icon: ':heavy_check_mark:'
    path: other/fast_ios.cpp
    title: other/fast_ios.cpp
  - icon: ':heavy_check_mark:'
    path: other/less_equal_ordered_set.cpp
    title: other/less_equal_ordered_set.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja
  bundledCode: "#line 1 \"test/erasable_heap.test.cpp\"\n#define PROBLEM         \
    \                                                       \\\n  \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja\"\
    \n\n#line 1 \"data_structure/erasable_heap.cpp\"\n#include <cassert>\n#include\
    \ <utility>\n\ntemplate <class Heap> class erasable_heap {\n  using W = typename\
    \ Heap::value_compare;\n  using T = typename Heap::value_type;\n\npublic:\n  using\
    \ value_compare = W;\n  using value_type = T;\n\nprivate:\n  static bool equivalent(const\
    \ T &x, const T &y) {\n    return W::compare(x, y) && W::compare(y, x);\n  }\n\
    \n  Heap base;\n  Heap erased;\n\n  void normalize() {\n    while (!base.empty()\
    \ && !erased.empty() &&\n           equivalent(base.top(), erased.top())) {\n\
    \      base.pop();\n      erased.pop();\n    }\n  }\n\npublic:\n  erasable_heap()\
    \ = default;\n\n  bool empty() const { return base.empty(); }\n\n  const T &top()\
    \ const {\n    assert(!empty());\n\n    return base.top();\n  }\n\n  void push(T\
    \ x) {\n    base.push(std::move(x));\n    normalize();\n  }\n\n  T pop() {\n \
    \   assert(!empty());\n\n    T ret = base.pop();\n    normalize();\n    return\
    \ ret;\n  }\n\n  void erase(T x) {\n    erased.push(std::move(x));\n    normalize();\n\
    \  }\n};\n\n/**\n * @brief Erasable Heap\n */\n#line 2 \"data_structure/pairing_heap.cpp\"\
    \n#include <memory>\n#line 4 \"data_structure/pairing_heap.cpp\"\n\ntemplate <class\
    \ W> class pairing_heap {\n  using Self = pairing_heap;\n  using T = typename\
    \ W::value_type;\n\npublic:\n  using value_compare = W;\n  using value_type =\
    \ T;\n\nprivate:\n  class node_type;\n  using node_ptr = std::unique_ptr<node_type>;\n\
    \  class node_type {\n  public:\n    T value;\n    node_ptr head;\n    node_ptr\
    \ next;\n\n    node_type(T value) : value(std::move(value)), head(), next() {}\n\
    \  };\n\n  static node_ptr merge(node_ptr x, node_ptr y) {\n    if (!x)\n    \
    \  return y;\n    if (!y)\n      return x;\n    if (!W::compare(x->value, y->value))\n\
    \      std::swap(x, y);\n    y->next = std::move(x->head);\n    x->head = std::move(y);\n\
    \    return x;\n  }\n\n  static node_ptr merge_list(node_ptr list) {\n    if (!list\
    \ || !list->next)\n      return list;\n    node_ptr next = std::move(list->next);\n\
    \    node_ptr rem = std::move(next->next);\n    return merge(merge(std::move(list),\
    \ std::move(next)),\n                 merge_list(std::move(rem)));\n  }\n\n  node_ptr\
    \ root;\n\n  pairing_heap(node_ptr root) : root(std::move(root)) {}\n\npublic:\n\
    \  pairing_heap() = default;\n\n  bool empty() const { return !root; }\n\n  const\
    \ T &top() const {\n    assert(!empty());\n\n    return root->value;\n  }\n\n\
    \  void push(T x) {\n    root = merge(std::move(root), std::make_unique<node_type>(std::move(x)));\n\
    \  }\n\n  T pop() {\n    assert(!empty());\n\n    T ret = std::move(root->value);\n\
    \    root = merge_list(std::move(root->head));\n    return ret;\n  }\n\n  static\
    \ Self meld(Self x, Self y) {\n    return Self(merge(std::move(x.root), std::move(y.root)));\n\
    \  }\n};\n\n/**\n * @brief Pairing Heap\n */\n#line 1 \"other/less_equal_ordered_set.cpp\"\
    \ntemplate <class T> class less_equal_ordered_set {\npublic:\n  using value_type\
    \ = T;\n  static constexpr bool compare(const T &x, const T &y) noexcept {\n \
    \   return x <= y;\n  }\n};\n#line 7 \"test/erasable_heap.test.cpp\"\n\n#include\
    \ <iostream>\n#include <limits>\n#line 11 \"test/erasable_heap.test.cpp\"\n#include\
    \ <vector>\n\nint main() {\n#line 1 \"other/fast_ios.cpp\"\nstd::ios::sync_with_stdio(false);\n\
    std::cin.tie(nullptr);\n#line 15 \"test/erasable_heap.test.cpp\"\n\n  int n, m,\
    \ r;\n  std::cin >> n >> m >> r;\n  std::vector<std::vector<std::pair<int, int>>>\
    \ g(n);\n  for (int i = 0; i != m; i += 1) {\n    int s, t, d;\n    std::cin >>\
    \ s >> t >> d;\n    g[s].emplace_back(d, t);\n  }\n  constexpr int Inf = std::numeric_limits<int>::max();\n\
    \  std::vector<int> dist(n, Inf);\n  dist[r] = 0;\n  erasable_heap<pairing_heap<less_equal_ordered_set<std::pair<int,\
    \ int>>>> heap;\n  heap.push({0, r});\n  while (!heap.empty()) {\n    const auto\
    \ [c, v] = heap.top();\n    heap.pop();\n    for (const auto &[d, u] : g[v]) {\n\
    \      if (c + d < dist[u]) {\n        if (dist[u] != Inf)\n          heap.erase({dist[u],\
    \ u});\n        dist[u] = c + d;\n        heap.push({dist[u], u});\n      }\n\
    \    }\n  }\n  for (int i = 0; i != n; i += 1) {\n    if (dist[i] < Inf)\n   \
    \   std::cout << dist[i];\n    else\n      std::cout << \"INF\";\n    std::cout\
    \ << \"\\n\";\n  }\n}\n"
  code: "#define PROBLEM                                                         \
    \       \\\n  \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=ja\"\
    \n\n#include \"data_structure/erasable_heap.cpp\"\n#include \"data_structure/pairing_heap.cpp\"\
    \n#include \"other/less_equal_ordered_set.cpp\"\n\n#include <iostream>\n#include\
    \ <limits>\n#include <utility>\n#include <vector>\n\nint main() {\n#include \"\
    other/fast_ios.cpp\"\n\n  int n, m, r;\n  std::cin >> n >> m >> r;\n  std::vector<std::vector<std::pair<int,\
    \ int>>> g(n);\n  for (int i = 0; i != m; i += 1) {\n    int s, t, d;\n    std::cin\
    \ >> s >> t >> d;\n    g[s].emplace_back(d, t);\n  }\n  constexpr int Inf = std::numeric_limits<int>::max();\n\
    \  std::vector<int> dist(n, Inf);\n  dist[r] = 0;\n  erasable_heap<pairing_heap<less_equal_ordered_set<std::pair<int,\
    \ int>>>> heap;\n  heap.push({0, r});\n  while (!heap.empty()) {\n    const auto\
    \ [c, v] = heap.top();\n    heap.pop();\n    for (const auto &[d, u] : g[v]) {\n\
    \      if (c + d < dist[u]) {\n        if (dist[u] != Inf)\n          heap.erase({dist[u],\
    \ u});\n        dist[u] = c + d;\n        heap.push({dist[u], u});\n      }\n\
    \    }\n  }\n  for (int i = 0; i != n; i += 1) {\n    if (dist[i] < Inf)\n   \
    \   std::cout << dist[i];\n    else\n      std::cout << \"INF\";\n    std::cout\
    \ << \"\\n\";\n  }\n}"
  dependsOn:
  - data_structure/erasable_heap.cpp
  - data_structure/pairing_heap.cpp
  - other/less_equal_ordered_set.cpp
  - other/fast_ios.cpp
  isVerificationFile: true
  path: test/erasable_heap.test.cpp
  requiredBy: []
  timestamp: '2020-03-11 22:42:07+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/erasable_heap.test.cpp
layout: document
redirect_from:
- /verify/test/erasable_heap.test.cpp
- /verify/test/erasable_heap.test.cpp.html
title: test/erasable_heap.test.cpp
---
