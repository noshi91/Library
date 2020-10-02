---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/erasable_heap.test.cpp
    title: test/erasable_heap.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/pairing_heap.test.cpp
    title: test/pairing_heap.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Pairing Heap
    links: []
  bundledCode: "#line 1 \"data_structure/pairing_heap.cpp\"\n#include <cassert>\n\
    #include <memory>\n#include <utility>\n\ntemplate <class W> class pairing_heap\
    \ {\n  using Self = pairing_heap;\n  using T = typename W::value_type;\n\npublic:\n\
    \  using value_compare = W;\n  using value_type = T;\n\nprivate:\n  class node_type;\n\
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
    \ std::move(y.root)));\n  }\n};\n\n/**\n * @brief Pairing Heap\n */\n"
  code: "#include <cassert>\n#include <memory>\n#include <utility>\n\ntemplate <class\
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
    \  }\n};\n\n/**\n * @brief Pairing Heap\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/pairing_heap.cpp
  requiredBy: []
  timestamp: '2020-03-11 22:42:07+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/pairing_heap.test.cpp
  - test/erasable_heap.test.cpp
documentation_of: data_structure/pairing_heap.cpp
layout: document
redirect_from:
- /library/data_structure/pairing_heap.cpp
- /library/data_structure/pairing_heap.cpp.html
title: Pairing Heap
---
