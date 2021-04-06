---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/pairing_heap.cpp
    title: Pairing Heap
  - icon: ':heavy_check_mark:'
    path: other/fast_ios.cpp
    title: other/fast_ios.cpp
  - icon: ':heavy_check_mark:'
    path: other/less_equal_ordered_set.cpp
    title: other/less_equal_ordered_set.cpp
  - icon: ':heavy_check_mark:'
    path: other/opposite_ordered_set.cpp
    title: other/opposite_ordered_set.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2170&lang=en
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2170&lang=en
  bundledCode: "#line 1 \"test/pairing_heap.test.cpp\"\n#define PROBLEM          \
    \                                                      \\\n  \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2170&lang=en\"\
    \n\n#line 1 \"data_structure/pairing_heap.cpp\"\n#include <cassert>\n#include\
    \ <memory>\n#include <utility>\n\ntemplate <class W> class pairing_heap {\n  using\
    \ Self = pairing_heap;\n  using T = typename W::value_type;\n\npublic:\n  using\
    \ value_compare = W;\n  using value_type = T;\n\nprivate:\n  class node_type;\n\
    \  using node_ptr = std::unique_ptr<node_type>;\n  class node_type {\n  public:\n\
    \    T value;\n    node_ptr head;\n    node_ptr next;\n\n    node_type(T value)\
    \ : value(std::move(value)), head(), next() {}\n  };\n\n  static node_ptr merge(node_ptr\
    \ x, node_ptr y) {\n    if (!x)\n      return y;\n    if (!y)\n      return x;\n\
    \    if (!W::compare(x->value, y->value))\n      std::swap(x, y);\n    y->next\
    \ = std::move(x->head);\n    x->head = std::move(y);\n    return x;\n  }\n\n \
    \ static node_ptr merge_list(node_ptr list) {\n    if (!list || !list->next)\n\
    \      return list;\n    node_ptr next = std::move(list->next);\n    node_ptr\
    \ rem = std::move(next->next);\n    return merge(merge(std::move(list), std::move(next)),\n\
    \                 merge_list(std::move(rem)));\n  }\n\n  node_ptr root;\n\n  pairing_heap(node_ptr\
    \ root) : root(std::move(root)) {}\n\npublic:\n  pairing_heap() = default;\n\n\
    \  bool empty() const { return !root; }\n\n  const T &top() const {\n    assert(!empty());\n\
    \n    return root->value;\n  }\n\n  void push(T x) {\n    root = merge(std::move(root),\
    \ std::make_unique<node_type>(std::move(x)));\n  }\n\n  T pop() {\n    assert(!empty());\n\
    \n    T ret = std::move(root->value);\n    root = merge_list(std::move(root->head));\n\
    \    return ret;\n  }\n\n  static Self meld(Self x, Self y) {\n    return Self(merge(std::move(x.root),\
    \ std::move(y.root)));\n  }\n};\n\n/**\n * @brief Pairing Heap\n */\n#line 1 \"\
    other/less_equal_ordered_set.cpp\"\ntemplate <class T> class less_equal_ordered_set\
    \ {\npublic:\n  using value_type = T;\n  static constexpr bool compare(const T\
    \ &x, const T &y) noexcept {\n    return x <= y;\n  }\n};\n#line 1 \"other/opposite_ordered_set.cpp\"\
    \ntemplate <class W> class opposite_ordered_set {\n  using T = typename W::value_type;\n\
    \npublic:\n  using value_type = T;\n  static constexpr bool compare(const T &l,\
    \ const T &r) noexcept {\n    return W::compare(r, l);\n  }\n};\n#line 7 \"test/pairing_heap.test.cpp\"\
    \n\n#include <algorithm>\n#include <iostream>\n#include <stack>\n#line 12 \"test/pairing_heap.test.cpp\"\
    \n#include <vector>\n\nvoid solve(const int n, const int q) {\n  using heap_type\
    \ =\n      pairing_heap<opposite_ordered_set<less_equal_ordered_set<int>>>;\n\n\
    \  std::vector<int> p(n), deg(n, 0);\n  for (int i = 1; i != n; i += 1) {\n  \
    \  std::cin >> p[i];\n    p[i] -= 1;\n    deg[p[i]] += 1;\n  }\n  std::vector<heap_type>\
    \ ph(n);\n  std::vector<int> time(n, q);\n  time[0] = -1;\n  for (int i = 0; i\
    \ != q; i += 1) {\n    char c;\n    std::cin >> c;\n    switch (c) {\n    case\
    \ 'M': {\n      int v;\n      std::cin >> v;\n      v -= 1;\n      time[v] = std::min(time[v],\
    \ i);\n    } break;\n    case 'Q': {\n      int v;\n      std::cin >> v;\n   \
    \   v -= 1;\n      ph[v].push(i);\n    } break;\n    }\n  }\n  std::stack<int>\
    \ st;\n  for (int i = 0; i != n; i += 1) {\n    if (deg[i] == 0)\n      st.push(i);\n\
    \  }\n  long long ans = 0;\n  while (!st.empty()) {\n    const int v = st.top();\n\
    \    st.pop();\n    auto &pv = ph[v];\n    while (!pv.empty() && time[v] < pv.top())\
    \ {\n      pv.pop();\n      ans += v + 1;\n    }\n    if (v == 0)\n      continue;\n\
    \    ph[p[v]] = heap_type::meld(std::move(ph[p[v]]), std::move(pv));\n    deg[p[v]]\
    \ -= 1;\n    if (deg[p[v]] == 0)\n      st.push(p[v]);\n  }\n  std::cout << ans\
    \ << \"\\n\";\n}\n\nint main() {\n#line 1 \"other/fast_ios.cpp\"\nstd::ios::sync_with_stdio(false);\n\
    std::cin.tie(nullptr);\n#line 71 \"test/pairing_heap.test.cpp\"\n\n  while (true)\
    \ {\n    int n, q;\n    std::cin >> n >> q;\n    if (n == 0 && q == 0)\n     \
    \ break;\n    solve(n, q);\n  }\n}\n"
  code: "#define PROBLEM                                                         \
    \       \\\n  \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2170&lang=en\"\
    \n\n#include \"data_structure/pairing_heap.cpp\"\n#include \"other/less_equal_ordered_set.cpp\"\
    \n#include \"other/opposite_ordered_set.cpp\"\n\n#include <algorithm>\n#include\
    \ <iostream>\n#include <stack>\n#include <utility>\n#include <vector>\n\nvoid\
    \ solve(const int n, const int q) {\n  using heap_type =\n      pairing_heap<opposite_ordered_set<less_equal_ordered_set<int>>>;\n\
    \n  std::vector<int> p(n), deg(n, 0);\n  for (int i = 1; i != n; i += 1) {\n \
    \   std::cin >> p[i];\n    p[i] -= 1;\n    deg[p[i]] += 1;\n  }\n  std::vector<heap_type>\
    \ ph(n);\n  std::vector<int> time(n, q);\n  time[0] = -1;\n  for (int i = 0; i\
    \ != q; i += 1) {\n    char c;\n    std::cin >> c;\n    switch (c) {\n    case\
    \ 'M': {\n      int v;\n      std::cin >> v;\n      v -= 1;\n      time[v] = std::min(time[v],\
    \ i);\n    } break;\n    case 'Q': {\n      int v;\n      std::cin >> v;\n   \
    \   v -= 1;\n      ph[v].push(i);\n    } break;\n    }\n  }\n  std::stack<int>\
    \ st;\n  for (int i = 0; i != n; i += 1) {\n    if (deg[i] == 0)\n      st.push(i);\n\
    \  }\n  long long ans = 0;\n  while (!st.empty()) {\n    const int v = st.top();\n\
    \    st.pop();\n    auto &pv = ph[v];\n    while (!pv.empty() && time[v] < pv.top())\
    \ {\n      pv.pop();\n      ans += v + 1;\n    }\n    if (v == 0)\n      continue;\n\
    \    ph[p[v]] = heap_type::meld(std::move(ph[p[v]]), std::move(pv));\n    deg[p[v]]\
    \ -= 1;\n    if (deg[p[v]] == 0)\n      st.push(p[v]);\n  }\n  std::cout << ans\
    \ << \"\\n\";\n}\n\nint main() {\n#include \"other/fast_ios.cpp\"\n\n  while (true)\
    \ {\n    int n, q;\n    std::cin >> n >> q;\n    if (n == 0 && q == 0)\n     \
    \ break;\n    solve(n, q);\n  }\n}\n"
  dependsOn:
  - data_structure/pairing_heap.cpp
  - other/less_equal_ordered_set.cpp
  - other/opposite_ordered_set.cpp
  - other/fast_ios.cpp
  isVerificationFile: true
  path: test/pairing_heap.test.cpp
  requiredBy: []
  timestamp: '2020-03-11 22:42:07+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/pairing_heap.test.cpp
layout: document
redirect_from:
- /verify/test/pairing_heap.test.cpp
- /verify/test/pairing_heap.test.cpp.html
title: test/pairing_heap.test.cpp
---
